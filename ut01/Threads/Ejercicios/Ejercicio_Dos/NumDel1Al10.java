package ut01.Threads.Ejercicios.Ejercicio_Dos;

class MyRunnable2 implements Runnable{
    private static final int NUMEROS = 10;

    public void run(){
        for(int i = 0; i < NUMEROS; i++){
            System.out.print((i + 1) + "\t");
        }
    }
}
public class NumDel1Al10{
    public static void main(String[] args) {
        Thread t1 = new Thread(new MyRunnable2());
        t1.start();
    }
}
