/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _PROXY_H_RPCGEN
#define _PROXY_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif


struct wd_in {
	u_int size;
	u_int len;
	char *data;
};
typedef struct wd_in wd_in;

#define ProxyServer 99
#define ProxyV1 1

#if defined(__STDC__) || defined(__cplusplus)
#define fetchPage 1
extern  enum clnt_stat fetchpage_1(char **, wd_in *, CLIENT *);
extern  bool_t fetchpage_1_svc(char **, wd_in *, struct svc_req *);
extern int proxyserver_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define fetchPage 1
extern  enum clnt_stat fetchpage_1();
extern  bool_t fetchpage_1_svc();
extern int proxyserver_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_wd_in (XDR *, wd_in*);

#else /* K&R C */
extern bool_t xdr_wd_in ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_PROXY_H_RPCGEN */
