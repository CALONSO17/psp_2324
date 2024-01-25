package ut01.Threads.Ejercicios.ExamenPrimos.UDPObserver;

public class Principal {

    public static void main(String[] args) {
        // Crear una instancia de UDPServer en el puerto 4321
        UDPServer server = new UDPServer(4321);

        // Crear dos lectores de datos
        LectorDeDatos l1 = new LectorDeDatos("Paco");
        LectorDeDatos l2 = new LectorDeDatos("Amparo");

        // Agregar los lectores al servidor
        server.addLector(l1);
        server.addLector(l2);

        // Iniciar un hilo para ejecutar el servidor UDP
        new Thread(server).start();
    }

}
