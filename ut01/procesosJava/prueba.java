
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;


public class prueba {

    public static void main(String[] args) {
        // Intervalo de tiempo en segundos
        int intervaloSegundos = 5;

        while (true) {
            executeFreeCommand();
            // Esperar el intervalo antes de ejecutar de nuevo
            try {
                Thread.sleep(intervaloSegundos);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private static void executeFreeCommand() {
        try {
            // Crear el objeto ProcessBuilder para el comando free -h
            ProcessBuilder processBuilder = new ProcessBuilder("free", "-h");

            // Iniciar el proceso
            Process process = processBuilder.start();

            // Capturar la salida del proceso y mostrarla en la consola
            captureProcessOutput(process);

            // Esperar a que el proceso termine
            int exitCode = process.waitFor();

            // Imprimir el código de salida del proceso
            System.out.println("Proceso free -h terminado con código de salida: " + exitCode);
        } catch (IOException | InterruptedException e) {
            // Manejar posibles excepciones
            e.printStackTrace();
        }
    }

    private static void captureProcessOutput(Process process) {
        // Capturar la salida del proceso y mostrarla en la consola
        try (InputStream inputStream = process.getInputStream();
             InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
             BufferedReader bufferedReader = new BufferedReader(inputStreamReader)) {

            String line;
            System.out.println("Estado de la memoria del sistema:");
            while ((line = bufferedReader.readLine()) != null) {
                System.out.println(line);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}