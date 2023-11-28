package ut01.Threads.Ejercicios.Ejercicio_Cuatro.Contador_Bloque_Sincro;

public class Decrementador implements Runnable {
    Contador cont;

    public Decrementador(Contador c) {
        cont = c;
    }

    @Override
    public void run() {
        for (int i = 0; i < ContadorMain.VECES; i++) {
            cont.decrement();
        }
    }
}
