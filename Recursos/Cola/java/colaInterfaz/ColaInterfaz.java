package colaInterfaz;

import java.util.Queue;
import java.util.ArrayDeque;

public class ColaInterfaz {
    public static void main(String[] args) {
        Queue<Integer> cola = new ArrayDeque<>(4);  // Inicializamos la cola con capacidad 4

        // Añadir elementos a la cola
        System.out.println("Añadiendo elementos a la cola:");
        for (int i = 1; i <= 4; i++) {
            if (cola.offer(i)) {
                System.out.println("Elemento " + i + " añadido");
            } else {
                System.out.println("Error: No se pudo añadir el elemento " + i);
            }
        }

        // Intentar añadir un elemento adicional para ver el comportamiento cuando la cola está llena
        System.out.println("\nIntentando añadir otro elemento (5) cuando la cola está llena:");
        if (cola.offer(5)) {
            System.out.println("Elemento 5 añadido");
        } else {
            System.out.println("Error: No se pudo añadir el elemento 5");
        }

        // Eliminar elementos de la cola
        System.out.println("\nEliminando elementos de la cola:");
        while (!cola.isEmpty()) {
            int removedElement = cola.poll();
            System.out.println("Elemento " + removedElement + " retirado");
        }

        // Intentar retirar un elemento adicional para ver el comportamiento cuando la cola está vacía
        System.out.println("\nIntentando retirar un elemento cuando la cola está vacía:");
        Integer removedElement = cola.poll();
        if (removedElement == null) {
            System.out.println("Error: La cola está vacía. No se puede retirar un elemento.");
        }
    }
}
