package ut01.Threads.Ejercicios.ExamenPrimos.Bingo;

public class Bingo implements Runnable {
    private static final long TFIJO = 1500;
    private static final double ESPERA = 2000;
    private static final double MAX_NUM = 100;
    private Bola b;
    private String name;

    // Constructor que recibe una instancia de Bola
    public Bingo(Bola b) {
        name = "BINGO";
        this.b = b;
    }

    @Override
    public void run() {
        System.out.println(name + " started");

        while (true) {
            try {
                // Simula el tiempo que tarda en mover el bombo
                System.out.println("******************************************");
                System.out.println(name + " moviendo el bombo");
                System.out.println("******************************************");
                Thread.sleep((long) (Math.random() * ESPERA) + TFIJO);

                synchronized (b) {
                    // Genera un número aleatorio y lo asigna a la instancia de Bola
                    int n = (int) (Math.random() * MAX_NUM);
                    System.out.println("******************************************");
                    System.out.println("Bingo. Sacando número: " + n);
                    System.out.println("******************************************");
                    b.setMsg(n);

                    // Notifica a todos los hilos que estén esperando en la instancia de Bola
                    b.notifyAll();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
