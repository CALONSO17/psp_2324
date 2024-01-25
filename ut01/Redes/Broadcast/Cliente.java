package ut01.Redes.Broadcast;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class Cliente {
    static DatagramSocket socket;
    static InetAddress IPAddress;
    static byte[] sendData;
    static byte[] receivedData;
    static String sentence;
    static int puerto;
    static DatagramPacket sendPacket;
    static DatagramPacket receivedPacket;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        try {
            socket = new DatagramSocket();
            IPAddress = InetAddress.getByName("192.168.180.196"); // Dirección del servidor, mirarlo con ip a
            receivedData = new byte[1024];
            sentence = sc.nextLine(); // Mensaje a enviar
            puerto = 9876;

            Cliente.mandarMensaje(sentence);

            while (true) {
                Cliente.recibirMensaje();
                // escribimos nuevo mensaje
                sentence = sc.nextLine();
                Cliente.mandarMensaje(sentence);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void recibirMensaje() {
        try {
            receivedPacket = new DatagramPacket(receivedData, receivedData.length);
            socket.receive(receivedPacket);
            sentence = new String(receivedPacket.getData(), 0, receivedPacket.getLength());
            System.out.println(sentence);
            puerto = receivedPacket.getPort();
            IPAddress = receivedPacket.getAddress();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static void mandarMensaje(String mensaje) {
        try {
            sendData = mensaje.getBytes();
            sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, puerto);
            socket.send(sendPacket);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
