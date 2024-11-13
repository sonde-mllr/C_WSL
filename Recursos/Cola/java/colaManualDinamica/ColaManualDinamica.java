package colaManualDinamica;
import java.util.ArrayList;

public class ColaManualDinamica {
    private ArrayList<Integer> buf;
    private int head, tail;
    private boolean full, empty;

    public ColaManualDinamica() {
        buf = new ArrayList<>();
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
        buf.add(tail, value);
        tail = (tail + 1) % buf.size();
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
        int value = buf.get(head);
        buf.remove(head);
        if (head == tail) {
            empty = true;
        }
        full = false;
        System.out.println("Elemento " + value + " retirado");
        return value;
    }
}
