#ifndef MAIN_H
#define MAIN_H



#define MaxItems 1 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 // Size of the buffer

int inb;
int outb;

sem_t empty;
sem_t full;

node* buffer[BufferSize];

void doCurrentSort();
void changeQueueType();
pthread_mutex_t mutex;
queue benchmarkQueue;
int doLoop;
int activeBM;
queue* currentQueue;
queue fakeQueue;


int currQueueType; //0 FCFS, 1 SJF, 2 Prio

typedef struct{
  char name[20];
  int numJobs;
  int numPrios;
  int minTime;
  int maxTime;
}benchmarkInformation;

void run(char* jobName, int cpuTime, int prio);

void listModule();
void changeModule();
void quit();
int getQueueSize(queue *q);
clock_t t;




#endif