package ut01.Threads.Ejemplos;

public class PruebaThreadConStart extends Thread {
    private int countDown = 10;
    private static int taskCount = 0;
    private final int id = taskCount;
    
    public PruebaThreadConStart() {}
    
    public PruebaThreadConStart(int countDown) {
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
        
        PruebaThreadConStart launch = new PruebaThreadConStart();
        launch.start();
        PruebaThreadConStart prueba = new PruebaThreadConStart();
        prueba.start();
        prueba.toString();//Devuelve una representación legible de un thread [nombre, priority, nombre_del_grupo]
        prueba.isAlive();//Comprueba si un thread está vivo o no
        prueba.getId();//Devuelve el identificador del thread (es un id asignado por el proceso)
        Thread.yield();// Hace que el subproceso deje de ejecutarse en el momento en que vuelve a la cola y permite que se ejecuten otros subprocesos.
        try {
            prueba.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }//Se llama desde otro thread y hace que el thread que lo invoca se bloquee hasta que el thread termine. Es parecido a p.waitFor() para los procesos
        prueba.getName();//devuelve el nombre del thread
        //prueba.setName(null);//da un nuevo nombre al thread
        prueba.getPriority();
        prueba.setPriority(MAX_PRIORITY);
        //prueba.interrupt();//Interrumpe la ejecución del thread provocando que salte una excepción de tipo InterruptedException
        Thread.activeCount();//Devuelve el número de hilos pertenecientes a un grupo que siguen activos.
        prueba.getState();
        try {
            Thread.sleep(3000L);//3 segundos
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Comienza la cuenta atrás!");
        
    }    
}
/*Ahora el mensaje "Comienza la cuenta atrás!" sí aparece, en la salida, en la posición correcta, es decir, 
antes de la cuenta atrás. Si observamos el código, siguiendo una lógica secuencial, el mensaje debería aparecer después,
 como pasó en la primera prueba que hicimos.

La diferencia ahora es que el código del run() lo está ejecutando un hilo diferente,
 y desde el momento en que se hace el start() el control vuelve al hilo principal (main) que continúa ejecutando las líneas
  de código que hay en el método main. La creación de un hilo, aunque menos que la de un proceso,
 también tiene un coste de recursos y temporal, por lo que el hilo tarda unos instantes en empezar a ejecutarse.
  Por eso el hilo principal tiene tiempo de ejecutar la siguiente instrucción y mostrar el mensaje.

La gran diferencia ahora, que podemos observar en la salida, es que los hilos se están ejecutando concurrentemente, 
ya que vemos como sus salidas se intercalan.

Esa es la diferencia más obvia. Sin embargo, si ejecutamos el programa varias veces, 
podremos observar que no hay dos ejecuciones iguales. No depende de nosotros el orden en el que se ejecutan las instrucciones, 
sino que depende de la planificación que realice el SO. En este contexto nos encontramos con una ejecución aleatoria o 
indeterminista como la denominamos en el primer tema.

El cómo controlar ese orden es lo que trabajaremos en la segunda parte del tema. */
