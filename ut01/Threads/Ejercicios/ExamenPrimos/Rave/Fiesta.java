package ut01.Threads.Ejercicios.ExamenPrimos.Rave;

public class Fiesta {
    public static void main(String args[]) {
        // Crear una instancia de la clase WC que será compartida entre los hilos Ravero
        WC wc = new WC();

        // Iniciar tres hilos de Ravero, cada uno asociado con la misma instancia de WC
        new Thread(new Ravero(1, wc)).start();
        new Thread(new Ravero(2, wc)).start();
        new Thread(new Ravero(3, wc)).start();
    }
}
