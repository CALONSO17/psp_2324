package ut01.Redes;

import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class EjemploUDPServidor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Uso: java EjemploUDPServidor <puerto>");
            return;
        }

        try {
            int puerto = Integer.parseInt(args[0]);
            DatagramSocket socket = new DatagramSocket(puerto); // Abre el socket en el puerto 9876
            byte[] receivedData = new byte[1024];

            while (true) {
                DatagramPacket receivedPacket = new DatagramPacket(receivedData, receivedData.length);
                socket.receive(receivedPacket); // Espera y recibe el paquete

                // Extrae la información del paquete
                String message = new String(receivedPacket.getData(), 0, receivedPacket.getLength());
                System.out.println("Mensaje recibido: " + message);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}