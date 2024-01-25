package ut01.Threads.Ejercicios.ExamenPrimos.DivisoresPrimos;

public class DivisoresPrimos implements Runnable {
    private int start;
    private int end;
    private int number;

    // Constructor que recibe tres parámetros e inicializa los campos de la clase.
    public DivisoresPrimos(int start, int end, int number) {
        this.start = start;
        this.end = end;
        this.number = number;
    }

    // Implementación del método run() de la interfaz Runnable.
    @Override
    public void run() {
        // Bucle que recorre los números desde 'start' hasta 'end - 1'.
        for (int i = start; i < end; i++) {
            // Verifica si 'i' divide de forma entera a 'number' y si 'i' es primo.
            if (divideDeFormaEntera(i, number) && esPrimo(i)) {
                // Imprime el número si cumple ambas condiciones.
                System.out.print(i + " ");
            }
        }
    }

    // Método privado que verifica si 'i' divide de forma entera a 'n'.
    private boolean divideDeFormaEntera(int i, int n) {
        return (n % i) == 0;
    }

    // Método privado que verifica si 'n' es primo.
    private boolean esPrimo(int n) {
        boolean esPrimo = true;
        int i = 2;
        // Bucle que verifica si 'n' es divisible por algún número desde 2 hasta la raíz
        // cuadrada de 'n'.
        while (esPrimo && i <= Math.sqrt(n)) {
            if (n % i == 0) {
                // Si 'n' es divisible, entonces no es primo.
                esPrimo = false;
            }
            i++;
        }
        // Devuelve true si 'n' es primo, de lo contrario, devuelve false.
        return esPrimo;
    }
}
