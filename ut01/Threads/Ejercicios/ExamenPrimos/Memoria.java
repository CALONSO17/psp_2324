package ut01.Threads.Ejercicios.ExamenPrimos;

// javac Memoria.java
// salir a la raiz del paquete y ejecutar java ut01.Threads.Ejercicios.ExamenPrimos.Memoria carlos

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Memoria {

    public static void main(String[] args) {
        // Verificación de parámetros
        if (args.length != 1) {
            System.err.println("Uso: java Memoria <nombre_usuario>");
            System.exit(1);
        }

        String usuario = args[0];

        try {
            // Construir el comando "ps aux" y ejecutarlo
            ProcessBuilder processBuilder = new ProcessBuilder("ps", "aux");
            Process process = processBuilder.start();

            // Obtener la salida del comando
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;

            // Imprimir la cabecera
            if ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            // Procesar y mostrar los procesos del usuario con más del 0.0% de memoria
            while ((line = reader.readLine()) != null) {
                if (line.contains(usuario) && !line.contains(" 0.0 ")) {
                    System.out.println(line);
                }
            }

            // Esperar a que el proceso termine y obtener el valor de salida
            int exitValue = process.waitFor();
            System.out.println("Valor de Salida: " + exitValue);

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}
