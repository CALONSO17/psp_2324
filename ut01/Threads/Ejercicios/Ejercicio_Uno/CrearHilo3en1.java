package ut01.Threads.Ejercicios.Ejercicio_Uno;

class Hilo1 extends Thread{
    public void run(){
        System.out.println("Hola soy Thread extendido");
    }
}

class MyRunnable1 implements Runnable{
    public void run(){
        System.out.println("Hola soy Runnable implementado");
    }
}

public class CrearHilo3en1 {
    public static void main(String[] args) {
        Runnable runnable = () -> {
            System.out.println("Hola soy Lambda de Runnable");
        };

        Thread tLambda = new Thread(runnable);
        Hilo1 tThread = new Hilo1();
        Thread tRunnable = new Thread(new MyRunnable1());

        tLambda.start();
        tThread.start();
        tRunnable.start();

    }
}
