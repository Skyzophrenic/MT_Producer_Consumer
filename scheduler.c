#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "structures.h"
#include "help.h"

#include "main.h"
#include "scheduler.h"
#include "benchmark.h"


//used to resort the queue in priority
void queueForPrio(queue *q, node *n){
  n->next = NULL;
  if(q->head == NULL){
    q->head = n;
    q->tail = n;

    return;
  }

  if(q->head->priority > n->priority){ // special case: new best
    n->next = q->head;
    q->head = n;
    return;
  }
  node* temp = q->head;
  while(temp != NULL){ 
    if(temp->next == NULL){ //special case: end of queue
      temp->next = n;
      q->tail = n;
   
      return;
    }

    if((temp->priority <= n->priority) && (temp->next->priority >= n->priority)){
      n->next = temp->next;
      temp->next = n;
      return;
    }
    temp = temp->next;
  }
}

//used to resort the queue in sjf
void queueForShortest(queue *q, node *n){
  n->next = NULL;
  if(q->head == NULL){
    q->head = n;
    q->tail = n;
  
    return;
  }

  if(q->head->cpuTime > n->cpuTime){ // special case: new best
    n->next = q->head;
    q->head = n;
    return;
  }
  node* temp = q->head;
  while(temp != NULL){ 
    if(temp->next == NULL){ //special case: end of queue
      temp->next = n;
      q->tail = n;
      //printQueue(q);
      return;
    }

    if((temp->cpuTime <= n->cpuTime) && (temp->next->cpuTime >= n->cpuTime)){
      n->next = temp->next;
      temp->next = n;
      return;
    }
    
    temp = temp->next;
  }

  
}

//resorts the queue in priority
void sortPriority(queue *q){
  if(q->head == NULL){
    return;
  }
  while(q->head != NULL){
    enqueueNode(&fakeQueue, dequeue(q));
  }
  while(fakeQueue.head != NULL){
    queueForPrio(q, dequeue(&fakeQueue));
  }



}
//resorts the queue in sjf
void sortShortest(queue *q){
if(q->head == NULL){
    return;
  }
  while(q->head != NULL){
    enqueueNode(&fakeQueue, dequeue(q));
  }
  while(fakeQueue.head != NULL){
    queueForShortest(q, dequeue(&fakeQueue));
  }


}
//sorts the queue in fcfs
void sortFCFS(queue *q){

  if(q->head == NULL){
    return;
  }
  while(q->head != NULL){
    enqueueNode(&fakeQueue, dequeue(q));
  }
  while(fakeQueue.head != NULL){
    enqueueNode(q, dequeue(&fakeQueue));
  }

}


//assigns the current queue type for use 
void changeQueueType(int type){
  currQueueType = type;
}

//do a sort based on the "currQueueType" variable
void doCurrentSort(queue* q){
  if(currQueueType == 0){
    //fcfs
    sortFCFS(q);
  }
  if(currQueueType == 1){
    //sjf
    sortShortest(q);
  }
  if(currQueueType == 2){
    //prio
    sortPriority(q);
  }
}


//function to be called on producer thread
void *producer(void *pno)
{   
  node* item;
  
    while(doLoop) {
      //commandParser();
      
      if(!queueIsEmpty(&benchmarkQueue)){
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
      
        item = dequeue(&benchmarkQueue); 
        buffer[inb] = item;
        //printf("Producer %d: Insert Item %d at %d\n", *((int *)pno),buffer[inb]->cpuTime,inb);
        inb = (inb+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
        
      }else{

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
      }
    }
    return 0;
  
  }

//used for input validation to avoid crashes 
  int validateNum(char* arg){
  if(!isalpha(*arg)){
    //not a letter
    return 1;
  }else{
    return 0;
  }
}


//used to take input from the user in the terminal
void commandParser(){ 
while(doLoop){
  char input[100];
  char* args[100];
  char *array[sizeof(input)];
  char* word;
  char* context;
  int i = 0;
  fgets(input, sizeof(input), stdin); // read line
  //sem_wait(&empty);
  pthread_mutex_lock(&mutex);
  for (word = strtok_r(input, " ", &context);
		 word != NULL;
		 word = strtok_r(NULL, " ", &context)) {
       if (strcmp(word, " ") != 0 && strcmp(word, "\n") != 0)
		    {
			  args[i++] = word;
		    }
     }
     i=0;
	
    
    if(strcmp(args[0], "help\n") == 0){
      // help function
      helpModules();
    }
    if(strcmp(args[0], "help") == 0){
      // help function
      helpModule(args[1]);
    }
    if(strcmp(args[0], "run") == 0){
      // help function
      if(validateNum(args[2]) == 1 && validateNum(args[3]) == 1){
      run(args[1], atoi(args[2]), atoi(args[3]));
      }else{
        printf("Something went wrong with your command, please try again.\n");
      }
    }
    if(strcmp(args[0], "test") == 0){
      // help function
      if(validateNum(args[3]) == 1 && validateNum(args[4]) == 1 && validateNum(args[5]) == 1 && validateNum(args[6]) == 1){
      doBenchmark(args[1], args[2], atoi(args[3]), atoi(args[4]), atoi(args[5]), atoi(args[6]));
      }else{
        printf("Something went wrong with your command, please try again.\n");
      }
    }
    if(strcmp(args[0], "list\n") == 0){
      // help function
      printQueue(&benchmarkQueue);
    }
    if(strcmp(args[0], "change\n") == 0){
      // help function
      changeModule();
    }
    if((strcmp(args[0], "prio\n") == 0) || (strcmp(args[0], "priority\n") == 0)){
      // help function
      changeQueueType(2);
      sortPriority(&benchmarkQueue);
    }
    if(strcmp(args[0], "fcfs\n") == 0){
      // help function
      changeQueueType(0);
      sortFCFS(&benchmarkQueue);
    }

    if(strcmp(args[0], "sjf\n") == 0){
      // help function
      changeQueueType(1);
      sortShortest(&benchmarkQueue);
    }
    if(strcmp(args[0], "quit\n") == 0){
      // help function
      quit();
    }
    //sem_post(&empty);
    pthread_mutex_unlock(&mutex);
    
}
}
