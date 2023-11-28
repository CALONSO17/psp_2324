package ut01.Threads.Ejercicios.Ejercicio_Uno;

class Hilo extends Thread{
    public void run(){
        System.out.println("Hola mundo");
    }
}

public class CrearHiloExtend {
    public static void main(String[] args) {
        Hilo t = new Hilo();
        t.start();
    }
}
