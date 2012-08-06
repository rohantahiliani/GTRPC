#include <unistd.h>
#include <sys/select.h>
#include <curl/curl.h>
#include <stdio.h>
#include "proxy.h"

#define MAX_CACHE 1024*1024*50
#define CACHE_SIZE 1024

struct node{
	char url[100];
	int count;
	int index;
}n[CACHE_SIZE];

static wd_in w[CACHE_SIZE];
static int cur_size;
static int w_index;
