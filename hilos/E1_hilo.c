#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/*  Al programarlo Alejandro no 
    te vayas a olvidar de usar 
    el pthread.join para esperar 
    a que terminen los hilos */

// Inicializacion de variables globales:
// Contador
int cont = 0;
// Semáfoto mutex (binario)
pthread_mutex_t semaforo_bin;


// Función que van a ejecutar los hilos
void* sum_contador(void* arg){
    // Se crea la variable de tipo pthread "id_hilo" y se guarda el identificador del hilo 
    pthread_t id_hilo = pthread_self();
    // Se bloquea el semáforo para que otros hilos no entren en la región crítica
    pthread_mutex_lock(&semaforo_bin);
    // Imprimir el identificador del hilo
    printf("Soy el hilo %lu \n",(unsigned long)id_hilo);
    // Contador suma
    cont++;
    // Se imprime el contador
    printf("contador: %d \n",cont);
    // Se desbloquea el semáforo
    pthread_mutex_unlock(&semaforo_bin);
    return NULL;
}

int main(){
    pthread_t hilo1,hilo2;
    int h1 = 1, h2 = 2;

    pthread_mutex_init(&semaforo_bin, NULL);

    pthread_create(&hilo1,NULL,sum_contador,&h1);
    pthread_create(&hilo2,NULL,sum_contador,&h2);
    
    pthread_join(hilo1,NULL);
    pthread_join(hilo2,NULL);

    pthread_mutex_destroy(&semaforo_bin);

    return 0;
}



