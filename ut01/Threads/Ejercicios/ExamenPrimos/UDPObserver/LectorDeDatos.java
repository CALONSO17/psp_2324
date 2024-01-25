package ut01.Threads.Ejercicios.ExamenPrimos.UDPObserver;

public class LectorDeDatos implements UDPServer.LectorUDP {

    String id;

    // Constructor que asigna un identificador al lector
    public LectorDeDatos(String id) {
        this.id = id;
    }

    // Implementación del método de la interfaz LectorUDP para manejar la llegada de
    // datos
    @Override
    public void llegaronDatos(String dat) {
        // Imprimir en la consola el mensaje indicando que el lector ha recibido datos
        System.out.println(id + " recibe: " + dat);
    }
}
