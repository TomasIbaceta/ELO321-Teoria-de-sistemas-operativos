/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#define QUEUE_MAX_SIZE 10

typedef struct queue_t{
    int queue[QUEUE_MAX_SIZE];
    int *head;
    int *tail;
}queue_t;

void init(int *head, int *tail);
void Enqueue(int *q,int *tail, int element);
int Dequeue(int *q,int *head);
int IsEmpty(int head,int tail);
int IsFull(int tail,const int size);
void display(int *q,int head,int tail);

void init(queue_t* q)
{
    int q->head = q->queue;
    int q->tail = q->queue;
}
 
void Enqueue(int *q,int *tail, int element)
{
    q[(*tail)++] = element;
}
 
int Dequeue(int *q,int *head)
{
    return q[(*head)++];
}
 
int IsFull(int tail,const int size)
{
    return tail == size;
}
 
int IsEmpty(int head, int tail)
{
    return tail == head;
}
 
void display(int *q,int head,int tail)
{
    int i = tail - 1;
    while(i >= head)
        printf("%d ",q[i--]);
    printf("\n");
}

int main()
{
    const int SIZE = 5; /* tamaño del queue */
    int head, tail, element;
    int queue[SIZE];
 
    init(&head,&tail);
 
    printf("--Encolar--\n");
    /* meter elementos en el queue */
    while(!IsFull(tail,SIZE))
    {
        printf("Entre un entero al queue:");
        scanf("%d",&element);
 
        Enqueue(queue,&tail,element);
 
        display(queue,head,tail);
    }
    printf("Queue está lleno\n\n");
 
    printf("--Desencolar--\n");
    while(!IsEmpty(head,tail))
    {
        element = Dequeue(queue,&head);
        printf("remover elemento del queue %d \n",element);
 
        display(queue,head,tail);
    }
    printf("Queue esta vacia\n");
    return 0;
}