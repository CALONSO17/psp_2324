package ut01.Threads.Ejercicios.Ejercicio_Cuatro.Contador_Bloque_Sincro;

public class Contador {
    private int c = 0;
    int d;

    public Contador(int c) {
        this.c = c;
    }

    public void increment() {
        for (int i = 0; i < ContadorMain.VECES; i++) {
            d = i * i * i;
        }
        synchronized (this) {
            c = c + 1;
        }

    }

    public void decrement() {
        for (int i = 0; i < ContadorMain.VECES; i++) {
            d = i * i * i;
        }
        synchronized (this) {
            c = c - 1;
        }
    }

    @Override
    public String toString() {
        return String.valueOf(c);
    }
}
