#include <stdio.h>
#include <stdlib.h>

#define QUEUESIZE 4

typedef struct {
    int buf[QUEUESIZE];
    long head, tail;
    int full, empty;
} queue;

// Declaración de funciones
queue *queueInit(void);
void queueDelete(queue *q);
void queueAdd(queue *q, int in);
void queueDel(queue *q, int *out);

int main(void) {
    queue *fifo;
    int out;

    // Inicializar la cola
    fifo = queueInit();
    if (fifo == NULL) {
        fprintf(stderr, "Error: No se pudo inicializar la cola.\n");
        exit(1);
    }

    // Añadir elementos a la cola
    printf("Añadiendo elementos a la cola:\n");
    for (int i = 1; i <= 4; i++) {
        queueAdd(fifo, i);
        printf("Elemento %d añadido\n", i);
    }

    // Intentar añadir un elemento adicional para ver el comportamiento al estar llena
    printf("\nIntentando añadir otro elemento (5) cuando la cola está llena:\n");
    queueAdd(fifo, 5);
    
    // Eliminar elementos de la cola
    printf("\nEliminando elementos de la cola:\n");
    for (int i = 0; i < 4; i++) {
        queueDel(fifo, &out);
        printf("Elemento %d retirado\n", out);
    }

    // Intentar retirar un elemento adicional para ver el comportamiento al estar vacía
    printf("\nIntentando retirar un elemento cuando la cola está vacía:\n");
    queueDel(fifo, &out);

    // Limpiar la cola
    queueDelete(fifo);
    printf("\nLa cola ha sido eliminada correctamente.\n");

    return 0;
}

// Definición de las funciones de la cola

queue *queueInit(void) {
    queue *q;
    q = (queue *)malloc(sizeof(queue));
    if (q == NULL) return (NULL);
    q->empty = 1;
    q->full = 0;
    q->head = 0;
    q->tail = 0;
    return (q);
}

void queueDelete(queue *q) {
    free(q);
}

void queueAdd(queue *q, int in) {
    if (q->full) {
        printf("Error: La cola está llena. No se puede añadir el elemento %d.\n", in);
        return;
    }
    q->buf[q->tail] = in;
    q->tail++;
    if (q->tail == QUEUESIZE)
        q->tail = 0;
    if (q->tail == q->head)
        q->full = 1;
    q->empty = 0;
}

void queueDel(queue *q, int *out) {
    if (q->empty) {
        printf("Error: La cola está vacía. No se puede retirar un elemento.\n");
        return;
    }
    *out = q->buf[q->head];
    q->head++;
    if (q->head == QUEUESIZE)
        q->head = 0;
    if (q->head == q->tail)
        q->empty = 1;
    q->full = 0;
}
