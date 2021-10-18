//
// Created by gdari on 10/17/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>

pthread_mutex_t list_mutex;
pthread_cond_t condWait = PTHREAD_COND_INITIALIZER;
int listSize = 50;


struct node{
    int data;
    struct node *next;
    struct node *prev;
};

struct list{
    struct node *head;
    struct node *tail;
};

struct node *head = NULL;
struct node *tail = NULL;

bool isEmpty(struct list* dLL){
    if(dLL->head==NULL && dLL->tail==NULL){
        return true;
    }else{
        return false;
    }
}

void addFront(int data, struct list* dLL){
    //make a node that is going to be added
    struct node *new = (struct node*) malloc(sizeof(struct node));
    //assign it the values given
    new->data = data;

    if(isEmpty(dLL)){
        new->next = NULL;
        dLL->head = new;
        dLL->tail = new;

    }else{
        dLL->head->prev = new;
        //connect this new node to the current head
        new->next = dLL->head;
    }  
    //now make the new node the head node.
    new->prev = NULL;
    dLL->head = new;

}

void addEnd(int data, struct list* dLL){
    //make a node that is going to be added
    struct node *new = (struct node*) malloc(sizeof(struct node));
    //assign it the values given
    new->data = data;

    if(isEmpty(dLL)){
        new->prev = NULL;
        dLL->head = new;
    }else{
        dLL->tail->next = new;
        new->prev = dLL->tail;
    }

    //now make the new node the tail node.
    new->next = NULL;
    dLL->tail = new;
}

struct node* deleteHead(struct list* dLL){
    struct node *saveHead = dLL->head;

    if(dLL->head->next == NULL){
        dLL->tail = NULL;
        dLL->head = NULL;
    } else{
        dLL->head = saveHead->next;
        saveHead->next= NULL;
        saveHead->prev = NULL;
        dLL->head->prev = NULL;
    }
    return saveHead;
}

int getLength(struct list* dLL){
    int length = 0;
    struct node *current;
    //walk through until we hit null
    for(current = dLL->head; current != NULL; current = current->next){
        length++;
    }
    return length;
}

//display the list in from first to last
void displayFromStart(struct list* dLL) {

    //start from the beginning
    struct node *ptr = dLL->head;

    printf("[ ");
    //walk through pointers untill we hit the end
    while(ptr != NULL) {
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }

    printf(" ]\n");
}

bool isHeadEven(struct list* dLL){
    if((dLL->head->data % 2) == 0){
        return true;
    }else{
        return false;
    }
}

_Noreturn void *consumerOne(void* dLL){
    while(1){
        pthread_mutex_lock(&list_mutex);
        //sleep(1);
        int l = getLength(dLL);
        if(l <= 0){
            printf("C1: buffer empty \n");
            pthread_cond_wait(&condWait,&list_mutex);
            //sched_yield();
            //return 0;
        }else{
            if(!isHeadEven(dLL)){
                printf("C1 Received: ");
                displayFromStart(dLL);
                deleteHead(dLL);
                printf("C1 Output: ");
                displayFromStart(dLL);
                printf("\n");
                pthread_cond_signal(&condWait);
            }else{
                printf("C1: Waiting for odd. . . \n");
                pthread_cond_wait(&condWait,&list_mutex);
                //pthread_mutex_unlock(&list_mutex);
                //sched_yield();
                //return 0;
            }
        }
        pthread_mutex_unlock(&list_mutex);
        //sched_yield();
    }
}

_Noreturn void *consumerTwo(void* dLL){
    while(1){
        pthread_mutex_lock(&list_mutex);
        //sleep(1);
        int l = getLength(dLL);
        if(l <= 0){
            printf("C2: buffer empty \n\n");
            pthread_cond_wait(&condWait,&list_mutex);
            //sched_yield();
            //return 0;
        }else{
            if(isHeadEven(dLL)){
                printf("C2 Received: ");
                displayFromStart(dLL);
                deleteHead(dLL);
                printf("C2 Output: ");
                displayFromStart(dLL);
                printf("\n");
                pthread_cond_signal(&condWait);
            }else{
                printf("C2: Waiting for even. . . \n");
                pthread_cond_wait(&condWait,&list_mutex);
                //pthread_mutex_unlock(&list_mutex);
                //sched_yield();
                //return 0;
            }
        }
        pthread_mutex_unlock(&list_mutex);
        //sched_yield();
    }
}

_Noreturn void*producerOne(void* dLL){
    while(1){
        pthread_mutex_lock(&list_mutex);
        //sleep(1);
        int l = getLength(dLL);
        if(l >= listSize){
            printf("P1: buffer full \n");
            pthread_cond_wait(&condWait,&list_mutex);
            //pthread_mutex_unlock(&list_mutex);
            //sched_yield();
            //return 0;
        }else{
            int oddRandInt = rand() % 51;
            bool notOdd = true;
            while(notOdd){
                if(oddRandInt % 2 != 0){
                    notOdd = false;
                }else{
                    oddRandInt = rand() % 51;
                }
            }
            printf("P1 Received: ");
            displayFromStart(dLL);
            addEnd(oddRandInt,dLL);
            printf("P1 Output: ");
            displayFromStart(dLL);
            printf("\n");
            pthread_cond_signal(&condWait);   
        }
        pthread_mutex_unlock(&list_mutex);
        //sched_yield();
    }
}

_Noreturn void *producerTwo(void* dLL){
    while(1){
        pthread_mutex_lock(&list_mutex);
        //sleep(1);
        int l = getLength(dLL);
        if(l >= listSize){
            printf("P2: buffer full \n\n");
            pthread_cond_wait(&condWait,&list_mutex);
            //pthread_mutex_unlock(&list_mutex);
            //sched_yield();
            //return 0;
        }else{
            int evenRandInt = rand() % 51;
            bool notEven = true;
            while(notEven){
                if(evenRandInt % 2 == 0){
                    notEven = false;
                }else{
                    evenRandInt = rand() % 51;
                }
            }
            printf("P2 Received: ");
            displayFromStart(dLL);
            addEnd(evenRandInt,dLL);
            printf("P2 Output: ");
            displayFromStart(dLL);
            printf("\n");
            pthread_cond_signal(&condWait);
        }
        pthread_mutex_unlock(&list_mutex);
        //sched_yield();
    }
}


int main() {

    srand ( time(NULL) );
    //I have a global head and tail
    //initializing the double linked list buffer
    struct list dLL;
    struct list *dLLptr = &dLL;
    dLL.head = NULL;
    dLL.tail = NULL;

    int randInt = rand() % 51;
    printf("Adding Random Int: %d\n", randInt);
    addFront(randInt, dLLptr);
    displayFromStart(dLLptr);
    randInt = rand() % 51;
    printf("Adding Random Int: %d\n", randInt);
    addFront(randInt, dLLptr);
    displayFromStart(dLLptr);
    randInt = rand() % 51;
    printf("Adding Random Int: %d\n", randInt);
    addFront(randInt, dLLptr);
    displayFromStart(dLLptr);

    //doing pthread producer and consumers to the buffer
    //producers and consumers testing
//    producerOne(dLLptr);
//    producerTwo(dLLptr);
//    consumerOne(dLLptr);
//    consumerTwo(dLLptr);
    int numThreads = 0;
    pthread_t pthread_id;
    pthread_mutex_init(&list_mutex,NULL);
    pthread_create(&pthread_id,NULL, producerOne,dLLptr);
    numThreads++;
    pthread_create(&pthread_id,NULL, producerTwo,dLLptr);
    numThreads++;
    pthread_create(&pthread_id,NULL, consumerOne,dLLptr);
    numThreads++;
    pthread_create(&pthread_id,NULL, consumerTwo,dLLptr);
    numThreads++;
    for(int i = 0; i < numThreads; i++){
          pthread_join(i+1, NULL);
    }

    return 0;
}


