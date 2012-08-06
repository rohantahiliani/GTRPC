#include <unistd.h>
#include <sys/select.h>
#include <curl/curl.h>
#include <stdio.h>
#include "proxy.h"

#define MAX_CACHE 1024*1024*3
#define CACHE_SIZE 1024


struct lnode{
	int count;
	int index;
	struct lnode *next;
	struct lnode *prev;
};

struct node{
	char url[100];
	int count;
	wd_in w;
	struct lnode ln;
}n[CACHE_SIZE];


struct list{
	struct lnode *head;
	struct lnode *tail;
}ll;

static unsigned long int cur_size;
typedef struct node node;
typedef struct lnode lnode;
typedef struct list list;
