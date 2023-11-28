import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
//javac Compresor.java 
//java Compresor /home/carlos
public class Compresor {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Debe proporcionar al menos una ruta de directorio como parámetro.");
            System.exit(1);
        }

        // Obtener la fecha actual en formato YYYY_MM_DD
        String fechaActual = new SimpleDateFormat("yyyy_MM_dd").format(new Date());

        for (String directorio : args) {
            comprimirDirectorio(directorio, fechaActual);
        }
    }

    private static void comprimirDirectorio(String directorio, String fecha) {
        try {
            // Obtener el nombre del directorio sin la ruta
            String nombreDirectorio = obtenerNombreDirectorio(directorio);

            // Construir el nombre del archivo comprimido con la fecha
            String nombreArchivo = nombreDirectorio + "_" + fecha + ".tar";

            // Construir el comando para comprimir el directorio
            ProcessBuilder processBuilder = new ProcessBuilder("tar", "cf", nombreArchivo, directorio);

            // Iniciar el proceso
            Process proceso = processBuilder.start();

            // Esperar a que el proceso termine
            int exitCode = proceso.waitFor();

            // Imprimir el código de salida del proceso
            System.out.println("Directorio '" + directorio + "' comprimido como '" + nombreArchivo +
                    "' con código de salida: " + exitCode);

        } catch (IOException | InterruptedException e) {
            // Manejar posibles excepciones
            e.printStackTrace();
        }
    }

    private static String obtenerNombreDirectorio(String rutaDirectorio) {
        // Obtener el nombre del directorio sin la ruta
        int ultimaBarra = rutaDirectorio.lastIndexOf("/");
        if (ultimaBarra != -1) {
            return rutaDirectorio.substring(ultimaBarra + 1);
        } else {
            return rutaDirectorio; // La ruta es solo el nombre del directorio
        }
    }
}
