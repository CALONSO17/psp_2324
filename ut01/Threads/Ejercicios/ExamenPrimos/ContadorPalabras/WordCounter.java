package ut01.Threads.Ejercicios.ExamenPrimos.ContadorPalabras;

import java.io.BufferedReader;
import java.io.FileReader;

public class WordCounter implements Runnable {
    public static final int NUM_LETRAS = ('z' - 'a') + 1; // 26
    private static final int EOF = -1;
    private String ruta;
    private int[] contadoresLetras;

    // Constructor que recibe la ruta del fichero y crea un array para contadores de
    // letras.
    public WordCounter(String rutaFichero) {
        ruta = rutaFichero;
        contadoresLetras = new int[NUM_LETRAS];
    }

    @Override
    public void run() {
        try {
            // Se crea un lector de archivos para leer el contenido del fichero.
            BufferedReader reader = new BufferedReader(new FileReader(ruta));
            int c;

            // Mientras haya datos en el fichero.
            while ((c = reader.read()) != EOF) {
                // Procesar: incrementar el contador correspondiente a la letra en el array.
                if ('a' <= c && c <= 'z') { // minúsculas
                    contadoresLetras[c - 'a']++;
                } else if ('A' <= c && c <= 'Z') { // mayúsculas
                    contadoresLetras[c - 'A']++;
                }
            }

            // Finalizar: cerrar el lector de archivos.
            reader.close();
        } catch (Exception e) {
            // Manejo básico de excepciones, puede ser mejorado según los requisitos.
        }
    }

    /*
     * OPCIÓN 1
     * Devuelve el contador de una letra específica.
     */
    public int getCount(char c) {
        if ('a' <= c && c <= 'z') { // minúsculas
            return contadoresLetras[c - 'a'];
        } else if ('A' <= c && c <= 'Z') { // mayúsculas
            return contadoresLetras[c - 'A'];
        }
        return 0;
    }

    /*
     * OPCIÓN 2
     * Devuelve el array completo de contadores de letras.
     */
    public int[] getCounter() {
        return contadoresLetras;
    }
}
