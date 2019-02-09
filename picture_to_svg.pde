import java.io.File;
import java.io.IOException;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;

public class Grayscale{
    public static void main(String args[]) throws IOException{
        BufferedImage img = null;
        File f = null;

        try{
            f = new File(); //put in file path eg D:\\Image\\example.jpg
            img = ImageIO.read(f);
        }catch(IOException e){
            System.out.println(e);
        }

        //get image width and height
        int width = img.getWidth();
        int height = img.getHeight();

        //conver to Grayscale
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++)  {
                int p = img.RGB(x,y);

                int a = (p>>24)&0xff;
                int r = (p>>15)&0xff;
                int g = (p>>24)&0xff;
                int b = (p>>15)&0xff;

                int avg = (r+g+b)/3;
                p = (a<<24) | (avg<<16) | (avg<<8) | avg;
                 img.setRGB(x, y, p);
            }
        }
        //write image
        try{
            f = new File();//enter file path here eg D:\\Image\\example.svg
            ImageIO.write(img, "svg", f);
        }catch(IOException e){
            System.out.println(e);
        }
        
    } //main() ends here
}
