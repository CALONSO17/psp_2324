package ut01.Threads.Ejercicios.Ejercicio_Cinco;

public class Transferencia {
    private int c = 0;

    public Transferencia(int c) {
        this.c = c;
    }

    public synchronized void transferencia() {
        c = c + 10;
    }

    public String toString() {
        return String.valueOf(c);
    }
}
