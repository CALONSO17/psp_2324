package ut01.Threads.Carrera;

import java.util.Scanner;

public class Principal {
    private static final int KILOMETROS_TOTALES = 100;

    public static void main(String[] args) {
        Object salida = new Object();
        Scanner sc = new Scanner(System.in);
        int nCorredores, num;
        System.out.print("¿Cuantos corredores hay en la carrera?\n");
        nCorredores = sc.nextInt();

        Thread[] hilos = new Thread[nCorredores];

        Corredor[] corredores = new Corredor[nCorredores];

        for (int i = 0; i < corredores.length; i++) {
            corredores[i] = new Corredor(KILOMETROS_TOTALES, i + 1, salida);
            hilos[i] = new Thread(corredores[i]);
        }

        System.out.println("La carrera va a comenzar");


        for (int i = 0; i < hilos.length; i++) {
            hilos[i].start();
        }
        System.out.println("Usuario, pulsa cuando quieras empezar");
        num = sc.nextInt();
        synchronized (salida) {
            salida.notifyAll();
        }

        for (int i = 0; i < hilos.length; i++) {
            try {
                hilos[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.out.println("La carrera ha terminado");
        sc.close();
    }
}

