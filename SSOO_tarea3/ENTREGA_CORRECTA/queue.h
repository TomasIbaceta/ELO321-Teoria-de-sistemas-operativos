#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_MAX_SIZE 5

typedef struct queue_t{ /*para queue ADT implementado con array*/
    int queue[QUEUE_MAX_SIZE+1];
    int *head;
    int *tail;
    char* name;
}queue_t;

/*
example: init(&queue_1, "cola_supermercado"); 
Inicializa un array y le da un nombre
*/
void init(queue_t*, char*);

/*
example: enqueue(&queue_1, 5);
agrega un elemento al final de la queue
*/
int enqueue(queue_t*, int); //return int para corrección de errores

/*
example: dequeue(&queue_1);
Quita el primer elemento de la queue y desplaza todos los elementos una posición hacia la cabeza
*/
int dequeue(queue_t*);

/*
example: isFull(&queue_1);
devuelve 1 si la cola está llena.
*/
int isFull(queue_t*);

/*
example: isEmpty(&queue_1);
devuelve 1 si la cola está vacía.
*/
int isEmpty(queue_t*);

/*
example: display(&queue_1);
Muestra los elementos en la queue entre head y tail.
"queue->name: (head| 1 2 3 4 |tail)"
*/
void display(queue_t*);    
    

#endif /* QUEUE_H */

