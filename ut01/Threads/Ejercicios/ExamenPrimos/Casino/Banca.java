package ut01.Threads.Ejercicios.ExamenPrimos.Casino;

public class Banca implements Runnable {
    private static final int SALDO_INICIAL = 50000;
    public static final int APUESTA_MINIMA = 10;
    int saldo;

    private Ruleta ruleta;
    private static Banca instance;

    // Constructor privado para implementar el patrón Singleton.
    private Banca() {
        saldo = SALDO_INICIAL;
        ruleta = Ruleta.getInstance();
    }

    // Método estático para obtener la única instancia de Banca (patrón Singleton).
    public static Banca getInstance() {
        if (instance == null) {
            instance = new Banca();
        }
        return instance;
    }

    // Método sincronizado para obtener el saldo actual de la banca.
    public synchronized int getSaldo() {
        return saldo;
    }

    /*
     * Si le pasas +100, la banca transfiere 100 a Jugador
     * 
     * Banca banca = Banca.getInstance();
     * Jugador pepe = new Jugador(800);
     * banca.transferirA(pepe, 100);
     */
    private void transferirA(Jugador j, int cantidad) {
        saldo -= cantidad;
        j.modificaSaldo(cantidad);
    }

    // Método sincronizado para gestionar las apuestas de los jugadores.
    public synchronized void gestionaApuesta(Jugador jugador) {
        int cantidad = jugador.getCantidad();
        int nRuleta = ruleta.getNumero();

        // Verificar si el número de la ruleta coincide con la apuesta del jugador.
        if (nRuleta == jugador.getApuesta()) {
            System.out.println(jugador.getNombre() + "*****************************");
            System.out.println(jugador.getNombre() + " ha ganado " + cantidad * Ruleta.MAX_NUMEROS_NO_ZERO);
            System.out.println(jugador.getNombre() + "*****************************");
            transferirA(jugador, cantidad * Ruleta.MAX_NUMEROS_NO_ZERO);
        } else {
            System.out.println(jugador.getNombre() + " ha perdido " + cantidad);
            transferirA(jugador, -cantidad);
        }
    }

    // Método que se ejecuta en un hilo mientras el saldo de la banca sea mayor que
    // 0.
    @Override
    public void run() {
        while (getSaldo() > 0) {
            ruleta.lanzarBola();
        }
    }
}
