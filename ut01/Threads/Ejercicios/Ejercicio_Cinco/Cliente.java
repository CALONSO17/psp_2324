package ut01.Threads.Ejercicios.Ejercicio_Cinco;

public class Cliente implements Runnable {
    Transferencia tf;

    public Cliente(Transferencia t) {
        tf = t;
    }

    @Override
    public void run() {
        for (int i = 0; i < Banco.VECES; i++) {
            tf.transferencia();
        }
    }

}
