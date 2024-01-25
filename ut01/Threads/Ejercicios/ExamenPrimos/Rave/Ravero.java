package ut01.Threads.Ejercicios.ExamenPrimos.Rave;

public class Ravero implements Runnable {
    private WC wc;
    private int id;

    // Constructor que recibe un identificador y una instancia de WC
    public Ravero(int id, WC wc) {
        this.wc = wc;
        this.id = id;
    }

    // Método para simular una pausa o espera en milisegundos
    private void duerme(int ms) {
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        while (true) { // Que la fiesta no pare!
            System.out.println(id + " Fiesta!!");
            duerme(250);

            // Verificar si el baño está libre
            if (!wc.ocupado()) { // Si dos consultan al mismo tiempo
                synchronized (wc) { // Uno de ellos se queda aquí
                    wc.entra(); // Entra al baño
                    System.out.println(id + " Entro!!");
                    duerme(1000);
                    System.out.println(id + " Salgo!!");
                    wc.sal(); // Sale del baño
                }
            }
        }
    }
}
