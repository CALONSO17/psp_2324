package ut01.Threads.Ejemplos.EjemploSincro;

// Clase que representa un escritor de libros implementando la interfaz Runnable
public class EscritorDeLibros implements Runnable {
    // Libro que el escritor está completando
    Libro libro;

    // Constructor de la clase
    public EscritorDeLibros(Libro libro) {
        super();
        this.libro = libro;
    }

    // Método run que se ejecuta cuando se inicia el hilo
    @Override
    public void run() {
        // Bloque sincronizado para garantizar la coherencia en el acceso al libro
        synchronized (libro) {
            // Imprime un mensaje indicando que el escritor está comenzando a escribir el
            // libro
            System.out.println("El autor está comenzando el libro: " + libro.getTitulo());
            try {
                // Simula el proceso de escritura con una pausa de 1000 milisegundos (1 segundo)
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            // Establece que el libro ha sido completado
            libro.setCompletado(true);
            // Imprime un mensaje indicando que el libro ha sido completado
            System.out.println("El libro se ha completado ahora");

            // Notifica a un lector que el libro ha sido completado
            libro.notify();
            // Imprime un mensaje indicando que se ha notificado a un lector
            System.out.println("Notificar a un lector");
        }
    }
}
