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
#include "main.h"

time_t curr;

//used to measure job time
void pushJobTimeUsed(double target){
  metric.timeOnJobs += target;
}

//used to set min max times
void compareTimes(double target){
  if(target < metric.minTimeUsed){
    metric.minTimeUsed = target;
  }
  if(target > metric.maxTimeUsed){
    metric.maxTimeUsed = target;
  }
  pushJobTimeUsed(target);
}

//used to get the start time of the benchmark
void postStartTime(){
  metric.startTime = clock();
}

//used to get the end time of the benchmarl
void postEndTime(){
  metric.endTime = clock();
}

//get start time
int getStartTime(){
  curr = clock();
  return t;
}

//get total time used
double getTimeUsed(){
  curr = clock() - curr;
  double endTime = ((double)curr)/CLOCKS_PER_SEC;
  return endTime;
}



