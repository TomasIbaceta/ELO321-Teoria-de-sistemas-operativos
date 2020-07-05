#include <stdio.h>
#include <stdlib.h>
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

int main()
{
    queue_t autos_norteSur;
    init(&autos_norteSur);
    
    enqueue(&autos_norteSur, 5);
    enqueue(&autos_norteSur, 3);
    enqueue(&autos_norteSur, 4);
    enqueue(&autos_norteSur, 1);
    enqueue(&autos_norteSur, 7);
   
    for (int i=0; i<QUEUE_MAX_SIZE; i++){
         printf("posicion es %d, queue es %d\n", i, autos_norteSur.queue[i]);
    }
    
    dequeue(&autos_norteSur);
    dequeue(&autos_norteSur);
    enqueue(&autos_norteSur, 2);
    enqueue(&autos_norteSur, 9);
    
    for (int i=0; i<QUEUE_MAX_SIZE; i++){
         printf("posicion es %d, queue es %d\n", i, autos_norteSur.queue[i]);
    }
    return 0;
}

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