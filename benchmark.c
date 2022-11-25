
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
#include "evaluation.h"
#include "main.h"



/*"test    |   test <benchmark_name> <numJobs> <numPrios> <minTime> <maxTime>  |create a benchmark to test a queue type\n",*/
//used to allow the user to input benchmarks with the test command
void doBenchmark(char name[], char sortType[], int numJobs, int numPrios, int minTime, int maxTime ){
  currentQueue = &benchmarkQueue;
  postStartTime();
  printf("@@@@@@@@@@@@@@@ BENCHMARK INFO @@@@@@@@@@@@@@@@\n");
  printf("Benchmark name: %s\n", name);
  printf("Queue Type: %s\n", sortType);
  printf("Num jobs: %d\n", numJobs);
  printf("Min time: %d\n", minTime);
  printf("Max time: %d\n", maxTime);
  int counter = 0;
  int thisJobTime = 0;
  int thisJobPrio = 0;
  while(counter < numJobs){

    thisJobTime = (rand() % (maxTime - minTime + 1)) + minTime;
    thisJobPrio = (rand() % (numPrios - 0+1)) + 1;

    counter++;
    enqueue(&benchmarkQueue, "job1", thisJobTime, thisJobPrio);
  }

  if(strcmp("fcfs", sortType) == 0){
    changeQueueType(0);
  }
  if((strcmp("prio", sortType) == 0) || (strcmp("priority", sortType) == 0)){
    changeQueueType(2);
  }
  if(strcmp("sjf", sortType) == 0){
    changeQueueType(1);
  }
  activeBM = 1;
  doCurrentSort(&benchmarkQueue);

}