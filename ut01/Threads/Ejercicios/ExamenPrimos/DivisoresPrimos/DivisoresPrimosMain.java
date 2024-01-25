package ut01.Threads.Ejercicios.ExamenPrimos.DivisoresPrimos;

public class DivisoresPrimosMain {
    private static final int NUM_PARAMS = 2;
    private static final int NUM_MINIMO = 30000;
    private static final int THREADS_MAX = 10;
    private static final int THREADS_MIN = 2;

    public static void main(String[] args) {
        // Verificación del número de parámetros
        if (args.length != NUM_PARAMS) {
            System.err.print("Número de parámetros incorrectos");
            return;
        }

        // Parseo de los parámetros
        int numTrabajo = Integer.parseInt(args[0]);
        int numThreads = Integer.parseInt(args[1]);

        // Verificación de parámetros dentro de rangos permitidos
        if (numTrabajo < NUM_MINIMO || numThreads < THREADS_MIN || THREADS_MAX < numThreads) {
            System.err.print("Parámetros incorrectos");
            return;
        }

        // Cálculo de la cantidad de números por hilo
        int cantidadDeNumerosPorThread = numTrabajo / numThreads;

        // Bucle que crea y lanza hilos para procesar los números
        for (int i = 0; i < numThreads; i++) {
            // Cálculo del rango de números a procesar por cada hilo
            int ini = (i == 0) ? 1 : i * cantidadDeNumerosPorThread; /* cálculo de inicio */
            int fin = (i == numThreads - 1) ? numTrabajo : ini + cantidadDeNumerosPorThread; /* cálculo de fin */

            // Creación y inicio de un nuevo hilo que ejecuta la lógica en DivisoresPrimos
            new Thread(
                    new DivisoresPrimos(
                            ini,
                            fin,
                            numTrabajo))
                    .start();
        }
    }
}
