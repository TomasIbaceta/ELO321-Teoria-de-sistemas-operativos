#include <stdio.h>
#include <stdlib.h>
#include "queue.h"




int main()
{
    queue_t autos_norteSur;
    init(&autos_norteSur);
    
    enqueue(&autos_norteSur, 5);
    enqueue(&autos_norteSur, 3);
    enqueue(&autos_norteSur, 4);
    enqueue(&autos_norteSur, 1);
    enqueue(&autos_norteSur, 7);
    enqueue(&autos_norteSur, 9);
   
    for (int i=0; i<QUEUE_MAX_SIZE; i++){
         printf("posicion es %d, queue es %d\n", i, autos_norteSur.queue[i]);
    }
    
    dequeue(&autos_norteSur);
    dequeue(&autos_norteSur);
    dequeue(&autos_norteSur);
    enqueue(&autos_norteSur, 40);
    enqueue(&autos_norteSur, 16);


    
    for (int i=0; i<QUEUE_MAX_SIZE; i++){
         printf("posicion es %d, queue es %d\n", i, autos_norteSur.queue[i]);
    }
    return 0;
}

