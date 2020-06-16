#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
 
#define N 5 // Número de Filósofos
#define THINKING 2 // Estados Pensando, hambre y comiendo
#define HUNGRY 1
#define EATING 0
#define LEFT (fil_num + 4) % N
#define RIGHT (fil_num + 1) % N
 
int estado[N]= { 2, 2, 2, 2, 2 };  // Arreglo del Estado de cada Filósofo
int filosofo[N] = { 0, 1, 2, 3, 4 }; //
 
sem_t mutex;
sem_t S[N];
 
void test(int fil_num)
{
   
    if (estado[fil_num] == HUNGRY && estado[LEFT] != EATING && estado[RIGHT] != EATING) {
        // Cambia Estado Comiendo
        estado[fil_num] = EATING;
 
        sleep(1);
 
        printf("Filósofo %d tomando palillos %d y %d\n", fil_num + 1, LEFT + 1, fil_num + 1);
 
        printf("Filósofo %d esta comiendo ***\n\n", fil_num + 1);
	sleep(20);
 
     
        sem_post(&S[fil_num]);
    }
    else
     printf("Filósofo %d palillos  %d y %d ocupados \n\n", fil_num + 1, LEFT + 1, fil_num + 1);
}
 
// Recoger Palillos
void take_fork(int fil_num)
{ 
    sem_wait(&mutex); //  Semáforo para realizar test
 
    // Cambia Estado a Hambre
    estado[fil_num] = HUNGRY;
 
    printf("Filósofo %d con Hambre\n", fil_num + 1);
 
    // Verifica si los vecinos no estan comiendo
    test(fil_num);
 
    sem_post(&mutex); // libera semáforo
 
    // si no puede comer espera a que se habilite su semaforo
    printf("Esperando semáforo S Filósofo %d \n", fil_num +1);
    sem_wait(&S[fil_num]);
    printf("Se Habilita semáforo S Filósofo %d \n\n", fil_num +1);   
 
    sleep(1);
}
 
// Soltar Palillos
void put_fork(int fil_num)
{
 
    sem_wait(&mutex);
 
    // state that thinking
    estado[fil_num] = THINKING;
 
    printf("Filósofo %d soltando palillos %d y %d \n",
           fil_num + 1, LEFT + 1, fil_num + 1);
    printf("Filósofo %d pensando \n\n", fil_num + 1);
 
    printf("Filósofo %d test izquierda \n\n", fil_num + 1);
    test(LEFT);
    printf("Filósofo %d test derecha \n\n", fil_num + 1);
    test(RIGHT);
 
    sem_post(&mutex);
}
 
void* funcion_filosofo(void* num)
{
 
    while (1) {
 
        int* i = num;
 
        sleep(5);
 
        take_fork(*i);
 
        sleep(5);
 
        put_fork(*i);
    }
}
 
int main()
{
 
    int i;
    pthread_t thread_filosofo[N];
 
    // inicialización de semáforos
    sem_init(&mutex, 0, 1);
 
    for (i = 0; i < N; i++)  
        sem_init(&S[i], 0, 0);
 
    for (i = 0; i < N; i++) { 
        // creación de hilos de filosofos
        pthread_create(&thread_filosofo[i], NULL,
                       funcion_filosofo, &filosofo[i]); 
        printf("Filósofo %d pensando\n", i + 1);
    }
 
    for (i = 0; i < N; i++) 
        pthread_join(thread_filosofo[i], NULL);
}
