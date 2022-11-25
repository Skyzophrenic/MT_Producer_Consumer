#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


#include "structures.h"
//#include "main.h"



void printJobInfo(node n){
  printf("\n PRINTING JOB INFO `````````` \n"
  "Name: %s\n" 
  "Prio: %d\n" 
  "CompTime: %d\n"
  "Time Submitted: %s\n"
  "``````````````````\n", 
  n.name, 
  n.priority, 
  n.cpuTime,
  n.timeSubmitted);  
}

queuepointer init_queue(queue *q){
  q->head = NULL;
  q->tail = NULL;
  return q;
}

int queueIsEmpty(queue *q){
  return(q->head == NULL);
}


node enqueue(queue *q, char name[], int time, int prio){
  node * newnode = malloc(sizeof(node));
  strcpy(newnode->name, name);
  newnode->cpuTime = time;
  newnode->priority = prio;
  newnode->next = NULL;

  time_t t = time;
  char * time_str = ctime(&t);
  time_str[strlen(time_str)-1] = '\0';
  strcpy(newnode->timeSubmitted, time_str);
  

  if(q->tail != NULL){
    q->tail->next = newnode;
  }
  q->tail = newnode;
  if(q->head == NULL){
    q->head = newnode;
  }
  return *newnode;
}


node enqueueNode(queue *q, node *n){
  
  if(q->head == NULL){
    //printf("I am working on: %d\n", n->priority);
    q->head = n;
    q->tail = n;
    n->next = NULL;
    return *n;
  }
  if(q->tail != NULL){
    //printf("--I am working on: %d\n", n->priority);
    q->tail->next = n;
    q->tail = n;
    n->next = NULL;
  }
  //q->tail = n;
  return *n;
  
}

node* dequeue(queue *q){
  if(q->head == NULL){
     return q->head; /// make return null (or nothing) when learn how
  }
  node *tmp = q->head;
  //Job result = tmp->job;
  q->head = q->head->next;
  //char *retVal;
  //strcpy(retVal, tmp->name);
  if(q->head == NULL){
    q->tail = NULL;
  }
  //printJobInfo(*tmp);
  //free(tmp);
  return tmp;
}
/*
void printQueue(queue *q){
printf("Print Queue: \n");
  node* nPtr = q->head;
  int counter = 0;
  while(nPtr != NULL){
    printf("%d) %s %d %d\n", counter, nPtr->name, nPtr->cpuTime, nPtr->priority);
    counter++;
    nPtr = nPtr->next;
  }
}
*/
void pushToOA(){
  metric.totalNumberSortedWith += metric.numberSortedWith;
  metric.oaTimeUsed += metric.timeUsed;
  metric.oaTimeOnJobs += metric.timeOnJobs;
  if(metric.minTimeUsed < metric.oaMinTimeUsed){ metric.oaMinTimeUsed = metric.minTimeUsed;}
  if(metric.maxTimeUsed > metric.oaMaxTimeUsed){metric.oaMaxTimeUsed = metric.maxTimeUsed;}

}

void cleanMetric(){
  metric.numberSortedWith = 0;
  metric.timeUsed = 0;
  metric.minTimeUsed = 999;
  metric.maxTimeUsed = 0;
  metric.timeOnJobs = 0;
}

void printBenchmark(){
  double totalTime = ((metric.endTime - metric.startTime)/CLOCKS_PER_SEC) * 1000;
  double jobTime = ((metric.timeOnJobs));
  metric.timeUsed = totalTime;
  double tp = totalTime / metric.numberSortedWith;
  printf("Total Jobs Passed: %d\n", metric.numberSortedWith);
  printf("Total Time Used: %f\n", totalTime);
  printf("Time used on jobs: %f\n", metric.timeOnJobs);
  printf("Min Job Time: %f\n", metric.minTimeUsed);
  printf("Max Job Time: %f\n", metric.maxTimeUsed);
  printf("Throughput: %f per second\n", tp);
  printf("JTP: %f\n\n", metric.timeOnJobs / metric.numberSortedWith);
  pushToOA();
  cleanMetric();
}



void oaPrintBenchmark(){
  double tp = metric.oaTimeUsed / metric.totalNumberSortedWith;
  printf("Total Jobs Passed: %d\n", metric.totalNumberSortedWith);
  printf("Total Time Used: %f\n", metric.oaTimeUsed);
  printf("Min Job Time: %f\n", metric.oaMinTimeUsed);
  printf("Max Job Time: %f\n", metric.oaMaxTimeUsed);
  printf("Throughput: %f per second\n\n", tp);
}


