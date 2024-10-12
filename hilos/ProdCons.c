#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/*
    Problema producto consumidor:
        - 2 Hilos se tienen que ejecutar continuamente con funciones diferentes
        - Función productor: (pensarlo como en el ejemplo del buffet)
            El productor se tiene que encargar de llenar una estructura de datos
            Dicha estructura tiene que contener 
*/

#define TAMAÑO_BUFFER 8
#define ITERACIONES 20
pthread_mutex_t semaforo_bin;



typedef struct{
    /* data */
    int bufferElementos[TAMAÑO_BUFFER];
    int indicePrimerElemento;
    int indiceUltimoElemento;
    int contadorElementos;
}bufferMesa;

void inicializarBuffer(bufferMesa* buffer){
    buffer->indicePrimerElemento=0;
    buffer->indiceUltimoElemento=-1;
    buffer->contadorElementos=0;
}

int bufferLleno(bufferMesa* buffer){
    return buffer->contadorElementos==TAMAÑO_BUFFER;
}

int bufferVacio(bufferMesa* buffer){
    return buffer->contadorElementos==0;
}

int agregarABuffer(bufferMesa* buffer,int e){
    if(bufferLleno(buffer)){
        printf("El buffer está lleno, no se puede añadir nada más\n");
        return -1;
    }
    buffer->indiceUltimoElemento = (buffer->indiceUltimoElemento+1)%TAMAÑO_BUFFER;
    buffer->bufferElementos[buffer->indiceUltimoElemento] = e;
    buffer->contadorElementos++;
    return 0;
}

int popPrimerElemento(bufferMesa* buffer){
    
    if(bufferVacio(buffer)){
        printf("El buffer está vacío, no se pueden quitar elementos\n");
        return -1;
    }

    int elementoSacado = buffer->bufferElementos[buffer->indicePrimerElemento];
    buffer->indicePrimerElemento = (buffer->indicePrimerElemento+1)%TAMAÑO_BUFFER;
    buffer->contadorElementos--;

    return elementoSacado;
}

void* hiloProductor(void* args){
    bufferMesa* buffer = (bufferMesa*) args;
    for(int i = 0;i<ITERACIONES;i++){ 
        pthread_mutex_lock(&semaforo_bin);
        /* Inicio Región Crítica*/
        // Se "produce" (Se pone añade un 1)
        if(agregarABuffer(buffer,1)!=-1){
            printf("Añadido un elemento al buffer en la posicion: %i\n",buffer->indiceUltimoElemento);
            printf("Numero de elementos: %i \n: ",buffer->contadorElementos);
        }
        pthread_mutex_unlock(&semaforo_bin);
        /* Fin Región Crítica*/
        sleep(2);
    }
    return NULL;
}

void* hiloConsumidor(void* args){
    bufferMesa* buffer = (bufferMesa*) args;
    for(int i = 0; i<ITERACIONES;i++){
        pthread_mutex_lock(&semaforo_bin);
        /* Inicio Región Crítica*/
        // Se elimina el primer elemento disponible del buffer
        int elemento = popPrimerElemento(buffer);
        if(elemento!=-1){
            printf("Retirado el elemento: %i, estaba en la posicion: %i\n",elemento,buffer->indicePrimerElemento-1);
        }
        pthread_mutex_unlock(&semaforo_bin);
        sleep(5);
    }
    
    return NULL;   
}

int main(){
    bufferMesa bufferProductos;
    inicializarBuffer(&bufferProductos);

    pthread_t hProd,hCons;

    pthread_mutex_init(&semaforo_bin,NULL);

    if(pthread_create(&hProd,NULL,hiloProductor,&bufferProductos)!=0){
        printf("No se pudo crear el hilo productor\n");
        return 1;
    }
    if(pthread_create(&hCons,NULL,hiloConsumidor,&bufferProductos)!=0){
        printf("No se pudo crear el hilo consumidor\n");
        return 1;
    }
    
    /* FALTAN COSAS AUN*/

    pthread_join(hProd,NULL);
    pthread_join(hCons,NULL);

    return 0;
}