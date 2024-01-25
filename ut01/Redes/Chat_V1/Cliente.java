package ut01.Redes.Chat_V1;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class Cliente {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        try {
            DatagramSocket socket = new DatagramSocket();
            InetAddress IPAddress = InetAddress.getByName("192.168.1.149"); // Dirección del servidor, mirarlo con ip a
            byte[] sendData = new byte[1024];
            byte[] receivedData = new byte[1024];
            String sentence = sc.nextLine(); // Mensaje a enviar
            int puerto = 9876;
            sendData = sentence.getBytes();

            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, puerto);
            socket.send(sendPacket); // Envía el paquete al servidor

            while (true) {
                DatagramPacket receivedPacket = new DatagramPacket(receivedData, receivedData.length);
                socket.receive(receivedPacket); // Espera y recibe el paquete
                // Extrae la información del paquete
                String message = new String(receivedPacket.getData(), 0, receivedPacket.getLength());
                System.out.println(message);
                puerto = receivedPacket.getPort();
                IPAddress = receivedPacket.getAddress();
                // escribimos nuevo mensaje
                message = sc.nextLine();
                sendData = message.getBytes();

                sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, puerto);
                socket.send(sendPacket); // Envía el paquete al servidor
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
