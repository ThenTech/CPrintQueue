#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>

///*
//*	Maximum length of a string.
//*/
//#define MAX_STRING	50

/*
*	Default data type.
*/
typedef void* DATA;

/*
*	Default print types.
*/
typedef enum PRINTENUM { STRING, INT, FLOAT } TYPE;

/*
*	Default list element.
*/
typedef struct NODE{
	DATA value;
	TYPE type;
	struct NODE *next;
} NODE;

/*
*	A link/pointer to a specified node in the list.
*/
typedef NODE *LINK;


/*-------------------------------------------------------------------------------------------
*################################ Linked List Functions #####################################
*--------------------------------------------------------------------------------------------
/*
*	Delete the element after from.
*/
void deleteNext(LINK from) {
	LINK delete = from->next;
	from->next = from->next->next;
	free(delete);
}

/*
*	Clear the entire list.
*/
void clear(LINK *from) {
	while ((*from)->next != NULL) deleteNext(*from);
	*from = NULL;
}

/*-------------------------------------------------------------------------------------------
*##################################### Queue Functions ######################################
*--------------------------------------------------------------------------------------------
*/
/*
*	Struct representing a queue, with its head and tail.
*/
typedef struct queue {
	LINK front;
	LINK back;
} QUEUE;

/*
*	Return whether the queue is empty.
*/
int isEmptyQueue(QUEUE top) {
	return top.front == NULL;
}

/*
*	Clear the entire queue.
*/
void clearQ(QUEUE *q) {
	clear(&(*q).front);
	(*q).front = (*q).back = NULL;
}

/*
*	Return the first element's data
*/
LINK peek(QUEUE q) {
	return q.front;
}

/*
*	Return the top element 's data and remove it from the queue.
*/
LINK poll(QUEUE *q) {
	if (isEmptyQueue(*q)) {
		printf("\n[ERROR] poll : nullreference!");
		return (LINK)NULL;
	} else {
		LINK tmp = q->front;
		DATA d = tmp->value;
		q->front = tmp->next;
		//free(tmp); return d;	//-> if DATA returned instead of LINK
		return tmp;
	}
}

/*
*	ADD element's data
*/
void add(QUEUE *q, TYPE t, DATA d) {
	LINK tmp = malloc(sizeof(NODE));

	tmp->type = t;
	switch (t) {
		case STRING:
			tmp->value = malloc(strlen(d) * sizeof(char));	// MAX_STRING
			strcpy(tmp->value, d);
			break;
		case INT:
			//tmp->value = malloc(sizeof(int));	// necessary?
			tmp->value = d;
			break;
		case FLOAT:
			//tmp->value = malloc(sizeof(double));	// necessary?
			tmp->value = d;
			break;
		default:
			printf("[ERROR] add : Type unknow! Skipped.");
			break;
	}

	tmp->next = NULL;

	if (isEmptyQueue(*q)) {
		q->front = q->back = tmp;
	} else {
		q->back->next = tmp;
		q->back = tmp;
	}
}

/*
*	Generate a list of strings of size elements.
*/
void fillQueue(QUEUE *q, TYPE t, size_t elements) {
	for (size_t i = 0; i < elements; i++) {
		if (t == STRING) {
			char *s = malloc(12 * sizeof(char));	// MAX_STRING = 50
			sprintf(s, "String %d", i);
			add(q, t, s);
		} else {
			add(q, t, i);
		}
	}
}

/*
*	Helper for printListRecurCnt() to include count and print actual data.
*	Call with: printQueueNode( <headpointer>, <startcount>)
*/
void printQueueNode(LINK head, size_t cnt) {
	switch (head->type) {
		case STRING:
			printf("element %2d :: value = %s\n", cnt, head->value);
			break;
		case INT:
			printf("element %2d :: value = %d\n", cnt, *(int *) &head->value);	// evil floating point bit level hacking
			break;
		case FLOAT:
			printf("element %2d :: value = %f\n", cnt, *(double *) head->value);	// evil floating point bit level hacking (w/o extra pointer since its already a pointer)
			break;
		default:
			printf("[ERROR] printQueueNode : Type unknow!");
			break;
	}
}

/*
*	Helper for printQueueRecur() to include count.
*	Call with: printListRecurCnt( <headpointer>, <startcount>)
*/
void printListRecurCnt(LINK head, size_t cnt) {
	if (head != NULL) {
		printQueueNode(head, cnt);
		printListRecurCnt(head->next, ++cnt);
	}
}

/*
*	Recursively print the elements in the list starting from head pointer.
*	Calls printListRecurCnt() to include the count.
*/
void printQueueRecur(QUEUE q) {
	if (q.front != NULL)	printListRecurCnt(q.front, 0);
	else					printf("\n[ERROR] printQueueRecur : HEAD pointer is NULL, Queue empty!");
}

void printQueuePoll(QUEUE *q) {
	printQueueNode(q->front, 0);
	poll(q);
}
