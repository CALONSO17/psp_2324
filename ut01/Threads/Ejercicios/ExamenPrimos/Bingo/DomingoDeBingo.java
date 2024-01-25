package ut01.Threads.Ejercicios.ExamenPrimos.Bingo;

public class DomingoDeBingo {
    public static void main(String[] args) {
        // Crear una instancia de Bola que será compartida entre los hilos
        Bola b = new Bola();

        // Crear instancias de Binguero, cada uno asociado con la misma instancia de
        // Bola
        Binguero paco = new Binguero("Paco", b);
        new Thread(paco).start();

        Binguero jorge = new Binguero("Jorge", b);
        new Thread(jorge).start();

        Binguero amparo = new Binguero("Amparo", b);
        new Thread(amparo).start();

        // Crear un hilo de Bingo asociado con la misma instancia de Bola
        Bingo bingo = new Bingo(b);
        new Thread(bingo).start();

        System.out.println("All the threads are started");
    }
}
