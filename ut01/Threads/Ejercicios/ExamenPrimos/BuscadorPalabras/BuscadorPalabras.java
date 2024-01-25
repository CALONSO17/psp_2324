package ut01.Threads.Ejercicios.ExamenPrimos.BuscadorPalabras;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

public class BuscadorPalabras implements Runnable {

    String[] rutas;
    String busqueda;
    File localizacion;
    int ini;
    int fin;
    int count;

    // Constructor que inicializa los atributos de la clase.
    public BuscadorPalabras(String[] rutas, File localizacion, String busqueda, int ini, int fin) {
        this.rutas = rutas;
        this.busqueda = busqueda;
        this.localizacion = localizacion;
        this.ini = ini;
        this.fin = fin;
        count = 0;
    }

    @Override
    public void run() {
        // Bucle que itera sobre el rango de rutas asignado a este hilo.
        for (int i = ini; i < fin; i++) {
            // Procesar: Buscar y contar ocurrencias en cada archivo.
            int c = encuentraYCuenta(rutas[i], busqueda);
            count += c;
            System.out.println("Aparece en " + rutas[i] + " " + c + " veces");
        }
    }

    // Método privado que busca y cuenta ocurrencias de una cadena en un archivo.
    private int encuentraYCuenta(String ruta, String busqueda) {
        int c = 0;
        try {
            // Crear un lector para el archivo.
            BufferedReader br = new BufferedReader(new FileReader(localizacion + "/" + ruta));
            String line;

            // Leer el archivo línea por línea.
            while ((line = br.readLine()) != null) {
                // Verificar si la línea contiene la cadena de búsqueda.
                if (line.contains(busqueda)) {
                    c++;
                }
            }
        } catch (Exception e) {
            // Manejo de errores en caso de problemas con el archivo.
            System.err.println("Ocurrió un error en el fichero " + ruta);
            System.err.println(e);
        }
        return c;
    }

    // Método público que devuelve el recuento total de ocurrencias.
    public int getCount() {
        return count;
    }
}
