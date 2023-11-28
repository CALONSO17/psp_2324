import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class ListadoUsoEspacio {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Debe proporcionar al menos una ruta.");
            return;
        }

        for (String ruta : args) {
            ejecutarComando("du -h " + ruta + " | tail -1");
        }
    }

    public static void ejecutarComando(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder("/bin/bash", "-c", command);

        try {
            Process process = processBuilder.start();
            int exitCode = process.waitFor();

            if (exitCode == 0) {
                imprimirResultado(process.getInputStream());
            } else {
                imprimirError(process.getErrorStream());
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void imprimirResultado(InputStream inputStream) throws IOException {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }
    }

    public static void imprimirError(InputStream errorStream) throws IOException {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(errorStream))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.err.println(line);
            }
        }
    }
}


/*
Para mostrar la salida ordenada en un fichero
alberto@alberto-VirtualBox:~/PSP2324$ java ut02.Procesos.ListadoUsoEspacio /home/alberto /home > salida.txt
alberto@alberto-VirtualBox:~/PSP2324$ sort salida.txt
 */ 
