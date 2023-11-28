package ut01.Threads.Ejercicios.Ejercicio_Cinco;

/*Imagina un sistema de banco en línea que maneja las cuentas de los usuarios. Dos usuarios, Alice y Bob, 
intentan transferir dinero de sus cuentas a una tercera cuenta al mismo tiempo. Necesitas asegurarte de que las operaciones se realicen de 
manera segura y sin conflictos, utilizando sincronización.

Crea dos threads, uno para cada usuario. Cada thread intentará realizar 1000 transferencia de dinero de 10 euros.
 Usa un método synchronized para asegurar que las operaciones en las cuentas no se realicen simultáneamente, evitando así condiciones de carrera. */
public class Banco {
    public static final int VECES = 100000;

    public static void main(String[] args) {
        Transferencia t = new Transferencia(0);

        Thread alice = new Thread(new Cliente(t));
        Thread bob = new Thread(new Cliente(t));

        alice.start();
        bob.start();

        try {
            alice.join();
            bob.join();
        } catch (InterruptedException i) {
            i.getMessage();
        }

        System.out.println(String.format("El contenido es: %s", t));
    }
}
