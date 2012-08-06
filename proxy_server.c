#include <unistd.h>
#include <sys/select.h>
#include <curl/curl.h>
#include <stdio.h>
#include "proxy.h"

static size_t write_data(void *buffer, size_t size, 
                         size_t nmemb, void *userp) {
	struct wd_in *wdi = userp;

	while(wdi->len + (size * nmemb) >= wdi->size) {
		wdi->data = realloc(wdi->data, wdi->size*2);
		wdi->size*=2;
	}

	memcpy(wdi->data + wdi->len, buffer, size * nmemb);
	wdi->len+=size*nmemb;

	return size * nmemb;
}

wd_in curl_op(char **arg){
	CURL *curl;
	CURLcode res;
	wd_in wdi;
	char *url = arg[0];

	memset(&wdi, 0, sizeof(wdi));
	curl = curl_easy_init();
	if(NULL != curl) {
		wdi.size = 1024;
		wdi.data = malloc(wdi.size);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &wdi);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		return wdi;
	}
	else {
		fprintf(stderr, "Error: could not get CURL handle.\n");
		return NULL;
	}
}

wd_in *
fetchpage_1_svc(char **argp, struct svc_req *rqstp)
{
	static wd_in result;
	result=curl_op(argp);
	/*
	 * insert server code here
	 */

	return &result;
}

