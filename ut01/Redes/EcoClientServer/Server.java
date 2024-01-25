package ut01.Redes.EcoClientServer;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class Server {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Uso: java EjemploUDPServidor <puerto>");
            return;
        }

        try {
            int puerto = Integer.parseInt(args[0]);
            DatagramSocket socket = new DatagramSocket(puerto); // Abre el socket en el puerto 9876
            byte[] receivedData = new byte[1024];
            byte[] sendData = new byte[1024];
            InetAddress address;

            while (true) {
                DatagramPacket receivedPacket = new DatagramPacket(receivedData, receivedData.length);
                socket.receive(receivedPacket); // Espera y recibe el paquete
                puerto = receivedPacket.getPort();
                address = receivedPacket.getAddress();
                String message1 = new String(receivedPacket.getData(), 0, receivedPacket.getLength());
                System.out.println("He recibido de la ip " + address + " el mensaje: " + message1);
                String message = new String(receivedPacket.getData(), 0, receivedPacket.getLength());
                sendData = message.getBytes();

                DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, address, puerto);
                socket.send(sendPacket); // Envía el paquete al servidor
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
