#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "printqueue.h" 

int main(int argc, char *argv[]) {

	QUEUE q = {NULL, NULL};

	// Fill with test data
	//fillQueue(&q, STRING, 10);

	add(&q, STRING, "Test string");
	add(&q, STRING, "Another likewise");
	add(&q, INT, 123);
	add(&q, STRING, "<- before this one, an int");

	// Print all
	printQueueRecur(q);

	printf("\nFirst element: "); printQueueNode(peek(q), 0);

	// Remove first
	printf("\nRemove       : "); printQueueNode(poll(&q), 0);

	printf("\nFirst element: "); printQueueNode(peek(q), 0);
	putchar('\n');

	// Add new elements
	add(&q, STRING, "Yet another number!");
	double d = 3.141596;
	add(&q, FLOAT, &d);
	add(&q, STRING, "BuT tH15 t1me a DOUn|3");
	
	printQueueRecur(q);

	putchar('\n'); putchar('\n');

	// Print first and remove
	printQueuePoll(&q);
	printQueuePoll(&q);
	printQueuePoll(&q);

	// Print all
	putchar('\n'); putchar('\n'); putchar('\n');
	printQueueRecur(q);

	printf("\n");
	system("PAUSE");
	return 0;
}
