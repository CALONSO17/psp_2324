package ut01.Threads.Ejercicios.ExamenPrimos.Casino;

public class Jugador implements Runnable {

    private static final int SALDO = 1000;
    int saldo;
    int apuesta;
    int cantidad;
    String nombre;
    Ruleta ruleta;
    Banca banca;

    // Constructor que inicializa los atributos del jugador.
    public Jugador(String nombre) {
        this.nombre = nombre;
        saldo = SALDO;
        ruleta = Ruleta.getInstance();
        banca = Banca.getInstance();
    }

    // Método para modificar el saldo del jugador.
    public void modificaSaldo(int cantidad) {
        this.saldo += cantidad;
    }

    @Override
    public void run() {
        // Bucle mientras el saldo sea suficiente para la apuesta mínima.
        while (saldo >= Banca.APUESTA_MINIMA) {
            cantidad = Banca.APUESTA_MINIMA;
            apuesta = (int) ((Math.random() * Ruleta.MAX_NUMEROS_NO_ZERO) + 1);
            System.out.println("Soy " + getNombre() + " aposté por el " + apuesta);

            try {
                // Esperar a que la ruleta notifique sobre el resultado del lanzamiento de la
                // bola.
                synchronized (ruleta) {
                    ruleta.wait();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            // Gestionar la apuesta con la banca.
            banca.gestionaApuesta(this);
            System.out.println("Soy " + getNombre() + " me quedan " + saldo);
        }

        // El jugador está en bancarrota.
        System.out.println("Estoy en bancarrota");
    }

    // Obtener la cantidad apostada.
    public int getCantidad() {
        return cantidad;
    }

    // Obtener el número por el que apostó el jugador.
    public int getApuesta() {
        return apuesta;
    }

    // Obtener el nombre del jugador.
    public String getNombre() {
        return nombre;
    }
}
