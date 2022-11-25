/*
      Jordan Slonaker, Giovanni Thompson, Stephen Lee
      Software Engineering Project 1
      Due Date: October 3rd
*/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "structures.h"
#include "help.h"

#include "scheduler.h"
#include "dispatcher.h"
#include "benchmark.h"
#include "main.h"
#include "list.h"

// a large basis for my re-studying of these concepts came from this article:
// https://shivammitra.com/c/producer-consumer-problem-in-c/#


void changeModule(){
  printf("***** Sample change\n");
}

//used to quit the application, ending both loops in scheduler / dispatcher threads
void quit(){
  doLoop = 0;
}

//used to get estimated wait time when inputting a node
int getEstimatedWait(queue *q, node *n){
  node* nnPtr = q->head;
  int estimate = 0;
  while(nnPtr != NULL && nnPtr != n){
    estimate+=nnPtr->cpuTime;
    nnPtr = nnPtr->next;
  }
  return estimate;
}

//used to allow the user to input single job nodes
void run(char* jobName, int cpuTime, int prio){
  node n = enqueue(&benchmarkQueue, jobName, cpuTime, prio);
  doCurrentSort(&benchmarkQueue);
  printf("Job %s was submitted\n", jobName);
  printf("Estimated wait time: %d\n", getEstimatedWait(&benchmarkQueue, &n));
  //0 FCFS, 1 SJF, 2 Prio
  printf("Current Policy: %d\n", currQueueType);
}




// MAIN, entrance point for application
int main()
{   
  //set up metrics
  inb = 0;
  outb = 0;
  doLoop = 1;
  metric.minTimeUsed = 999;
  time_t myTime = time(NULL);
  char * time_str = ctime(&myTime);
  time_str[strlen(time_str)-1] = '\0';


  sem_init(&empty,0,BufferSize);
  sem_init(&full,0,0);

  //initialize queues
  init_queue(&benchmarkQueue);



  strcpy(metrics[0].evalType, "FCFS");
  strcpy(metrics[1].evalType, "SJF");
  strcpy(metrics[2].evalType, "Prio");

  printf("Welcome to CSU Batch\n");

    pthread_t pro,con, com; //creating producer and consumer threads


    pthread_mutex_init(&mutex, NULL); //creating mutex
 

    pthread_cond_t locked;
    int a = 1; //Just used for numbering the producer and consumer


  

    //thread initialization
    pthread_create(&com, NULL, (void *)commandParser, (void *)&a);
    pthread_create(&pro, NULL, (void *)producer, (void *)&a);
    pthread_create(&con, NULL, (void *)consumer, (void *)&a);

    //join threads once tasks are completed
    pthread_join(com, NULL);
    pthread_join(pro, NULL);
    pthread_join(con, NULL);


    //mutex / semaphore cleanups
    pthread_mutex_destroy(&mutex);



    return 0;
    
}