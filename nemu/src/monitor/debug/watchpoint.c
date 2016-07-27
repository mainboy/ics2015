#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;
static int cur=0;

void init_wp_pool() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_pool[i].NO = i;
		wp_pool[i].next = &wp_pool[i + 1];
	}
	wp_pool[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
WP* new_wp() {
	cur++;
	if (cur >= NR_WP) {
		assert(0);
	}
	WP *p=head;
	if (NULL == p) {
		head = free_;
		free_ = free_->next;
		head->next = NULL;
		p = head;
	} else {
		while(p->next!=NULL){
			p = p->next;
		}
		p->next = free_;
		free_ = free_->next;
		p = p->next;
		p->next = NULL;
	}
	return p;
}

void free_wp(WP *wp) {
	WP *p=head, *prev=NULL, *temp=NULL;
	while(p->NO != wp->NO) {
		prev = p;
		p = p->next;
	}
	if(NULL == prev) {
		head->next = free_;
		free_ = head;
		head = NULL;
	}else {
		temp = p->next;
		prev->next = p->next;
		p->next = free_;
		free_ = temp;
	}

}

void print_wp() {
	WP *p=head;
	printf("Num         Type         What\n");
	while(NULL != p){
		printf("%d        hw watchpoint     %s\n",p->NO, p->str);
		p=p->next;
	}

}

bool check_wp() {
	WP *p=head;
	bool success;
	while(NULL != p){
		if(expr(p->str,&success) != p->val)
			return true;
		p=p->next;
	}
	return false;
}

