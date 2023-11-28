import java.io.IOException;

public class Comprimir{
    public static void main (String [] args) throws IOException{

        String nombre = args[0];
        nombre.replace("/", "_");
        nombre += "_2324_10_30.tar.gz";
        args[0].replace("/", "_");
        String [] commands = {
            "tar", "cvzf", nombre, args[0]
        };

        ProcessBuilder pb = new ProcessBuilder(commands);
        pb.inheritIO();
        Process p = pb.start();
    }
}