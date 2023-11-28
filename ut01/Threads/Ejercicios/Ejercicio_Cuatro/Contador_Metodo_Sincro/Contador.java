package ut01.Threads.Ejercicios.Ejercicio_Cuatro.Contador_Metodo_Sincro;

public class Contador {
    int c;

    public Contador(int c) {
        this.c = c;
    }

    public synchronized void increment() {
        c = c + 1;
    }

    public synchronized void decrement() {
        c = c - 1;
    }

    @Override
    public String toString() {
        return String.valueOf(c);
    }
}
