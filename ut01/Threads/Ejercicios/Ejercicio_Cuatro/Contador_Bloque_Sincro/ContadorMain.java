package ut01.Threads.Ejercicios.Ejercicio_Cuatro.Contador_Bloque_Sincro;

/*Crea una clase Counter con un método sincronizado increment que incremente una variable count.
 Crea dos hilos que incrementen el contador y observa el resultado. Modifica la clase Counter anterior para usar un bloque sincronizado en 
 lugar de un método sincronizado.

Modificación 04a
Modifica el ejercicio para poder incrementar y decrementar, crea 5 hilos que incrementen 1000 veces y 5 que decrementen 1000 veces. 
Muestra el resultado de hacer esta operación con sincronización y sin sincornización. */

public class ContadorMain {
    public static final int VECES = 1000;

    public static void main(String[] args) {
        Contador c = new Contador(0);

        Thread t1 = new Thread(new Incrementador(c));
        Thread t2 = new Thread(new Decrementador(c));

        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException i) {
            i.getMessage();
        }

        System.out.println(String.format("El contenido es: %s", c));
    }
}
