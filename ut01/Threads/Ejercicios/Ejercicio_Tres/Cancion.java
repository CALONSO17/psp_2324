package ut01.Threads.Ejercicios.Ejercicio_Tres;

import java.util.Scanner;

class LosPajaritos implements Runnable{

    @Override
    public void run() {
        System.out.println("Pajaritos por aqui, pajaritos por alla\n");
    }
    
}

class CorroPatata implements Runnable{

    @Override
    public void run() {
        System.out.println("Al corro de la patata, comeremos ensalada\n");
    }
    
}

class LosElefantes implements Runnable{
    private static final int MAX_RANDOM = 300000;
    private static final int MIN_RANDOM = 100000;
    String animal;
    String accion;
    int numMaximo;

    public LosElefantes(String animal, String accion, int numMaximo){
        this.animal = animal;
        this.accion = accion;
        this.numMaximo = numMaximo;
    }

    @Override
    public void run() {
        int j = 2;
        boolean esPrimo = true;
        String primo;

        for(int i  = 0; i < numMaximo; i++){
            int numRandom = (int)Math.floor(Math.random() * (MAX_RANDOM-MIN_RANDOM+1)) + MIN_RANDOM;

            while(esPrimo && j <= Math.sqrt(numRandom)){
                if(numRandom % j == 0){
                    esPrimo = false;
                }
                j++;
            }

            if(esPrimo){
                primo = "es primo";
            }else{
                primo = "no es primo";
            }
            
            if(i > 0){
                System.out.println(String.format("%d %ss, se balanceaban sobre la tela de una araña\n" + 
                "como veian que se %sn fueron a llamar a otro %s", i + 1, animal, accion, animal ));
            }else{
                System.out.println(String.format("%d %s, se balanceaba sobre la tela de una araña\n" + 
                    "como veia que se %s fue a llamar a otro %s", i + 1, animal, accion, animal ));
            }
            System.out.println(String.format("El numero %d %s\n", numRandom, primo));
        }
    }
    
}
public class Cancion {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String animal, accion;
        int numEstrofas;

        System.out.print("---CANCION---\nDime un animal: ");
        animal = sc.nextLine();
        System.out.print("\nDime una accion(ej.resistia): ");
        accion = sc.nextLine();
        System.out.print("\nAhora dime cuantas veces quieres la estrofa: ");
        numEstrofas = sc.nextInt();
        System.out.println();

        Thread tElefantes = new Thread(new LosElefantes(animal, accion, numEstrofas));
        Thread tPajarito = new Thread(new LosPajaritos());
        Thread tPatata = new Thread(new CorroPatata());

        tElefantes.setPriority(2);
        tPajarito.setPriority(3);
        tPatata.setPriority(4);

        tElefantes.start();
        tPajarito.start();
        tPatata.start();
        sc.close();
    }
}
