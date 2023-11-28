package ut01.Threads.Ejercicios.Ejercicio_Uno;

class MyRunnable implements Runnable{
    public void run(){
        System.out.println("Hola mundo");
    }
}
public class CrearHiloRunnable {
    public static void main(String[]args){
        Thread t = new Thread(new MyRunnable());
        t.start();
    }
}
