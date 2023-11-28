package ut01.Threads.Carrera;

public class Corredor implements Runnable {
    int kmRecorrido;
    int kmTotales;
    int dorsal;
    Object salida;
    public static final long TIEMPO_DESCANSO = 500;
    private static final double MAX_INTERVALO_KM = 10;
    
    public Corredor(int kmTotales, int dorsal, Object salida) {
        this.kmTotales = kmTotales;
        this.dorsal = dorsal;
        this.kmRecorrido = 0;
        this.salida = salida;
    }


    @Override
    public void run() {
        synchronized(salida){
            try {
                salida.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }   
        System.out.println(String.format("Soy el corredor %d y estoy empezando la carrera", dorsal));
        while(kmRecorrido < kmTotales){
            try {
                Thread.sleep((long)(Math.random() * TIEMPO_DESCANSO) + TIEMPO_DESCANSO);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            kmRecorrido += Math.random() * MAX_INTERVALO_KM;
            System.out.println(String.format("Soy el dorsal %d y voy por el km %d/%d", dorsal, kmRecorrido,kmTotales));
        }
        System.out.println(String.format("Soy el corredor %d, TERMINE!!", dorsal));
    }
    
}
