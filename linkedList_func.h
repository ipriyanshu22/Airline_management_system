#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	struct flight fl;

	struct Node* next;

} node;

typedef node linkedList;

node* create()
{
	node* hd;
	hd=(linkedList*)malloc(sizeof(linkedList));
	hd->next = NULL;
	return hd;
}

void ins_end(struct flight fl, node* hd)
{
	node* t;
	t=hd;
	// if(t->next == NULL)
	// {
	// 	node* new1=(node*)malloc(sizeof(node));
	// 	new1->flight.details=fl.details;
	// 	new1->flight.flight_date=fl.flight_date;
	// 	new1->next=NULL;
	// 	t->next=new1;
	// 	return;
	// }
	while(t->next!=NULL)
	{
		t=t->next;
	}

	node* new1=(node*)malloc(sizeof(node));
	new1->fl.details=fl.details;
	new1->fl.flight_date=fl.flight_date;
	new1->next=NULL;
	t->next=new1;
}