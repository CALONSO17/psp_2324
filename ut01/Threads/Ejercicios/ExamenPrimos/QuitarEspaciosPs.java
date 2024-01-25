package ut01.Threads.Ejercicios.ExamenPrimos;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class QuitarEspaciosPs {

    private static final int CAMPO_USER = 0;
    private static final int CAMPO_MEM = 3;
    private static final String MEM_CERO = "0.0";

    // Método para eliminar espacios duplicados en una cadena.
    public static String removeEspacios(String cadena) {
        String limpia = "";
        boolean espacio = false;
        for (int i = 0; i < cadena.length(); i++) {
            if (cadena.charAt(i) != ' ') {
                espacio = false;
                limpia += cadena.charAt(i);
            } else {
                if (!espacio) {
                    limpia += ' ';
                }
                espacio = true;
            }
        }
        return limpia;
    }

    public static void main(String[] args) throws IOException {

        // Ejecutar el comando "ps aux" para obtener información del sistema.
        Process p = new ProcessBuilder("ps", "aux").start();
        try {
            // Crear un lector para la salida del proceso.
            BufferedReader lector = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String linea;

            boolean primera = true;
            while ((linea = lector.readLine()) != null) {
                if (primera) {
                    // Imprimir la primera línea sin filtrar.
                    System.out.println(linea);
                    primera = false;
                } else {
                    // Dividir la línea en partes, eliminar espacios duplicados y verificar el
                    // usuario y la memoria.
                    String[] cachos = removeEspacios(linea).split(" ");
                    if (cachos[CAMPO_USER].equals(args[0]) && !cachos[CAMPO_MEM].equals(MEM_CERO)) {
                        // Imprimir la línea si el usuario coincide y la memoria no es cero.
                        System.out.println(linea);
                    }
                }
            }
            lector.close();

        } catch (Exception e) {
            e.printStackTrace();
        }

        // Comprobación del valor de salida del proceso. 0 significa bien, 1 significa
        // mal.
        int exitVal;
        try {
            exitVal = p.waitFor();
            System.out.println("Valor de Salida: " + exitVal);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
