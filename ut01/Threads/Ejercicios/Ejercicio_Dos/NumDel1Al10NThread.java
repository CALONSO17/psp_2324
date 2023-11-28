package ut01.Threads.Ejercicios.Ejercicio_Dos;

import java.util.Scanner;

class Tabla implements Runnable{
    private static final int NUMEROS = 10;
    int num;

    public Tabla(int num){
        this.num = num;
    }

    public void run(){
        for(int i = 0; i < NUMEROS; i++){
            System.out.print(String.format("%d x %d = %d\n",num, i+1, (num*(i+1))));
        }
    }
}
public class NumDel1Al10NThread {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("¿Cuantos hilos quieres?\n");
        int nHilos = sc.nextInt();

        Thread[] hilos = new Thread[nHilos];

        Tabla[] tablas = new Tabla[nHilos];

        for (int i = 0; i < hilos.length; i++) {
            tablas[i] = new Tabla(i + 1);
            hilos[i] = new Thread(tablas[i]);
        }

        for (int i = 0; i < hilos.length; i++) {
            hilos[i].setName("Tabla del " + (i+1));
            System.out.println(hilos[i].getName());
            hilos[i].start();
        }

        for (int i = 0; i < hilos.length; i++) {
            try {
                hilos[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        sc.close();
    }
}
