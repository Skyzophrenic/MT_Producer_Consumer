#ifndef SCHEDULER_H
#define SCHEDULER_H



void queueForPrio(queue *q, node *n);
void queueForShortest(queue *q, node *n);
void sortPriority(queue *q);
void sortShortest(queue *q);
void sortFCFS(queue *q);
void changeQueueType(int type);
void doCurrentSort(queue* q);
void *producer(void *pno);
void commandParser();

#endif