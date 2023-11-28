package ut01.Threads.Ejemplos;

public class PruebaThread implements Runnable {
    private int countDown = 10;
    private static int taskCount = 0;
    private final int id = taskCount;
    
    public PruebaThread() {}
    
    public PruebaThread(int countDown) {
        this.countDown = countDown;
    }
    
    @Override
    public void run() {
        while (countDown > 0) {
            System.out.println("#" + id + " (" + countDown + ")" );
            countDown--;
        }
        System.out.println("Lanzamiento (" + id + ")");
    }
    
    public static void main(String[] args) {
        System.out.println("Comienza la cuenta atrás!");
        PruebaThread launch = new PruebaThread();
        PruebaThread prueba = new PruebaThread();
        launch.run();
        prueba.run();
        
    }    
}
/*El mensaje debería mostrarse antes que la cuenta atrás. De hecho la instrucción con el System.out está después de la llamada al método run.

Como se puede observar, no estamos haciendo nada diferente. El código de run se está ejecutando uno después de otro.

En realidad, no estamos creando nuevos threads, lo único que hemos hecho hasta ahora es implementar una interfaz, 
pero llamando al método run estamos haciendo que el hilo principal de la aplicación, el único hilo de momento, 
esté ejecutando un método run, después otro, después otro, ... y cuando ha acabado con todos hace el System.out. */