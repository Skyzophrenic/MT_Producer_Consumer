#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>


#include "structures.h"
#include "help.h"
#include "dispatcher.h"

#include "scheduler.h"
#include "evaluation.h"
#include "main.h"

//previously used to provide a job place holder in differing dev environments
/*
void fakeJobPlaceHolder(){
  int counter = 0;
  int counter2 = 0;
  int counter3 = 0;
  while(counter <= 10000000){
    while(counter2 <= 10000000){
      while(counter3 <= 10000000){
    counter3++;
  }
    counter2++;
  }
    counter++;
  }

}*/


//function to be called on consumer thread
void *consumer(void *cno)
{   
  while(doLoop){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        if(buffer[outb] != NULL){
          
    
          target = buffer[outb];
          //printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item->cpuTime,   outb);
          pid_t parent = getpid();
          pid_t pid = fork();

          if (pid == -1)
          {
          // error, failed to fork()
          } 
          else if (pid > 0)
          {
          //parent wait
          int status;
          t = clock();
          waitpid(pid, &status, 0);
          //fakeJobPlaceHolder();
          metric.numberSortedWith += 1;
          t = clock() -t;
          double time_taken  = (((double)t)/CLOCKS_PER_SEC)*10000;
          compareTimes(time_taken);
          }
          else {
    // we are the child
          char binaryPath[] = "./";
          strcat(binaryPath, target->name);
          char *args[] = {binaryPath, NULL};
          int errorCode = execv(binaryPath, args); 
          _exit(EXIT_FAILURE);   // exec never returns
          }


        if(activeBM == 1 && queueIsEmpty(&benchmarkQueue)){
          postEndTime();
          activeBM = 0;
          printBenchmark();
        }



          outb = (outb+1)%BufferSize;
          buffer[outb] = NULL;
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1);
    }
    postEndTime();
    oaPrintBenchmark();
    return 0;

}


/*
t = clock();
        
        pid_t parent = getpid();
        pid_t pid = fork();

        if (pid == -1)
        {
          // error, failed to fork()
        } 
        else if (pid > 0)
        {
          //parent wait
          int status;
          waitpid(pid, &status, 0);
          //fakeJobPlaceHolder();
        metric.numberSortedWith += 1;
        
        t = clock() -t;
        double time_taken  = ((double)t)/CLOCKS_PER_SEC;

        compareTimes(time_taken);
        }
        else 
{
    // we are the child
        char binaryPath[] = "./";
        strcat(binaryPath, target->name);
    
        char *args[] = {binaryPath, NULL};
 
        int errorCode = execv(binaryPath, args); 
        _exit(EXIT_FAILURE);   // exec never returns
}



        pthread_mutex_unlock(&mutex);
        sleep(1);
  
     }
     if(activeBM == 1 && queueIsEmpty(&benchmarkQueue)){
  
       postEndTime();
       activeBM = 0;
       printBenchmark();

     }
     pthread_mutex_unlock(&mutex);
        
    }}
    postEndTime();
    oaPrintBenchmark();

*/