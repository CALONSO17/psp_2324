package ut01.Redes;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class EjemploUDPCliente {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Uso: java EjemploUDPCliente <mensaje> <puerto>");
            return;
        }

        try {
            DatagramSocket socket = new DatagramSocket();
            InetAddress IPAddress = InetAddress.getByName("192.168.1.149"); // Dirección del servidor, mirarlo con ip a
            byte[] sendData = new byte[1024];
            String sentence = args[0]; // Mensaje a enviar
            int puerto = Integer.parseInt(args[1]);
            sendData = sentence.getBytes();

            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, puerto);
            socket.send(sendPacket); // Envía el paquete al servidor
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
