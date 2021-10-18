//
// Created by gdari on 10/17/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head = NULL;
struct node *tail = NULL;

bool isEmpty(){
    return head == NULL;
}

void addFront(int data){
    //make a node that is going to be added
    struct node *new = (struct node*) malloc(sizeof(struct node));
    //assign it the values given
    new->data = data;

    if(isEmpty()){
        tail = new;
    }else{
        head->prev = new;
    }

    //connect this new node to the current head
    new->next = head;
    //now make the new node the head node.
    head = new;

}

void addEnd(int data){
    //make a node that is going to be added
    struct node *new = (struct node*) malloc(sizeof(struct node));
    //assign it the values given
    new->data = data;

    if(isEmpty()){
        tail = new;
    }else{
        tail->next = new;

        new->prev = tail;
    }

    //now make the new node the tail node.
    tail = new;
}

struct node* deleteHead(){
    struct node *saveHead = head;

    if(head->next == NULL){
        tail = NULL;
    } else{
        head->next= NULL;
        head->prev = NULL;
    }

    head = head->next;
    return saveHead;
}

struct node* deleteTail(){
    struct node *saveTail = tail;

    if(head->next == NULL){
        head = NULL;
    } else{
        tail->next= NULL;
        tail->prev = NULL;
    }

    tail = tail->next;
    return saveTail;
}

int getLength(){
    int length = 0;
    struct node *current;
    for(current = head; current != NULL; current = current->next){
        length++;
    }
    return length;
}

void consumerOne(){
    
}

void consumerTwo(){

}

void producerOne(){

}

void producerTwo(){

}

int main() {
    printf("%d\n", isEmpty());
    //initializing the double linked list buffer
    int randInt = rand() % 51;
    addFront(randInt);
    randInt = rand() % 51;
    addFront(randInt);
    randInt = rand() % 51;
    addFront(randInt);

    //doing pthread producer and consumers to the buffer
    return 0;
}


