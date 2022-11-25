#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "structures.h"
#include "dispatcher.h"

//display the current queue, with statuses such as estimated time, prio, time submitted and status
void printQueue(queue *q){
  if(q->head != NULL){
printf("Print Queue: \n");
int counter = 0;
if(target != NULL){
printf("%d) %s %d %d %s running\n", counter, target->name, target->cpuTime, target->priority, target->timeSubmitted);
counter++;
}
node* nPtr = q->head;
  while(nPtr != NULL){
    printf("%d) %s %d %d %s waiting\n", counter, nPtr->name, nPtr->cpuTime, nPtr->priority, nPtr->timeSubmitted);
    counter++;
    nPtr = nPtr->next;
  }}else{printf("Queue was found to be empty\n");}
}