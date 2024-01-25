package ut01.Threads.Ejercicios.ExamenPrimos.Casino;

public class Casino {

    public static void main(String[] args) {
        // Crear una instancia de la ruleta y la banca (utilizando el patrón Singleton).
        Ruleta ruleta = Ruleta.getInstance();
        Banca banca = Banca.getInstance();

        // Crear dos jugadores.
        Jugador j1 = new Jugador("Jorge");
        Jugador j2 = new Jugador("Ana");

        // Iniciar hilos para la banca y los jugadores.
        new Thread(banca).start();
        new Thread(j1).start();
        new Thread(j2).start();
    }
}
