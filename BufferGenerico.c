#include <stdio.h>
#include <stdlib.h>


#define TAMAÑO_BUFFER 8

typedef struct {
    int *iBufferArray;
    int iIndiceAgregarElemento;
    int iIndiceSacarElemento;
    int iContadorElementos;
}Buffer;

Buffer* bufferGenerico;

/* ============ FUNCIONES ============ */

int bufferLleno(){
    return bufferGenerico->iContadorElementos==TAMAÑO_BUFFER;
}

int bufferVacio(){
    return bufferGenerico->iContadorElementos==0;
}

int addElement(int iElemento){
    int iValidarElementoAgregado = 0;
    if(!bufferLleno()){
        bufferGenerico->iIndiceAgregarElemento = (bufferGenerico->iIndiceAgregarElemento+1)%TAMAÑO_BUFFER;
        bufferGenerico->iBufferArray[bufferGenerico->iIndiceAgregarElemento] = iElemento;
        bufferGenerico->iContadorElementos++;
    } else {
        iValidarElementoAgregado = 1;
    }
    return iValidarElementoAgregado;
}

int removeElement(){
    int iElemento = -1;
    if(!bufferVacio()){
        iElemento = bufferGenerico->iBufferArray[bufferGenerico->iIndiceSacarElemento];
        bufferGenerico->iIndiceSacarElemento = (bufferGenerico->iIndiceSacarElemento+1)%TAMAÑO_BUFFER;
        bufferGenerico->iContadorElementos--;
    }
    return iElemento;
}

int getElements(){
    return bufferGenerico->iContadorElementos;
}

int searchPosition(int iIndice){
    int iElemento = -1;
    if(!bufferVacio()){
       iElemento = bufferGenerico->iBufferArray[iIndice];
    }
    return iElemento;
}

void initQueue(){
    bufferGenerico = (Buffer*)malloc(sizeof(Buffer));
    bufferGenerico->iBufferArray = (int*)malloc(TAMAÑO_BUFFER*sizeof(int));

    bufferGenerico->iIndiceAgregarElemento = 0;
    bufferGenerico->iIndiceSacarElemento = -1;
}

void freeQueue(){
    free(bufferGenerico->iBufferArray);
    free(bufferGenerico);
}

