package ut01.Threads.Ejemplos;

public class OrdenarTresNumeros {
    public static void main(String[] args) {
        int a = 1, b = 8, c = 6;
        
        if (a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        
        if (b > c) {
            int temp = b;
            b = c;
            c = temp;
        }
        
        if (a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        
        System.out.println("Números ordenados: " + a + ", " + b + ", " + c);
    }
}
