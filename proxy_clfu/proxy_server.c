#include "lfu.h"

static size_t write_data(void *buffer, size_t size, 
                         size_t nmemb, void *userp) {
	struct wd_in *wdi = userp;
	wdi->data = realloc(wdi->data, wdi->len + (size*nmemb));
	memcpy(wdi->data + wdi->len, buffer, size * nmemb);
	wdi->len+=size*nmemb;
	return size * nmemb;
}

void copy_result(wd_in *src, wd_in *dest){
	dest->data=src->data;
	dest->len=src->len;
}

void print_cache(){
	int i=-1;
	while(++i<CACHE_SIZE) if(n[i].count>0) printf("%d %d %s\n",i,n[i].count,n[i].url);
}

void list_insert(int ind){
	n[ind].ln.count=1;
	n[ind].ln.index=ind;
	if(ll.head==NULL){
		ll.head=&n[ind].ln;
		ll.tail=&n[ind].ln;
		n[ind].ln.next=NULL;
		n[ind].ln.prev=NULL;
	}
	else{
		ll.tail->next=&n[ind].ln;
		n[ind].ln.prev=ll.tail;
		n[ind].ln.next=NULL;
		ll.tail=&n[ind].ln;
	}
}

int list_remove(){
	lnode* p=ll.head;
	ll.head=p->next;
	if(ll.head!=NULL) ll.head->prev=NULL;
	return p->index;
}

void cache_insert(char *u, wd_in *result){
	int a;
	if((cur_size+result->len) > MAX_CACHE){
		while(cur_size+result->len > MAX_CACHE){
			a=list_remove();
			printf("Cache size exceeded. Evicting %s with count %d and size %u\n",n[a].url,n[a].count,n[a].w.len);fflush(stdout);
			if(a>=0){
				strcpy(n[a].url,"");
				n[a].count=0;
				cur_size-=n[a].w.len;
				free(n[a].w.data);
			}
		}
	}
	a=strlen(u)%CACHE_SIZE;
	if(n[a].count!=0) do{a=(a*5)%CACHE_SIZE;}while(n[a].count!=0); 
	n[a].count=1;
	list_insert(a);
	cur_size+=result->len;
	strcpy(n[a].url,u);
	n[a].w.data=malloc(result->len);
	copy_result(result,&n[a].w);
	//printf("%s %d\nPrinted\n",n[a].url,n[a].w.len);fflush(stdout);
}

int cache_find(char *u, wd_in *result){
	int a;
	a=strlen(u)%CACHE_SIZE;
	if(strcmp(n[a].url,u)!=0) do{a=(a*5)%CACHE_SIZE;}while(n[a].count!=0 && strcmp(n[a].url,u)!=0); 
	if(n[a].count==0) return 0;
	n[a].count++;
	n[a].ln.count++;
	lnode *p=&n[a].ln.next;
	while(p!=NULL && p->count < n[a].ln.count) p=p->next;
	if(p!=NULL && p->index!=n[a].ln.index){
		if(n[a].ln.prev!=NULL){
			n[a].ln.prev->next=n[a].ln.next;
			n[a].ln.next->prev=n[a].ln.prev;
		}
		if(p->prev!=NULL) {
			n[a].ln.prev=p->prev;
			n[a].ln.prev->next=&n[a].ln;
		}
		n[a].ln.next=p;
		p->prev=&n[a].ln;
	}
	copy_result(&n[a].w,result);
	printf("%s CACHE HIT at %d\n",u,a);fflush(stdout);
	return 1;
}

bool_t curl_op(char **arg, wd_in *result){
	CURL *curl;
	CURLcode res;
	wd_in wdi;
	char *url = arg[0];
	memset(&wdi, 0, sizeof(wdi));
	curl = curl_easy_init();
	if(NULL != curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &wdi);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		copy_result(&wdi,result);
		cache_insert(url, &wdi);
		return 1;
	}
	else {
		fprintf(stderr, "Error: could not get CURL handle.\n");
		return 0;
	}
}

bool_t
fetchpage_1_svc(char **argp, wd_in *result, struct svc_req *rqstp)
{
	static bool_t retval;
	memset(result,0,sizeof(*result));
	if(!(retval=cache_find(argp[0],result))) retval=curl_op(argp,result);
	if(strcmp(argp[0],"rohant.in")==0) print_cache();
	printf("CACHE SIZE %lu\n",cur_size);fflush(stdout);
	return retval;
}

int
proxyserver_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	/*xdr_free (xdr_result, result);*/

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}
