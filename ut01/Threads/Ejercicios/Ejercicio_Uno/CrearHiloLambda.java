package ut01.Threads.Ejercicios.Ejercicio_Uno;

public class CrearHiloLambda {
    public static void main(String[] args) {
        Runnable runnable = () -> {
            System.out.println("Hola mundo");
        };

        Thread t = new Thread(runnable);
        t.start();
    }
}
