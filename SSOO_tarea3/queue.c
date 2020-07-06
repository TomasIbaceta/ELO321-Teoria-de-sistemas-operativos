/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "queue.h"
#include <stdio.h>

void init(queue_t* q)
{
    for (int i=0; i<(QUEUE_MAX_SIZE); i++){
        q->queue[i] = 0;
    }
    
    q->head = q->queue;
    q->tail = q->queue;
}

int enqueue(queue_t* q, int element){
    if ( isFull(q)){
        printf("ERROR: queue full\n");
        return -1;
    }

    else{
        printf("Element Queued: %d\n", element);
        *q->tail = element;
        if ( !isFull(q) ){
            q->tail++;
        }
        return 0;  
    }
}

int dequeue(queue_t* q){ //retornar el primer elemento, shiftear todos uno para la izquierda
    if ( isEmpty(q) ){
        printf("ERROR: queue is empty\n");
        return -1;
    }
    
    else{
        int dequeued = *(q->head);
    
        for (int i = 0; q->head+i != q->tail; i++){ //shiftea todos uno a la izquierda, manteniendo las posiciones de head y tail
            *(q->head+i) = *(q->head+i+1);
        }
        *(q->tail--) = 0;

        printf("Element Dequeued: %d\n", dequeued);
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
        printf("ERROR: queue is empty\n");
        return;
    }
    
    int *i = (q->head);
    printf("Displaying:\n Head| ");
    while (i <= (q->tail - 1)){
        printf("%d ", *i++);
    }
    printf("|tail \n");
    return;
}