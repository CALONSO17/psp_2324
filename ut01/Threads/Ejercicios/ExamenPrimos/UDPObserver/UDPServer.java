package ut01.Threads.Ejercicios.ExamenPrimos.UDPObserver;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.util.ArrayList;

public class UDPServer implements Runnable {
    // Interfaz para implementar el patrón Observer
    public interface LectorUDP {
        public void llegaronDatos(String dato);
    }

    private static final int MAX_LENGTH = 100;

    private ArrayList<LectorUDP> lectores;

    private int port;

    // Método para añadir un observador (lector)
    public void addLector(LectorUDP lector) {
        lectores.add(lector);
    }

    // Método para notificar a todos los observadores cuando llegan nuevos datos
    private void notificarLectoresNuevoDato(String dato) {
        for (LectorUDP l : lectores) {
            l.llegaronDatos(dato);
        }
    }

    // Constructor del servidor UDP
    public UDPServer(int port) {
        this.port = port;
        lectores = new ArrayList<LectorUDP>();
    }

    @Override
    public void run() {
        try {
            // Crear un socket UDP en el puerto especificado
            DatagramSocket socket = new DatagramSocket(port);
            byte[] buffer = new byte[MAX_LENGTH];

            while (true) {
                // Recibir datos en un paquete Datagram
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet); // Aquí se queda bloqueado hasta que llegan datos

                // Convertir los datos a una cadena y notificar a los observadores
                String dato = new String(packet.getData(), 0, packet.getLength());
                notificarLectoresNuevoDato(dato);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
