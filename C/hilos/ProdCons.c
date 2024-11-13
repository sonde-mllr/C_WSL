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

// Defino el tamaño del buffer y el número máximo de iteraciones que tendrán los hilos
#define TAMAÑO_BUFFER 8
#define ITERACIONES 20

// creo el semáforo binario
pthread_mutex_t semaforo_bin;


// defino el buffer con las variables 
typedef struct{
    /* data */
    int bufferElementos[TAMAÑO_BUFFER];
    int indicePrimerElemento;
    int indiceUltimoElemento;
    int contadorElementos;
}bufferMesa;


/*============== FUNCIONES ============== */

// Función para establecer los valores iniciales del buffer
void inicializarBuffer(bufferMesa* buffer){
    // Indica donde está el primer elemento que encontramos en el buffer
    // Si imaginamos un array dibujado:
    // [][][x][x][x][x][][]
    // En este caso el indice primer elemento sería 2
    buffer->indicePrimerElemento=0;
    // Indica donde está el último elemento añadido 
    // En el caso del "dibujo anterior" estaría en 5
    buffer->indiceUltimoElemento=-1;
    // Cuenta el numero de elementos, en el caso del dibujo: 4
    buffer->contadorElementos=0;
}

// Si el numero de elementos del buffer es igual al tamaño, devuelve true
// Indica cuando el buffer está lleno
int bufferLleno(bufferMesa* buffer){
    return buffer->contadorElementos==TAMAÑO_BUFFER;
}

// Si el contador de elemetos está a 0 devuelve true
// Indica si el buffer está vacío
int bufferVacio(bufferMesa* buffer){
    return buffer->contadorElementos==0;
}

// Añade un elemento al buffer
// Parametros de entrada: El buffer de tipo bufferMesa y un entero "e"
int agregarABuffer(bufferMesa* buffer,int e){
    // Primero comprueba si el buffer está lleno, en caso de que lo esté escribe el mensaje
    // Y devuelve -1 (Esto es para mas tarde comprobar si está lleno o no en el hilo y ejecutar el if o no)
    if(bufferLleno(buffer)){
        printf("El buffer está lleno, no se puede añadir nada más\n");
        return -1;
    }
    // Cambia las variables del buffer
    /*
        indiceUltimoElemento
    */
    // El nuevo indice será el resto del indice anterior+1 entre el tamaño del buffer
    // Se hace de esta manera para que si llega al tamaño del buffer, el indice del último elemento sea 0
    buffer->indiceUltimoElemento = (buffer->indiceUltimoElemento+1)%TAMAÑO_BUFFER;
    // En el buffer escribe en la posicion nueva definida por la linea anterior el parametro dado e
    buffer->bufferElementos[buffer->indiceUltimoElemento] = e;
    // Suma el número de elementos
    buffer->contadorElementos++;
    // devuelve 0 para indicar que acabó correctamente
    return 0;
}

int popPrimerElemento(bufferMesa* buffer){
    //Comprueba si está vacío para poder sacar elementos
    // En caso contrario imprime el texto por pantalla y devuelve -1 para indicar error en caso de necesitarlo
    if(bufferVacio(buffer)){
        printf("El buffer está vacío, no se pueden quitar elementos\n");
        return -1;
    }
    // Guarda en la variable elemento sacado el primer valor que encuentre en el buffer 
    // Por como está el código actualmente 12/10/24 22:33 siempre va a ser 1 pero esto podría cambiar
    int elementoSacado = buffer->bufferElementos[buffer->indicePrimerElemento];
    // Actualiza donde estará el primer elemento del buffer (en la siguiente posición)
    buffer->indicePrimerElemento = (buffer->indicePrimerElemento+1)%TAMAÑO_BUFFER;
    // Actualiza el contador restando
    buffer->contadorElementos--;
    // Devuelve la variable que creamos antes
    return elementoSacado;
}

// Función que ejecutará el hilo Prodcutor
void* hiloProductor(void* args){
    // guarda en la variable buffer el buffer dado como parámetro. (apunta a su dirección de memoria... creo)
    bufferMesa* buffer = (bufferMesa*) args;
    // Se establece un bucle que se ejecutará hasta que i sea igual al numero de iteraciones definido al principio
    for(int i = 0;i<ITERACIONES;i++){
        // bloquea el semáforo
        pthread_mutex_lock(&semaforo_bin);
        /* Inicio Región Crítica*/
        // Se "produce" (un 1). Se añade un 1 al buffer, además comprueba el valor que devuelve la función, en caso de ser -1
        // nos estaría indicando que el buffer está lleno y no imprimirá nada por pantalla
        int numAleatorio = rand() % 10;
        if(agregarABuffer(buffer,numAleatorio)!=-1){
            printf("+ Añadido un elemento al buffer en la posicion: %i, Elemento: %i\n",buffer->indiceUltimoElemento,numAleatorio);
            printf("* Numero de elementos: %i \n ",buffer->contadorElementos);
        }
        // desbloquea el semáforo
        pthread_mutex_unlock(&semaforo_bin);
        /* Fin Región Crítica*/
        //espera dos segundos
        sleep(2);
    }
    return NULL;
}
// Función que ejecutará el hilo Consumidor
void* hiloConsumidor(void* args){
    // guarda en la variable buffer el buffer dado como parámetro. (apunta a su dirección de memoria... creo)
    bufferMesa* buffer = (bufferMesa*) args;
    // Se establece un bucle que se ejecutará hasta que i sea igual al numero de iteraciones definido al principio
    for(int i = 0; i<ITERACIONES;i++){
        pthread_mutex_lock(&semaforo_bin);
        /* Inicio Región Crítica*/
        // Se elimina el primer elemento disponible del buffer
        int elemento = popPrimerElemento(buffer);
        // Comprueba si no es -1, es caso de serlo significaría que está vacío el buffer
        // alomejor esta linea y la anterior se pueden escribir mas compacto rollo if((int elemento = popPrimerElemento(buffer)) != -1)
        // pero tampoco me apetecia complicarme pq no sabía si se podía o no
        if(elemento!=-1){
            printf("- Retirado el elemento: %i, estaba en la posicion: %i\n",elemento,buffer->indicePrimerElemento-1);
        }
        // desbloqua el buffer
        pthread_mutex_unlock(&semaforo_bin);
        // espera 5 segundos
        sleep(5);
    }
    
    return NULL;   
}

/* 
    Se debería añadir:
        - Un generador de elementos aleatorios entre un rango. Pe: Numeros del 1 al 3
        - Una condicion en la cual si el productor ya terminó (llego al numero máximo de iteraciones)
            y no quedan elementos en el buffer -> Que el consumidor termine la función. Esto sería muy
            util si la diferencia de tiempo entre la que se produce un elemento y este es consumido, es muy alta
*/

int main(){
    // crea la variable tipo bufferMesa
    bufferMesa bufferProductos;
    // inicializa el buffer mediante la función
    inicializarBuffer(&bufferProductos);

    // Crea 2 variables (hilos) tipo pthread
    pthread_t hProd,hCons;

    // Inicializa el semafoto binario definido al principio
    pthread_mutex_init(&semaforo_bin,NULL);

    // Crea los hulos estableciendo las funciones que van a ejecutar cada uno y ¿pasa como argumento el puntero que hace referencia al buffer?
    if(pthread_create(&hProd,NULL,hiloProductor,&bufferProductos)!=0){
        printf("* No se pudo crear el hilo productor \n");
        return 1;
    }
    if(pthread_create(&hCons,NULL,hiloConsumidor,&bufferProductos)!=0){
        printf("* No se pudo crear el hilo consumidor \n");
        return 1;
    }
    // Espera a que ambos acaben
    pthread_join(hProd,NULL);
    pthread_join(hCons,NULL);
    printf("[[ Ejecución de hilos acabada ]]\n<");
    return 0;
}

