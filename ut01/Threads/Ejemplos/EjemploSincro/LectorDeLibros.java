package ut01.Threads.Ejemplos.EjemploSincro;

// Clase que representa un lector de libros implementando la interfaz Runnable
public class LectorDeLibros implements Runnable {
    // Libro que el lector está esperando leer
    Libro libro;

    // Constructor de la clase
    public LectorDeLibros(Libro libro) {
        super();
        this.libro = libro;
    }

    // Método run que se ejecuta cuando se inicia el hilo
    @Override
    public void run() {
        // Bloque sincronizado para garantizar la coherencia en el acceso al libro
        synchronized (libro) {
            // Imprime un mensaje indicando que el hilo está esperando a que se complete el
            // libro
            System.out.println(Thread.currentThread().getName() + " está esperando a que se complete el libro: "
                    + libro.getTitulo());
            try {
                // El hilo se bloquea y espera a que se complete el libro (se llama a wait)
                libro.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            // Una vez que el libro ha sido completado, el hilo imprime un mensaje indicando
            // que puede leerlo
            System.out.println(Thread.currentThread().getName() + ": ¡El libro se ha completado! Ahora puedes leerlo");
        }
    }
}
