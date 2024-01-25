package ut01.Threads.Ejercicios.ExamenPrimos.Bingo;

public class Binguero implements Runnable {
    private Bola b;
    private String name;

    // Constructor que recibe un nombre y una instancia de Bola
    public Binguero(String name, Bola b) {
        this.name = name;
        this.b = b;
    }

    @Override
    public void run() {
        while (true) {
            synchronized (b) {
                try {
                    System.out.println(name + " esperando a la bola.");
                    // Esperar hasta que reciba una notificación desde la instancia de Bola
                    b.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                // Imprimir el número escuchado desde la instancia de Bola
                System.out.println(name + " he escuchado el: " + b.getMsg());
            }
        }
    }
}
