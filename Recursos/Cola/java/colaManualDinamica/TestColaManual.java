package colaManualDinamica;

public class TestColaManual {
    public static void main(String[] args) {
        ColaManualDinamica cola = new ColaManualDinamica();

        // Añadir elementos a la cola
        System.out.println("Añadiendo elementos a la cola:");
        for (int i = 1; i <= 4; i++) {
            cola.add(i);
        }

        // Intentar añadir un elemento adicional para ver el comportamiento al estar llena
        System.out.println("\nIntentando añadir otro elemento (5) cuando la cola está llena:");
        cola.add(5);

        // Eliminar elementos de la cola
        System.out.println("\nEliminando elementos de la cola:");
        for (int i = 0; i < 4; i++) {
            cola.remove();
        }

        // Intentar retirar un elemento adicional para ver el comportamiento al estar vacía
        System.out.println("\nIntentando retirar un elemento cuando la cola está vacía:");
        cola.remove();
    }
}
