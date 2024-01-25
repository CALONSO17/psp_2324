package ut01.Redes.Chat_V2;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class Servidor {
    static int puerto;
    static byte[] receivedData;
    static byte[] sendData;
    static DatagramSocket socket;
    static DatagramPacket receivedPacket;
    static InetAddress address;
    static String message;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        try {
            puerto = 9876;
            receivedData = new byte[1024];
            socket = new DatagramSocket(9876);

            Thread receiveThread = new Thread(() -> {
                while (true) {
                    recibirMensaje();
                }
            });
            receiveThread.start();

            while (true) {
                // escribimos nuevo mensaje
                message = sc.nextLine();
                Servidor.mandarMensaje(message);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void recibirMensaje() {
        try {
            receivedPacket = new DatagramPacket(receivedData, receivedData.length);
            socket.receive(receivedPacket);
            message = new String(receivedPacket.getData(), 0, receivedPacket.getLength());
            System.out.println(message);
            puerto = receivedPacket.getPort();
            address = receivedPacket.getAddress();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static void mandarMensaje(String mensaje) {
        try {
            sendData = mensaje.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, address, puerto);
            socket.send(sendPacket);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
