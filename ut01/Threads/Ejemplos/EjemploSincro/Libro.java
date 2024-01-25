package ut01.Threads.Ejemplos.EjemploSincro;

// Clase que representa un libro
public class Libro {
    // Atributos de la clase
    String titulo; // Título del libro
    boolean estaCompletado; // Indica si el libro está completado o no

    // Constructor de la clase
    public Libro(String titulo) {
        super();
        this.titulo = titulo;
    }

    // Método para obtener el título del libro
    public String getTitulo() {
        return titulo;
    }

    // Método para establecer el título del libro
    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    // Método para verificar si el libro está completado
    public boolean estaCompletado() {
        return estaCompletado;
    }

    // Método para establecer si el libro está completado o no
    public void setCompletado(boolean estaCompletado) {
        this.estaCompletado = estaCompletado;
    }
}
