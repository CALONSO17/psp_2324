package ut01.Redes.Chat_V1;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class Servidor {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        try {
            int puerto = 9876;
            DatagramSocket socket = new DatagramSocket(9876); // Abre el socket en el puerto 9876
            byte[] receivedData = new byte[1024];
            byte[] sendData = new byte[1024];
            InetAddress address;

            while (true) {
                DatagramPacket receivedPacket = new DatagramPacket(receivedData, receivedData.length);
                socket.receive(receivedPacket); // Espera y recibe el paquete
                // Extrae la información del paquete
                String message = new String(receivedPacket.getData(), 0, receivedPacket.getLength());
                System.out.println(message);
                puerto = receivedPacket.getPort();
                address = receivedPacket.getAddress();
                // escribimos nuevo mensaje
                message = sc.nextLine();
                sendData = message.getBytes();

                DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, address, puerto);
                socket.send(sendPacket); // Envía el paquete al servidor
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
