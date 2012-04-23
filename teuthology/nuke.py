import argparse
import yaml

def parse_args():
    from teuthology.run import config_file
    from teuthology.run import MergeConfig

    parser = argparse.ArgumentParser(description='Reset test machines')
    parser.add_argument(
        '-v', '--verbose',
        action='store_true', default=None,
        help='be more verbose'
        )
    parser.add_argument(
        '-t', '--targets',
        nargs='+',
        type=config_file,
        action=MergeConfig,
        default={},
        required=True,
        dest='config',
        help='yaml config containing machines to nuke',
        )
    parser.add_argument(
        '--archive',
        metavar='DIR',
        help='path to archive results in',
        )
    parser.add_argument(
        '--owner',
        help='job owner',
        )
    parser.add_argument(
        '-r', '--reboot-all',
        action='store_true',
        default=False,
        help='reboot all machines',
        )
    parser.add_argument(
        '-s', '--synch-clocks',
        action='store_true',
        default=False,
        help='synchronize clocks on all machines',
        )
    args = parser.parse_args()
    return args

def shutdown_daemons(ctx, log):
    from .orchestra import run
    nodes = {}
    for remote in ctx.cluster.remotes.iterkeys():
        proc = remote.run(
            args=[
                'if', 'grep', '-q', 'ceph-fuse', '/etc/mtab', run.Raw(';'),
                'then',
                'grep', 'ceph-fuse', '/etc/mtab', run.Raw('|'),
                'grep', '-o', " /.* fuse", run.Raw('|'),
                'grep', '-o', "/.* ", run.Raw('|'),
                'xargs', 'sudo', 'fusermount', '-u', run.Raw(';'),
                'fi',
                run.Raw(';'),
                'killall',
                '--quiet',
                'ceph-mon',
                'ceph-osd',
                'ceph-mds',
                'ceph-fuse',
                'radosgw',
                'testrados',
                'rados',
                'apache2',
                'testrados',
                run.Raw('||'),
                'true', # ignore errors from ceph binaries not being found
                ],
            wait=False,
            )
        nodes[remote.name] = proc
    
    for name, proc in nodes.iteritems():
        log.info('Waiting for %s to finish shutdowns...', name)
        proc.exitstatus.get()

def find_kernel_mounts(ctx, log):
    from .orchestra import run
    nodes = {}
    log.info('Looking for kernel mounts to handle...')
    for remote in ctx.cluster.remotes.iterkeys():
        proc = remote.run(
            args=[
                'grep', '-q', ' ceph ' , '/etc/mtab',
                run.Raw('||'),
                'grep', '-q', '^/dev/rbd' , '/etc/mtab',
                ],
            wait=False,
            )
        nodes[remote] = proc
    kernel_mounts = list()
    for remote, proc in nodes.iteritems():
        try:
            proc.exitstatus.get()
            log.debug('kernel mount exists on %s', remote.name)
            kernel_mounts.append(remote)
        except run.CommandFailedError: # no mounts!
            log.debug('no kernel mount on %s', remote.name)
    
    return kernel_mounts

def remove_kernel_mounts(ctx, kernel_mounts, log):
    """
    properly we should be able to just do a forced unmount,
    but that doesn't seem to be working, so you should reboot instead 
    """
    from .orchestra import run
    nodes = {}
    for remote in kernel_mounts:
        log.info('clearing kernel mount from %s', remote.name)
        proc = remote.run(
            args=[
                'grep', 'ceph', '/etc/mtab', run.Raw('|'),
                'grep', '-o', "on /.* type", run.Raw('|'),
                'grep', '-o', "/.* ", run.Raw('|'),
                'xargs', '-r',
                'sudo', 'umount', '-f', run.Raw(';'),
                'fi'
                ],
            wait=False
            )
        nodes[remote] = proc

    for remote, proc in nodes:
        proc.exitstatus.get()

def remove_osd_mounts(ctx, log):
    """
    unmount any osd data mounts (scratch disks)
    """
    from .orchestra import run
    ctx.cluster.run(
        args=[
            'grep', '/tmp/cephtest/data/', '/etc/mtab', run.Raw('|'),
            'awk', '{print $2}', run.Raw('|'),
            'xargs', '-r',
            'sudo', 'umount', run.Raw(';'),
            'true'
            ],
        )

def reboot(ctx, remotes, log):
    import time
    nodes = {}
    for remote in remotes:
        log.info('rebooting %s', remote.name)
        proc = remote.run( # note use of -n to force a no-sync reboot
            args=['sudo', 'reboot', '-f', '-n'],
            wait=False
            )
        nodes[remote] = proc
        # we just ignore these procs because reboot -f doesn't actually
        # send anything back to the ssh client!
        #for remote, proc in nodes.iteritems():
        #proc.exitstatus.get()
    from teuthology.misc import reconnect
    if remotes:
        log.info('waiting for nodes to reboot')
        time.sleep(5) #if we try and reconnect too quickly, it succeeds!
        reconnect(ctx, 480)     #allow 8 minutes for the reboots

def reset_syslog_dir(ctx, log):
    from .orchestra import run
    nodes = {}
    for remote in ctx.cluster.remotes.iterkeys():
        proc = remote.run(
            args=[
                'if', 'test', '-e', '/etc/rsyslog.d/80-cephtest.conf',
                run.Raw(';'),
                'then',
                'sudo', 'rm', '-f', '--', '/etc/rsyslog.d/80-cephtest.conf',
                run.Raw('&&'),
                'sudo', 'initctl', 'restart', 'rsyslog',
                run.Raw(';'),
                'fi',
                run.Raw(';'),
                ],
            wait=False,
            )
        nodes[remote.name] = proc

    for name, proc in nodes.iteritems():
        log.info('Waiting for %s to restart syslog...', name)
        proc.exitstatus.get()

def remove_testing_tree(ctx, log):
    nodes = {}
    for remote in ctx.cluster.remotes.iterkeys():
        proc = remote.run(
            args=[
                'sudo', 'rm', '-rf', '/tmp/cephtest',
                ],
            wait=False,
            )
        nodes[remote.name] = proc

    for name, proc in nodes.iteritems():
        log.info('Waiting for %s to clear filesystem...', name)
        proc.exitstatus.get()

def synch_clocks(remotes, log):
    from .orchestra import run
    nodes = {}
    for remote in remotes:
        proc = remote.run(
            args=[
                'sudo', 'service', 'ntp', 'stop',
                run.Raw('&&'),
                'sudo', 'ntpdate-debian',
                run.Raw('&&'),
                'sudo', 'hwclock', '--systohc', '--utc',
                run.Raw('&&'),
                'sudo', 'service', 'ntp', 'start',
                run.Raw('||'),
                'true',    # ignore errors; we may be racing with ntpd startup
                ],
            wait=False,
            )
        nodes[remote.name] = proc
    for name, proc in nodes.iteritems():
        log.info('Waiting for clock to synchronize on %s...', name)
        proc.exitstatus.get()

def main():
    from gevent import monkey; monkey.patch_all()
    from .orchestra import monkey; monkey.patch_all()

    import logging

    log = logging.getLogger(__name__)

    ctx = parse_args()

    loglevel = logging.INFO
    if ctx.verbose:
        loglevel = logging.DEBUG

    logging.basicConfig(
        level=loglevel,
        )

    from teuthology.misc import read_config
    read_config(ctx)

    log.info('\n  '.join(['targets:', ] + yaml.safe_dump(ctx.config['targets'], default_flow_style=False).splitlines()))

    if ctx.owner is None:
        from teuthology.misc import get_user
        ctx.owner = get_user()

    nuke(ctx, log)

def nuke(ctx, log):
    from teuthology.task.internal import check_lock, connect
    check_lock(ctx, None)
    connect(ctx, None)

    log.info('Unmount ceph-fuse and killing daemons...')
    shutdown_daemons(ctx, log)
    log.info('All daemons killed.')

    log.info('Unmount any osd data directories...')
    remove_osd_mounts(ctx, log)

    log.info('Dealing with any kernel mounts...')
    kernel_mounts = find_kernel_mounts(ctx, log)
    #remove_kernel_mounts(ctx, kernel_mounts, log)
    need_reboot = kernel_mounts
    if ctx.reboot_all:
        need_reboot = ctx.cluster.remotes.keys()
    reboot(ctx, need_reboot, log)
    log.info('All kernel mounts gone.')

    log.info('Synchronizing clocks...')
    if ctx.synch_clocks:
        need_reboot = ctx.cluster.remotes.keys()
    synch_clocks(need_reboot, log)

    log.info('Reseting syslog output locations...')
    reset_syslog_dir(ctx, log)
    log.info('Clearing filesystem of test data...')
    remove_testing_tree(ctx, log)
    log.info('Filesystem Cleared.')
