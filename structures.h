#ifndef STRUCTURES_H
#define STRUCTURES_H


typedef struct node{
  //Job job;
  struct node *next;
  char name[20];
  int priority;
  int cpuTime;
  char timeSubmitted[50];
} node, *nodepointer;

typedef struct{
  node *head;
  node *tail;
} queue, *queuepointer;


typedef struct{
  char evalType[10];
  int numberSortedWith;
  int totalNumberSortedWith;
  float startTime;
  float timeUsed;
  float averageWaitingTime;
  float maxTimeUsed;
  float minTimeUsed;
  float oaMaxTimeUsed;
  float oaMinTimeUsed;
  float oaTimeUsed;
  float endTime;
  float timeOnJobs;
  float oaTimeOnJobs;

} performanceMetric;
performanceMetric metrics[3];
performanceMetric metric;




queuepointer init_queue(queue*);
int queueIsEmpty(queue*);
void printJobInfo(node n);
node enqueue(queue *q, char name[], int time, int prio);
node enqueueNode(queue *q, node *n);
node* dequeue(queue *q);
void printQueue(queue *q);
void printBenchmark();
void cleanMetric();
void oaPrintBenchmark();
void pushToOA();



#endif