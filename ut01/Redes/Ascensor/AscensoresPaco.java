package ut01.Redes.Ascensor;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

public class AscensoresPaco implements IAscensor {

    public int id;
    public InetAddress ip;
    public int puerto;
    public int pisoActual;

    HashMap<Integer, String> pisos = new HashMap<>();

    @Override
    public void config(int iden, String address, int port) {
        this.id = iden;
        try {
            this.ip = InetAddress.getByName(address);
        } catch (UnknownHostException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        this.puerto = port;
        pisos.put(-2, "S2");
        pisos.put(-1, "S1");
        pisos.put(0, "PB");
        pisos.put(1, "01");
        pisos.put(2, "02");
        pisos.put(3, "03");
        this.pisoActual = 0;
    }

    @Override
    public void run() {
        while (true) {
            try {
                DatagramSocket socket = new DatagramSocket();
                byte[] sendData = new byte[1024];
                String sentence = "Hols";// Mensaje a enviar
                sendData = sentence.getBytes();

                DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, ip, puerto);
                socket.send(sendPacket); // Envía el paquete al servidor
                socket.close();
                Thread.sleep(1000);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void subir() {
        getPlanta();
    }

    @Override
    public void bajar() {

    }

    @Override
    public String getPlanta() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'getPlanta'");
    }

    @Override
    public String toProtocolo() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'toProtocolo'");
    }

    @Override
    public IAscensor fromProtocolo(String info) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'fromProtocolo'");
    }

}
