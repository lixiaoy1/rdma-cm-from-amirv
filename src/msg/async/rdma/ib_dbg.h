// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab

#ifndef __IB_DBG_H__
#define __IB_DBG_H__

#define dout_subsys ceph_subsys_ms
#undef dout_prefix
#define dout_prefix *_dout << "ib_dbg "

#define ibdbg_ldout \
  if (g_ceph_context && g_ceph_context->_log) \
    ldout(g_ceph_context,1) << f << ":" << l << " ib command: " << __func__

static inline struct ibv_srq *_ibv_create_srq(const char *f, int l,
					      struct ibv_pd *pd,
				struct ibv_srq_init_attr *srq_init_attr)
{
  auto ret = ibv_create_srq(pd, srq_init_attr);

  ibdbg_ldout << " pd: " << pd <<
    " | srq: " << ret << dendl;

  return ret;
}
#define ibv_create_srq(...)           _ibv_create_srq(__func__, __LINE__, __VA_ARGS__)

static inline void _ibv_ack_cq_events(const char *f, int l,
                                      struct ibv_cq *cq, unsigned int nevents)
{
  ibdbg_ldout << " cq: " << cq << " nevents: " << nevents << dendl;

  ibv_ack_cq_events(cq, nevents);
}
#define ibv_ack_cq_events(...)        _ibv_ack_cq_events(__func__, __LINE__, __VA_ARGS__)

static inline struct ibv_pd *_ibv_alloc_pd(const char *f, int l,
                                          struct ibv_context *context)
{
  auto ret = ibv_alloc_pd(context);


  ibdbg_ldout << " ctxt: " << context <<
    " | pd: " << ret << dendl;

  return ret;
}
#define ibv_alloc_pd(...)             _ibv_alloc_pd(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_close_device(const char *f, int l,
                                   struct ibv_context *context)
{
  auto ret = ibv_close_device(context);

  ibdbg_ldout << " ctxt: " << context <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_close_device(...)         _ibv_close_device(__func__, __LINE__, __VA_ARGS__)

static inline struct ibv_comp_channel *_ibv_create_comp_channel(const char *f, int l,
                                                               struct ibv_context *context)
{
  auto ret = ibv_create_comp_channel(context);

  ibdbg_ldout << " ctxt: " << context <<
    " | channel: " << ret << " fd: " << ( ret ? ret->fd : -1 ) << dendl;

  return ret;
}
#define ibv_create_comp_channel(...)  _ibv_create_comp_channel(__func__, __LINE__, __VA_ARGS__)

static inline struct ibv_cq *_ibv_create_cq(const char *f, int l,
                                           struct ibv_context *context, int cqe,
                                           void *cq_context,
                                           struct ibv_comp_channel *channel,
                                           int comp_vector)
{
  auto ret = ibv_create_cq(context, cqe, cq_context, channel, comp_vector);

  ibdbg_ldout << " context: " << context << " channel: " << channel <<
    " | cq: " << ret << dendl;

  return ret;
}
#define ibv_create_cq(...)            _ibv_create_cq(__func__, __LINE__, __VA_ARGS__)

static inline struct ibv_qp *_ibv_create_qp(const char *f, int l,
                                            struct ibv_pd *pd,
                                            struct ibv_qp_init_attr *qp_init_attr)
{
  auto ret = ibv_create_qp(pd, qp_init_attr);

  ibdbg_ldout << " pd: " << pd <<
    " send_cq: " << qp_init_attr->send_cq <<
    " recv_cq: " << qp_init_attr->recv_cq <<
    " srq: " << qp_init_attr->srq <<
    " | qp: " << ret << dendl;

  return ret;
}
#define ibv_create_qp(...)            _ibv_create_qp(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_dealloc_pd(const char *f, int l,
                                  struct ibv_pd *pd)
{
  auto ret = ibv_dealloc_pd(pd);

  ibdbg_ldout << " pd: " << pd <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_dealloc_pd(...)           _ibv_dealloc_pd(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_destroy_comp_channel(const char *f, int l,
                                            struct ibv_comp_channel *channel)
{
  auto ret = ibv_destroy_comp_channel(channel);

  ibdbg_ldout << " channel: " << channel <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_destroy_comp_channel(...) _ibv_destroy_comp_channel(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_destroy_cq(const char *f, int l,
                                  struct ibv_cq *cq)
{
  auto ret = ibv_destroy_cq(cq);

  if (ret) {
    ibdbg_ldout << " cq: " << cq <<
      " | ret: " << cpp_strerror(ret) << dendl;
  } else {
    ibdbg_ldout << " cq: " << cq <<
      " | ret: " << ret << dendl;
  }

  return ret;
}
#define ibv_destroy_cq(...)           _ibv_destroy_cq(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_destroy_qp(const char *f, int l,
                                  struct ibv_qp *qp)
{
  auto ret = ibv_destroy_qp(qp);

  ibdbg_ldout << " qp: " << qp <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_destroy_qp(...)           _ibv_destroy_qp(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_destroy_srq(const char *f, int l,
                                   struct ibv_srq *srq)
{
  auto ret = ibv_destroy_srq(srq);

  ibdbg_ldout << " srq: " << srq <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_destroy_srq(...)          _ibv_destroy_srq(__func__, __LINE__, __VA_ARGS__)

//#define ibv_exp_query_gid_attr(...)   _ibv_exp_query_gid_attr(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_fork_init(const char *f, int l)
{
  auto ret = ibv_fork_init();

  ibdbg_ldout <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_fork_init()            _ibv_fork_init(__func__, __LINE__)

static inline void _ibv_free_device_list(const char *f, int l,
                                         struct ibv_device **list)
{
  ibdbg_ldout << " list: " << list << dendl;

  ibv_free_device_list(list);
}
#define ibv_free_device_list(...)     _ibv_free_device_list(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_get_cq_event(const char *f, int l,
                                    struct ibv_comp_channel *channel,
                                    struct ibv_cq **cq, void **cq_context)
{
  auto ret = ibv_get_cq_event(channel, cq, cq_context);

  ibdbg_ldout << " channel: " << channel << " cq: " << cq << " cq_context:" << cq_context <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_get_cq_event(...)         _ibv_get_cq_event(__func__, __LINE__, __VA_ARGS__)

static inline struct ibv_device **_ibv_get_device_list(const char *f, int l,
                                                       int *num_devices)
{
  auto ret = ibv_get_device_list(num_devices);

  ibdbg_ldout <<
    " | num: " << *num_devices << " list: " << ret << dendl;

  return ret;
}
#define ibv_get_device_list(...)      _ibv_get_device_list(__func__, __LINE__, __VA_ARGS__)

static inline const char *_ibv_get_device_name(const char *f, int l,
                                               struct ibv_device *device)
{
  auto ret = ibv_get_device_name(device);

  ibdbg_ldout << " device: " << device <<
    " | name: " << ret << dendl;

  return ret;
}
#define ibv_get_device_name(...)      _ibv_get_device_name(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_modify_qp(const char *f, int l,
                                 struct ibv_qp *qp, struct ibv_qp_attr *attr,
                                 int attr_mask)
{
  auto ret = ibv_modify_qp(qp, attr, attr_mask);

  ibdbg_ldout << " qp: " << qp <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_modify_qp(...)            _ibv_modify_qp(__func__, __LINE__, __VA_ARGS__)

static inline struct ibv_context *_ibv_open_device(const char *f, int l,
                                                   struct ibv_device *device)
{
  auto ret = ibv_open_device(device);

  ibdbg_ldout << " device: " << device <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_open_device(...)          _ibv_open_device(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_poll_cq(const char *f, int l,
                               struct ibv_cq *cq, int num_entries, struct ibv_wc *wc)
{
  auto ret = ibv_poll_cq(cq, num_entries, wc);
  static utime_t last_print = ceph_clock_now();
  static int suppressed_counter = 0;

  if ((ceph_clock_now() - last_print).to_msec() < 100) {
    suppressed_counter++;
    return ret;
  }

  if (suppressed_counter > 0) {
    ibdbg_ldout << " cq: " << cq << " num_entries: " << num_entries <<
      " | ret: " << ret <<
      " {suppressed " << suppressed_counter << " prints}" << dendl;
    suppressed_counter = 0;
  } else {
    ibdbg_ldout << " cq: " << cq << " num_entries: " << num_entries <<
      " | ret: " << ret << dendl;
  }

  last_print = ceph_clock_now();

  return ret;
}
#define ibv_poll_cq(...)              _ibv_poll_cq(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_post_send(const char *f, int l,
                                 struct ibv_qp *qp, struct ibv_send_wr *wr,
                                 struct ibv_send_wr **bad_wr)
{
  auto ret = ibv_post_send(qp, wr, bad_wr);

  ibdbg_ldout << " qp: " << qp <<
    std::hex << std::showbase <<
    " wr_id: " << wr->wr_id <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_post_send(...)            _ibv_post_send(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_post_srq_recv(const char *f, int l,
                                     struct ibv_srq *srq,
                                     struct ibv_recv_wr *recv_wr,
                                     struct ibv_recv_wr **bad_recv_wr)
{
  auto ret = ibv_post_srq_recv(srq, recv_wr, bad_recv_wr);

  static struct ibv_srq *last_srq = nullptr;
  if (last_srq != srq) {
    ibdbg_ldout << " srq: " << srq <<
      " | ret: " << ret << dendl;
    last_srq = srq;
  }

  return ret;
}
#define ibv_post_srq_recv(...)        _ibv_post_srq_recv(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_query_device(const char *f, int l,
                                    struct ibv_context *context,
                                    struct ibv_device_attr *device_attr)
{
  auto ret = ibv_query_device(context, device_attr);

  ibdbg_ldout << " context: " << context <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_query_device(...)         _ibv_query_device(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_query_gid(const char *f, int l,
                                 struct ibv_context *context, int port_num,
                                 int index, union ibv_gid *gid)
{
  auto ret = ibv_query_gid(context, port_num, index, gid);

  ibdbg_ldout << " context: " << context << " port_num: " << port_num << " index: " << index <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_query_gid(...)            _ibv_query_gid(__func__, __LINE__, __VA_ARGS__)

static inline int ____ibv_query_port(const char *f, int l,
                                     struct ibv_context *context,
                                     int port_num,
                                     struct ibv_port_attr *port_attr)
{
  auto ret = ___ibv_query_port(context, port_num, port_attr);

  ibdbg_ldout << " context: " << context << " port_num: " << port_num <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ___ibv_query_port(...)        ____ibv_query_port(__func__, __LINE__, __VA_ARGS__)

#if 0
static inline int _ibv_query_qp(const char *f, int l,
                                struct ibv_qp *qp, struct ibv_qp_attr *attr,
                                int attr_mask,
                                struct ibv_qp_init_attr *init_attr)
{
  auto ret = ibv_create_srq(pd, srq_init_attr);
  
  ibdbg_ldout <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_query_qp(...)             _ibv_query_qp(__func__, __LINE__, __VA_ARGS__)

static inline struct ibv_mr *_ibv_reg_mr(const char *f, int l,
                                         struct ibv_pd *pd, void *addr,
                                         size_t length, int access)
{
  auto ret = ibv_create_srq(pd, srq_init_attr);
  
  ibdbg_ldout <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_reg_mr(...)               _ibv_reg_mr(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_dereg_mr(const char *f, int l,
                                struct ibv_mr *mr)
{
  auto ret = ibv_create_srq(pd, srq_init_attr);
  
  ibdbg_ldout <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_dereg_mr(...)             _ibv_dereg_mr(__func__, __LINE__, __VA_ARGS__)

#endif

static inline int _ibv_req_notify_cq(const char *f, int l,
                                     struct ibv_cq *cq, int solicited_only)
{
  auto ret = ibv_req_notify_cq(cq, solicited_only);

  ibdbg_ldout << " cq: " << cq << " solicited_only: " << solicited_only <<
    " | ret: " << ret << dendl;

  return ret;
}
#define ibv_req_notify_cq(...)        _ibv_req_notify_cq(__func__, __LINE__, __VA_ARGS__)

static inline int _ibv_get_async_event(const char *f, int l,
                                       struct ibv_context *context,
                                       struct ibv_async_event *event)
{
  auto ret = ibv_get_async_event(context, event);

  ibdbg_ldout << " context: " << context <<
    " | event: " << event << " ret: " << ret << dendl;

  return ret;
}
#define ibv_get_async_event(...)        _ibv_get_async_event(__func__, __LINE__, __VA_ARGS__)

static inline void _ibv_ack_async_event(const char *f, int l,
                                        struct ibv_async_event *event)
{
  ibdbg_ldout << " event: " << event << dendl;

  ibv_ack_async_event(event);
}
#define ibv_ack_async_event(...)        _ibv_ack_async_event(__func__, __LINE__, __VA_ARGS__)

static inline struct rdma_event_channel *_rdma_create_event_channel(const char *f, int l)
{
  auto ret = rdma_create_event_channel();

  ibdbg_ldout << " channel: " << ret << dendl;

  return ret;
}
#define rdma_create_event_channel(...)  _rdma_create_event_channel(__func__, __LINE__)

static inline int _rdma_create_id(const char *f, int l,
                                   struct rdma_event_channel *channel,
                                   struct rdma_cm_id **id, void *context,
                                   enum rdma_port_space ps)
{
  auto ret = rdma_create_id(channel, id, context, ps);

  ibdbg_ldout << " ret: " << ret << " id: " << *id << dendl;

  return ret;
}
#define rdma_create_id(...)             _rdma_create_id(__func__, __LINE__, __VA_ARGS__)


static inline int _rdma_create_qp(const char *f, int l,
                                   struct rdma_cm_id *id, struct ibv_pd *pd,
                                   struct ibv_qp_init_attr *qp_init_attr)
{
  auto ret = rdma_create_qp(id, pd, qp_init_attr);

  ibdbg_ldout << " id: " << id <<
    " pd: " << pd <<
    " send_cq: " << qp_init_attr->send_cq <<
    " recv_cq: " << qp_init_attr->recv_cq <<
    " srq: " << qp_init_attr->srq <<
    " | ret: " << ret << dendl;

  return ret;
}
#define rdma_create_qp(...)             _rdma_create_qp(__func__, __LINE__, __VA_ARGS__)


static inline void _rdma_destroy_qp(const char *f, int l,
                                   struct rdma_cm_id *id)
{
  ibdbg_ldout << " id: " << id << dendl;

  rdma_destroy_qp(id);
}
#define rdma_destroy_qp(...)        _rdma_destroy_qp(__func__, __LINE__, __VA_ARGS__)


#if 0
static inline int _rdma_create_srq(const char *f, int l,
                                   struct rdma_cm_id *id, struct ibv_pd *pd,
                                   struct ibv_srq_init_attr *attr)
{
  auto ret = rdma_create_srq(id, pd, attr);

  ibdbg_ldout << " id: " << id  <<
    " pd: " << pd <<
    " | srq: " << ret << dendl;

  return ret;
}
#define rdma_create_srq(...)            _rdma_create_srq(__func__, __LINE__, __VA_ARGS__)
#endif

static inline void _rdma_freeaddrinfo(const char *f, int l,
                                     struct rdma_addrinfo *res)
{
  ibdbg_ldout << " dst: " << res->ai_dst_addr << dendl;

  rdma_freeaddrinfo(res);
}
#define rdma_freeaddrinfo(...)          _rdma_freeaddrinfo(__func__, __LINE__, __VA_ARGS__)


static inline void _rdma_destroy_event_channel(const char *f, int l,
                                              struct rdma_event_channel *channel)
{
  ibdbg_ldout << " channel: " << channel << dendl;

  rdma_destroy_event_channel(channel);
}
#define rdma_destroy_event_channel(...)        _rdma_destroy_event_channel(__func__, __LINE__, __VA_ARGS__)


static inline int _rdma_destroy_id(const char *f, int l,
                                   struct rdma_cm_id *id)
{
  auto ret = rdma_destroy_id(id);

  ibdbg_ldout << " id: " << id  <<
    " | ret: " << ret << dendl;

  return ret;
}
#define rdma_destroy_id(...)        _rdma_destroy_id(__func__, __LINE__, __VA_ARGS__)


static inline int _rdma_disconnect(const char *f, int l,
                                    struct rdma_cm_id *id)
{
  auto ret = rdma_disconnect(id);

  ibdbg_ldout << " id: " << id  <<
    " | ret: " << ret << dendl;

  return ret;
}
#define rdma_disconnect(...)        _rdma_disconnect(__func__, __LINE__, __VA_ARGS__)


static inline int _rdma_getaddrinfo(const char *f, int l,
                                     char *node, char *service,
                                     struct rdma_addrinfo *hints,
                                     struct rdma_addrinfo **res)
{
  auto ret = rdma_getaddrinfo(node, service, hints, res);

  ibdbg_ldout <<
        " | ret: " << ret << dendl;

  return ret;
}
#define rdma_getaddrinfo(...)        _rdma_getaddrinfo(__func__, __LINE__, __VA_ARGS__)


static inline int _rdma_resolve_addr(const char *f, int l,
                                      struct rdma_cm_id *id, struct sockaddr *src_addr,
                                      struct sockaddr *dst_addr, int timeout_ms)
{
  auto ret = rdma_resolve_addr(id, src_addr, dst_addr, timeout_ms);

  ibdbg_ldout << " id: " << id  <<
    " dst: " << dst_addr <<
    " | ret: " << ret << dendl;

  return ret;
}
#define rdma_resolve_addr(...)        _rdma_resolve_addr(__func__, __LINE__, __VA_ARGS__)


static inline int _rdma_get_cm_event(const char *f, int l,
                                      struct rdma_event_channel *channel,
                                      struct rdma_cm_event **event)
{
  auto ret = rdma_get_cm_event(channel, event);

  ibdbg_ldout << " channel: " << channel  <<
        " | ret: " << ret << dendl;

  return ret;
}
#define rdma_get_cm_event(...)        _rdma_get_cm_event(__func__, __LINE__, __VA_ARGS__)


static inline int _rdma_resolve_route(const char *f, int l,
                                       struct rdma_cm_id *id, int timeout_ms)
{
  auto ret = rdma_resolve_route(id, timeout_ms);

  ibdbg_ldout << " id: " << id  <<
        " | ret: " << ret << dendl;

  return ret;
}
#define rdma_resolve_route(...)        _rdma_resolve_route(__func__, __LINE__, __VA_ARGS__)


static inline int _rdma_connect(const char *f, int l,
                                 struct rdma_cm_id *id, struct rdma_conn_param *conn_param)
{
  auto ret = rdma_connect(id, conn_param);

  ibdbg_ldout << " id: " << id  <<
        " | ret: " << ret << dendl;

  return ret;
}
#define rdma_connect(...)        _rdma_connect(__func__, __LINE__, __VA_ARGS__)


static inline int _rdma_accept(const char *f, int l,
                                struct rdma_cm_id *id, struct rdma_conn_param *conn_param)
{
  auto ret = rdma_accept(id, conn_param);

  ibdbg_ldout << " id: " << id  <<
        " | ret: " << ret << dendl;

  return ret;
}
#define rdma_accept(...)        _rdma_accept(__func__, __LINE__, __VA_ARGS__)


static inline int _rdma_ack_cm_event(const char *f, int l,
                                      struct rdma_cm_event *event)
{
  auto ret = rdma_ack_cm_event(event);

  ibdbg_ldout << " event: " << event  <<
        " | ret: " << ret << dendl;

  return ret;
}
#define rdma_ack_cm_event(...)        _rdma_ack_cm_event(__func__, __LINE__, __VA_ARGS__)

static inline int _rdma_migrate_id(const char *f, int l,
				  struct rdma_cm_id *id, struct rdma_event_channel *channel)
{
  auto ret = rdma_migrate_id(id, channel);

  ibdbg_ldout << " id: " << id  << " channel: " << channel <<
        " | ret: " << ret << dendl;

  return ret;
}
#define rdma_migrate_id(...)        _rdma_migrate_id(__func__, __LINE__, __VA_ARGS__)

static inline int _rdma_bind_addr(const char *f, int l,
				  struct rdma_cm_id *id, struct sockaddr *addr)
{
  auto ret = rdma_bind_addr(id, addr);

  ibdbg_ldout << " id: " << id  << " addr: " << addr <<
        " | ret: " << ret << dendl;

  return ret;
}
#define rdma_bind_addr(...)        _rdma_bind_addr(__func__, __LINE__, __VA_ARGS__)

#endif // __IB_DBG_H__
