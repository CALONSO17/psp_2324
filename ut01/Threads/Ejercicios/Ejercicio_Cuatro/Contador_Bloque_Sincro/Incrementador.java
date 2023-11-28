package ut01.Threads.Ejercicios.Ejercicio_Cuatro.Contador_Bloque_Sincro;

public class Incrementador implements Runnable {
    Contador cont;

    public Incrementador(Contador c) {
        cont = c;
    }

    @Override
    public void run() {
        for (int i = 0; i < ContadorMain.VECES; i++) {
            cont.increment();
        }
    }

}
