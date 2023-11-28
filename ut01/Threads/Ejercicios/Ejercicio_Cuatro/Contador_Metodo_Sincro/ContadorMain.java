package ut01.Threads.Ejercicios.Ejercicio_Cuatro.Contador_Metodo_Sincro;

public class ContadorMain {
    public static final int VECES = 1000000;

    public static void main(String[] args) {
        Contador c = new Contador(0);

        Thread t1 = new Thread(new Incrementador(c));
        Thread t2 = new Thread(new Decrementador(c));

        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException i) {
            i.getMessage();
        }

        System.out.println(String.format("El contenido es: %s", c));
    }
}
