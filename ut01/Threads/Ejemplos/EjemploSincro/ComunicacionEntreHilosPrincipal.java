package ut01.Threads.Ejemplos.EjemploSincro;

// Clase principal que demuestra la comunicación entre hilos
public class ComunicacionEntreHilosPrincipal {

    // Método principal
    public static void main(String args[]) {
        // Objeto de libro sobre el cual se llamará al método wait y notify
        Libro libro = new Libro("El Alquimista");

        // Lectores de libros que esperarán la finalización del libro
        LectorDeLibros johnLector = new LectorDeLibros(libro);
        LectorDeLibros arpitLector = new LectorDeLibros(libro);

        // Hilos de lectores de libros que esperarán la finalización del libro
        Thread hiloJohn = new Thread(johnLector, "John");
        Thread hiloArpit = new Thread(arpitLector, "Arpit");

        // Inicia los hilos de los lectores
        hiloArpit.start();
        hiloJohn.start();

        // Para asegurarse de que ambos lectores hayan comenzado a esperar el libro
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Hilo del escritor de libros que notificará una vez que el libro esté
        // completado
        EscritorDeLibros escritorDeLibros = new EscritorDeLibros(libro);
        Thread hiloEscritorDeLibros = new Thread(escritorDeLibros);
        hiloEscritorDeLibros.start();
    }
}
