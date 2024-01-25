package ut01.Threads.Ejercicios.ExamenPrimos.Casino;

public class Ruleta {
    private static final long TIEMPO_JUGADA = 3000;
    public static final int MAX_NUMEROS = 37;
    public static final int MAX_NUMEROS_NO_ZERO = 36;
    private int n;
    private static Ruleta instance;

    // Constructor privado para implementar el patrón Singleton.
    private Ruleta() {
        instance = null;
    }

    // Método estático para obtener la única instancia de Ruleta (patrón Singleton).
    public static Ruleta getInstance() {
        if (instance == null) {
            instance = new Ruleta();
        }
        return instance;
    }

    // Método que simula el lanzamiento de la bola en la ruleta.
    public void lanzarBola() {
        try {
            System.out.println("Hagan sus apuestas!");
            Thread.sleep(TIEMPO_JUGADA);
            n = (int) (Math.random() * MAX_NUMEROS);
            System.out.println("Salió el " + n + "!");

            // Notificar a todos los hilos que estén esperando en esta instancia de Ruleta.
            synchronized (this) {
                notifyAll();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    // Método para obtener el número que salió en la ruleta.
    public int getNumero() {
        return n;
    }
}
