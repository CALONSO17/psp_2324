package ut01.Threads.Ejemplos;

class U3S3_HiloPrioridad1 extends Thread {
  private int c = 0;
  private boolean stopHilo = false;
  public long getContador () {
    return c;
  }
  public void pararHilo() {
    stopHilo = true;
  }
  @Override
  public void run() {
    while (!stopHilo) c++;
  }
}

public class PrioridadHilos {
  public static void main(String args[]) {
    U3S3_HiloPrioridad1 h1 = new U3S3_HiloPrioridad1();
    U3S3_HiloPrioridad1 h2 = new U3S3_HiloPrioridad1();
    U3S3_HiloPrioridad1 h3 = new U3S3_HiloPrioridad1();

    h1.setPriority(Thread.NORM_PRIORITY);
    h2.setPriority(Thread.MAX_PRIORITY);
    h3.setPriority(Thread.MIN_PRIORITY);

    h1.start();
    h2.start();
    h3.start();

    try {
      Thread.sleep(10000);
        } catch (InterruptedException e) {}

    h1.pararHilo();
    h2.pararHilo();
    h3.pararHilo();

    System.out.println("h2 (Prio. Máx: "+h2.getContador());
    System.out.println("h1 (Prio. Normal: "+h1.getContador());
    System.out.println("h3 (Prio. Mínima: "+h3.getContador());
  }
}
/*Los hilos heredan la prioridad del padre en Java, pero este valor puede ser cambiado con el método setPriority() y con getPriority() 
podemos saber la prioridad de un hilo.

El valor de la prioridad varía entre 1 y 10. Cuanto más alto es el valor, mayor es la prioridad. 
La clase Thread define las siguientes constantes MIN_PRIORITY (valor 1) MAX_PRIORITY (valor 10) y NORM_PRIORITY (valor 5). 
El planificador elige el hilo en función de su prioridad. Si dos hilos tienen la misma prioridad realiza un round-robin, 
es decir de forma cíclica va alternando los hilos.

El hilo de mayor prioridad seguirá funcionando hasta que ceda el control:

Cede el control llamando al método yield().
Deja de ser ejecutable (por muerte o por bloqueo)
Aparece un hilo de mayor prioridad, por ejemplo si se encontraba en estado dormido por una operación de E/S o bien es 
desbloqueado por otro con los métodos notifyAll() / notify(). */
