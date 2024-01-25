package ut01.Threads.Ejercicios.ExamenPrimos;

public class HijoIdentificado implements Runnable {

    // Número de saludos que cada hijo imprimirá
    private static final int NUM_SALUDOS = 2;

    // Número total de hijos que se crearán
    private static final int NUM_HIJO = 4;

    // Identificador único del hijo
    int id;

    // Constructor que recibe un identificador para el hijo
    public HijoIdentificado(int id) {
        this.id = id;
    }

    // Método que representa la tarea que realiza cada hijo al ejecutar el hilo
    @Override
    public void run() {
        // Ciclo que imprime un mensaje para el hijo
        for (int i = 0; i < NUM_SALUDOS; i++) {
            System.out.println("Soy el hijo " + id);
        }
    }

    // Método principal que inicia el programa
    public static void main(String[] args) {
        // Ciclo que crea instancias de HijoIdentificado y ejecuta el método run
        // directamente
        for (int i = 1; i <= NUM_HIJO; i++) {
            HijoIdentificado hijo = new HijoIdentificado(i);
            hijo.run();

            /*
             * // Forma más adecuada de ejecutar el hilo utilizando un objeto Thread
             * Thread t = new Thread(hijo);
             * t.start();
             */

            /*
             * // Otra forma de crear e iniciar un hilo directamente en una línea
             * new Thread(new HijoIdentificado(i)).start();
             */
        }

        // Ciclo que imprime un mensaje para el hilo principal
        for (int i = 0; i < NUM_SALUDOS; i++) {
            System.out.println("Soy el principal");
        }
    }
}
