#include "proxy.h"

char * fetchpage_1_arg;

void
proxyserver_1(char *host)
{
	CLIENT *clnt;
	wd_in  *result_1;

#ifndef	DEBUG
	clnt = clnt_create (host, ProxyServer, ProxyV1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = fetchpage_1(&fetchpage_1_arg, result_1, clnt);
	if (result_1 == (wd_in *) NULL) clnt_perror (clnt, "call failed");
	else printf("%s",result_1->data);
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 3) {
		printf ("usage: %s server_host url\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	fetchpage_1_arg = argv[2];
	proxyserver_1 (host);
exit (0);
}
