/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   queue.h
 * Author: toman
 *
 * Created on July 6, 2020, 12:32 AM
 */

#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#define QUEUE_MAX_SIZE 5

typedef struct queue_t{
    int queue[QUEUE_MAX_SIZE+1];
    int *head;
    int *tail;
}queue_t;

void init(queue_t*);
int enqueue(queue_t*, int); //return int para corrección de errores
int dequeue(queue_t*);
int isFull(queue_t*);
int isEmpty(queue_t*);
void display(queue_t*);
    
#ifdef __cplusplus
}
#endif

#endif /* QUEUE_H */

