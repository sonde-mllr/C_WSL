package colaManual;

public class ColaManual {
    private static final int QUEUE_SIZE = 4;
    private int[] buf;
    private int head, tail;
    private boolean full, empty;

    public ColaManual() {
        buf = new int[QUEUE_SIZE];
        head = 0;
        tail = 0;
        full = false;
        empty = true;
    }

    // Añadir un elemento a la cola
    public void add(int value) {
        if (full) {
            System.out.println("Error: La cola está llena. No se puede añadir el elemento " + value);
            return;
        }
        buf[tail] = value;
        tail = (tail + 1) % QUEUE_SIZE;
        if (tail == head) {
            full = true;
        }
        empty = false;
        System.out.println("Elemento " + value + " añadido");
    }

    // Retirar un elemento de la cola
    public Integer remove() {
        if (empty) {
            System.out.println("Error: La cola está vacía. No se puede retirar un elemento.");
            return null;
        }
        int value = buf[head];
        head = (head + 1) % QUEUE_SIZE;
        if (head == tail) {
            empty = true;
        }
        full = false;
        System.out.println("Elemento " + value + " retirado");
        return value;
    }
}
