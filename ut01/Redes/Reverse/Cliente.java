package ut01.Redes.Reverse;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class Cliente {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Uso: java EjemploUDPCliente <mensaje> <puerto>");
            return;
        }

        try {
            DatagramSocket socket = new DatagramSocket();
            InetAddress IPAddress = InetAddress.getByName("192.168.38.196"); // Dirección del servidor, mirarlo con ip a
            byte[] sendData = new byte[1024];
            byte[] receivedData = new byte[1024];
            String sentence = args[0]; // Mensaje a enviar
            int puerto = Integer.parseInt(args[1]);
            sendData = sentence.getBytes();

            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, puerto);
            socket.send(sendPacket); // Envía el paquete al servidor

            DatagramPacket receivedPacket = new DatagramPacket(receivedData, receivedData.length);
            socket.receive(receivedPacket); // Espera y recibe el paquete

            // Extrae la información del paquete
            String message = new String(receivedPacket.getData(), 0, receivedPacket.getLength());
            System.out.println("Mensaje recibido: " + message);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
