/*************************************
ELO320 - TAREA 3: hilos y semaforos.

Tomás Ibaceta Guerra (ROL 201721039-7)

Abreviaciones:
    ns = norte-sur, para autos que van del norte al sur
    sn = sur-norte
    eo = este-oeste
    oe = oeste-este

VERSION CORREGIDA
    la versión anterior tenía un pequeño error de lógica que causaba que todo se rompiera y que solo funcionaran 2 de los hilos.
    encontré el error y pensé que por 5 minutos de atraso valdría la pena agregar un porcentaje tan grande de funcionalidad.

**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>
#include "queue.h"

#define T_PASO_UN_VEHICULO_S 1 //cantidad de segundos que le toma a un auto cruzar la calle

/*carreteras (colas) para que vean todos los hilos*/
queue_t via_ns;
queue_t via_sn;
queue_t via_eo;
queue_t via_oe;

void *autos_ns(void *unused);
void *autos_sn(void *unused);
void *autos_eo(void *unused);
void *autos_oe(void *unused);

/*variables de control*/
int puedePasar_ns = 0; //FLAG para norte-sur y sur-norte
int puedePasar_eo = 0;

/*semaforos*/
sem_t sem;

int main()
{
    /*inicializar semaforo*/

    if (sem_init(&sem,0,1) == -1){
        printf("ERROR: init Semaforo\n");
        return -1;
    }

    /*inicializar las carreteras*/

    init(&via_ns,"via_ns");
    init(&via_sn,"via_sn");
    init(&via_eo,"via_eo");
    init(&via_oe,"via_oe");

    /*crear los threads y sus atributos*/

    pthread_t tid_ns; /*norte sur */
    pthread_t tid_sn; 
    pthread_t tid_eo; /* este oeste */
    pthread_t tid_oe;
    pthread_attr_t attr_ns, attr_sn, attr_eo, attr_oe;
   
    pthread_attr_init(&attr_ns);
    pthread_attr_init(&attr_sn);
    pthread_attr_init(&attr_eo);
    pthread_attr_init(&attr_oe);

    pthread_create(&tid_ns, &attr_ns, autos_ns, NULL);
    pthread_create(&tid_sn, &attr_sn, autos_sn, NULL);
    pthread_create(&tid_eo, &attr_eo, autos_eo, NULL);
    pthread_create(&tid_oe, &attr_oe, autos_oe, NULL);

    /*los hilos ya están trabajando*/
    
    /*esperar a los exit (en esta configuración no ocurrirá nunca)*/

    pthread_join(tid_ns,NULL);
    pthread_join(tid_sn,NULL);
    pthread_join(tid_eo,NULL);
    pthread_join(tid_oe,NULL);

    return 0;
}

void *autos_ns(void *unused){ //agrega y deja pasar autos que van de norte a sur.
    int T_random_cola, T_pasoVehiculo; //maneja el tiempo random entre queues, maneja lo que se demora en pasar un auto.
    T_random_cola = time(NULL) + rand()%10; //condición inicial, se resetea en el while(1)
    while(1){
        /*permitir que los autos crucen cuando sea posible*/

        if((!isEmpty(&via_ns)) && puedePasar_ns){ //cruce norte-sur tiene acceso a la intersección
            if(time(NULL) >=  T_pasoVehiculo){ //si el auto ya pasó
                sem_post(&sem);
                dequeue(&via_ns);
                puedePasar_ns = 0;
                printf("%d| (%s): auto termina de cruzar.\n", time(NULL), via_ns.name );
                display(&via_ns);
                }
	    }   
        else{ //No tengo tomado el control del semaforo
            if( ( (!isEmpty(&via_ns))  && (sem_trywait(&sem) == 0))  || ( (!isEmpty(&via_ns))  && (puedePasar_ns) )  ){ // si tengo autos en la cola y puedo tomar el semaforo, lo tomo				
                puedePasar_eo = 0; //desactivamos la segunda flag.
                T_pasoVehiculo = time(NULL) + T_PASO_UN_VEHICULO_S; 
                puedePasar_ns = 1;
                printf("%d| (%s): auto comienza a cruzar...\n", time(NULL) ,via_ns.name );
            }
	    }

        /*permitir que lleguen autos en intervalos aleatorios de [0,10]s*/
        
        if( time(NULL) >= T_random_cola ){ //si pasó el tiempo para hacer enqueue
            enqueue(&via_ns, rand()%50 ); //se agrega numero random para observar al ojo como cola se mueve
            printf("%d| (%s): se agrega auto a la cola\n", time(NULL), via_ns.name);
            display(&via_ns);
            T_random_cola = time(NULL) + rand()%10; //resetear timer
        }
    }

    /*De aquí para abajo no ocurre nunca, y no es necesario para este contexto. Se deja escrito como recordatorio si en iteraciones
    futuras se pueda terminar el while(1) en caso de errores o algo*/
    pthread_exit(0);
}

void *autos_eo(void *unused){ //agrega y deja pasar autos que van de norte a sur.
    int T_random_cola, T_pasoVehiculo; //maneja el tiempo random entre queues, maneja lo que se demora en pasar un auto.
    T_random_cola = time(NULL) + rand()%10; //condición inicial, se resetea en el while(1)
    while(1){
        /*permitir que los autos crucen cuando sea posible*/

        if( (!isEmpty(&via_eo))  && puedePasar_eo ){ //cruce este-oeste tiene acceso a la intersección
            if(time(NULL) >=  T_pasoVehiculo){ //si el auto ya pasó
                sem_post(&sem);
                dequeue(&via_eo);
                puedePasar_eo = 0;
                printf("%d| (%s): auto termina de cruzar.\n", time(NULL) , via_eo.name );
                display(&via_eo);
                }
	    }   
        else{ //No tengo tomado el control del semaforo
           if( ( (!isEmpty(&via_eo))  && (sem_trywait(&sem) == 0))  || ( (!isEmpty(&via_eo))  && (puedePasar_ns) )  ){ // si tengo autos en la cola y puedo tomar el semaforo, lo tomo				
                puedePasar_ns = 0; //desactivamos el otro cruce.
                T_pasoVehiculo = time(NULL) + T_PASO_UN_VEHICULO_S; 
                puedePasar_eo = 1;
                printf("%d| (%s): auto comienza a cruzar...\n", time(NULL),  via_eo.name );
            }
	    }

        /*permitir que lleguen autos en intervalos aleatorios de [0,10]s*/
        
        if( time(NULL) >= T_random_cola ){ //si pasó el tiempo para hacer enqueue
            enqueue(&via_eo, rand()%50 ); //se agrega numero random para observar al ojo como cola se mueve
            printf("%d| (%s): se agrega auto a la cola\n", time(NULL), via_eo.name);
            display(&via_eo);
            T_random_cola = time(NULL) + rand()%10; //resetear timer
        }
    }

    /*De aquí para abajo no ocurre nunca, y no es necesario para este contexto. Se deja escrito como recordatorio si en iteraciones
    futuras se pueda terminar el while(1) en caso de errores o algo*/
    pthread_exit(0);
}


void *autos_sn(void *unused){ //agrega y deja pasar autos que van de sur a norte.
    int T_random_cola, T_pasoVehiculo; //maneja el tiempo random entre queues, maneja lo que se demora en pasar un auto.
    T_random_cola = time(NULL) + rand()%10; //condición inicial, se resetea en el while(1)
    while(1){
        if((!isEmpty(&via_sn)) && puedePasar_ns){ //cruce norte-sur tiene acceso a la intersección
            if(time(NULL) >=  T_pasoVehiculo){ //si el auto ya pasó
                sem_post(&sem);
                dequeue(&via_sn);
                puedePasar_ns = 0;
                printf("%d| (%s): auto termina de cruzar.\n", time(NULL), via_sn.name );
                display(&via_sn);
                }
	    }   
        else{ //No tengo tomado el control del semaforo
            if( ( (!isEmpty(&via_sn))  && (sem_trywait(&sem) == 0))  || ( (!isEmpty(&via_sn))  && (puedePasar_ns) )  ){ // si tengo autos en la cola y puedo tomar el semaforo, lo tomo				
                puedePasar_eo = 0; //desactivamos la segunda flag.
                T_pasoVehiculo = time(NULL) + T_PASO_UN_VEHICULO_S; 
                puedePasar_ns = 1;
                printf("%d| (%s): auto comienza a cruzar...\n", time(NULL) ,via_sn.name);
            }
	    }
        
        if( time(NULL) >= T_random_cola ){ //si pasó el tiempo para hacer enqueue
            enqueue(&via_sn, rand()%50 ); //se agrega numero random para observar al ojo como cola se mueve
            printf("%d| (%s): se agrega auto a la cola\n", time(NULL), via_sn.name);
            display(&via_sn);
            T_random_cola = time(NULL) + rand()%10; //resetear timer
        }
    }
}

void *autos_oe(void *unused){ //agrega y deja pasar autos que van de norte a sur.
    int T_random_cola, T_pasoVehiculo; //maneja el tiempo random entre queues, maneja lo que se demora en pasar un auto.
    T_random_cola = time(NULL) + rand()%10; //condición inicial, se resetea en el while(1)
    while(1){
        if((!isEmpty(&via_oe))  && puedePasar_eo){ //cruce este-oeste tiene acceso a la intersección
            if(time(NULL) >=  T_pasoVehiculo){ //si el auto ya pasó
                sem_post(&sem);
                dequeue(&via_oe);
                puedePasar_eo = 0;
                printf("%d| (%s): auto termina de cruzar.\n", time(NULL) , via_oe.name );
                display(&via_oe);
                }
	    }   
        else{ //No tengo tomado el control del semaforo
            if( ( (!isEmpty(&via_oe))  && (sem_trywait(&sem) == 0))  || ( (!isEmpty(&via_oe))  && (puedePasar_eo) )  ){ // si tengo autos en la cola y puedo tomar el semaforo, lo tomo				
                puedePasar_eo = 0; //desactivamos el otro cruce.
                T_pasoVehiculo = time(NULL) + T_PASO_UN_VEHICULO_S; 
                puedePasar_ns = 1;
                printf("%d| (%s): auto comienza a cruzar...\n", time(NULL),  via_oe.name );
            }
	    }
        
        if( time(NULL) >= T_random_cola ){ //si pasó el tiempo para hacer enqueue
            enqueue(&via_oe, rand()%50 ); //se agrega numero random para observar al ojo como cola se mueve
            printf("%d| (%s): se agrega auto a la cola\n", time(NULL), via_oe.name);
            display(&via_oe);
            T_random_cola = time(NULL) + rand()%10; //resetear timer
        }
    }
}
