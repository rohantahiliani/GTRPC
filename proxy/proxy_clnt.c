/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "proxy.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat 
fetchpage_1(char **argp, wd_in *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, fetchPage,
		(xdrproc_t) xdr_wrapstring, (caddr_t) argp,
		(xdrproc_t) xdr_wd_in, (caddr_t) clnt_res,
		TIMEOUT));
}