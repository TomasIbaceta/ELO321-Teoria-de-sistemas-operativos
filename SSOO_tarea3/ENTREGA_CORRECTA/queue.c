/*
Este archivo implementa un Queue ADT
Mas detalles en el .h 
*/

#include "queue.h"
#include <sys/time.h>
#include <stdio.h>
void init(queue_t* q, char* name)
{
    for (int i=0; i<(QUEUE_MAX_SIZE); i++){
        q->queue[i] = 0;
    }
    q->name = name;
    q->head = q->queue;
    q->tail = q->queue;    
}

int enqueue(queue_t* q, int element){
    if ( isFull(q)){
        //printf("ERROR: queue full\n");
        return -1;
    }

    else{
        *q->tail = element;
        if ( !isFull(q) ){
            q->tail++;
        }
        return 0;  
    }
}

int dequeue(queue_t* q){ //retornar el primer elemento, shiftear todos uno para la izquierda
    if ( isEmpty(q) ){
        printf("(%s) ERROR: queue is empty\n", q->name);
        return -1;
    }
    
    else{
        int dequeued = *(q->head);
    
        for (int i = 0; q->head+i != q->tail; i++){ //shiftea todos uno a la izquierda, manteniendo las posiciones de head y tail
            *(q->head+i) = *(q->head+i+1);
        }
        *(q->tail--) = 0;

        //printf("Element Dequeued: %d\n", dequeued);
        return dequeued;
    }
}

int isFull(queue_t* q){
    return (q->tail) == &(q->queue[QUEUE_MAX_SIZE]);
}

int isEmpty(queue_t* q){
    return q->head == q->tail;
}

void display(queue_t* q){
    if ( isEmpty(q) ){
        printf("%d| (%s) STATUS: (Head| |Tail)\n", time(NULL) ,q->name);
        return;
    }
    
    int *i = (q->head);
    printf("%d| (%s) STATUS: (Head| ", time(NULL), q->name);
    while (i <= (q->tail - 1)){
        printf("%d ", *i++);
    }
    printf("|tail) \n");
    return;
}