
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "help.h"
#include "structures.h"
#include "main.h"
//used to hold help display data
const char *helpData[] = {
  "COMMAND |   Parameters/Usage                                                |Information   \n",
  "change  |   change <queue_type(fcfs/prio/sjf)>                              |change the queue type to a designated target\n",
  "fcfs    |   fcfs                                                            |sorts job queue in the order of first arrival\n",
  "prio    |   prio                                                            |sorts job queue in the order of priority (ascending)\n",
  "sjf     |   sjf                                                             |sorts job queue in the order of estimated job time\n",
  "help    |   help (optional: <command_alias>)                                |displays the help menu / displays information about targeted command\n",
  "list    |   list                                                            |display current job queue\n",
  "quit    |   quit                                                            |exit the program\n",
  "run     |   run <job_name> <est_time> <priority>                            |send a job to the queque and re-sort accordingly\n",
  "test    |   test <benchmark_name> <sort_type> <numJobs> <numPrios> <minTime> <maxTime>  |create a benchmark to test a queue type\n",
  NULL
};

//displays every point in the helpdata holder
void helpModules(){
  
  int pntr = 0;
  while(helpData[pntr] != NULL){
    printf("%s\n", helpData[pntr]);

    pntr+=1;
  }
}

//shows a single point in the help data holder
void helpModule(char *param){
  printf("***** Sample help\n");
  printf("%s\n", param);
  if(strcmp("change\n", param) == 0){
    printf("%s\n", helpData[1]);
  }
  if(strcmp("fcfs\n", param) == 0){
    printf("%s\n", helpData[2]);
  }
  if(strcmp("prio\n", param) == 0){
    printf("%s\n", helpData[3]);
  }
  if(strcmp("sjf\n", param) == 0){
    printf("%s\n", helpData[4]);
  }
  if(strcmp("help\n", param) == 0){
    printf("%s\n", helpData[5]);
  }
  if(strcmp("help\n", param) == 0){
    printf("%s\n", helpData[5]);
  }
  if(strcmp("list\n", param) == 0){
    printf("%s\n", helpData[6]);
  }
  if(strcmp("quit\n", param) == 0){
    printf("%s\n", helpData[7]);
  }
  if(strcmp("run\n", param) == 0){
    printf("%s\n", helpData[8]);
  }
  if(strcmp("test\n", param) == 0){
    printf("%s\n", helpData[9]);
  }
}

