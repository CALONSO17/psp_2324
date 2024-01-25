package ut01.Threads.Ejercicios.ExamenPrimos.Bingo;

public class Bola {
    private int n;

    // Constructor que inicializa el número de la bola a -1 (no ha sido asignado)
    public Bola() {
        this.n = -1;
    }

    // Método para obtener el número de la bola
    public int getMsg() {
        return n;
    }

    // Método para asignar un número a la bola
    public void setMsg(int n) {
        this.n = n;
    }
}
