#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
    queue_t autos_norteSur;
    init(&autos_norteSur);
    
    enqueue(&autos_norteSur, 5);
    display(&autos_norteSur);
    enqueue(&autos_norteSur, 3);
    display(&autos_norteSur);
    enqueue(&autos_norteSur, 4);
    display(&autos_norteSur);
    enqueue(&autos_norteSur, 1);
    display(&autos_norteSur);
    enqueue(&autos_norteSur, 7);
    display(&autos_norteSur);
    enqueue(&autos_norteSur, 9);
    
    display(&autos_norteSur);
    /*
    for (int i=0; i<QUEUE_MAX_SIZE; i++){
         printf("posicion es %d, queue es %d\n", i, autos_norteSur.queue[i]);
    }
    */
    dequeue(&autos_norteSur);
    dequeue(&autos_norteSur);
    dequeue(&autos_norteSur);
    enqueue(&autos_norteSur, 40);
    enqueue(&autos_norteSur, 16);
    
    display(&autos_norteSur);
    /*
    for (int i=0; i<QUEUE_MAX_SIZE; i++){
         printf("posicion es %d, queue es %d\n", i, autos_norteSur.queue[i]);
    }
     * */
    return 0;
}

