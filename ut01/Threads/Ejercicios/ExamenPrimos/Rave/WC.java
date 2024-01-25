package ut01.Threads.Ejercicios.ExamenPrimos.Rave;

public class WC {

    private boolean ocu;

    // Constructor que inicializa el estado del baño como libre
    public WC() {
        ocu = false;
    }

    // Método para verificar si el baño está ocupado
    public boolean ocupado() {
        return ocu;
    }

    // Método para indicar que alguien ha entrado al baño
    public void entra() {
        ocu = true;
    }

    // Método para indicar que alguien ha salido del baño
    public void sal() {
        ocu = false;
    }
}
