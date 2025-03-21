package computergraphics;

import util.Pair;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.*;

public class DigitalImageRepresentation {

    public static void main(String[] args) throws IOException {

        var image = bufferedImageFromCSVGrid(Pair.of("computergraphics/duke_pixels_grid_rgb.csv", true));

        File output = new File("src/main/resources/computergraphics/duke.png");
        ImageIO.write(image, "png", output);

    }

    public static BufferedImage bufferedImageFromCSVGrid(Pair<String, Boolean> fileNameAndContainsHeader) throws IOException {
        BufferedImage bufferedImage = new BufferedImage(96, 96, BufferedImage.TYPE_INT_RGB);

        InputStream inputStream = DigitalImageRepresentation.class.getClassLoader().getResourceAsStream(fileNameAndContainsHeader.getFirst());
        assert inputStream != null;
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));

        String line;
        boolean containsHeader = fileNameAndContainsHeader.getSecond();
        // Loop to set pixel colors based on CSV data
        while ((line = reader.readLine()) != null) {
            // Skip the CSV header
            if (containsHeader) {
                containsHeader = false;
                continue;
            }

            // Split line into X, Y, R, G, B values
            String[] values = line.split(",");
            int x = Integer.parseInt(values[0]);
            int y = Integer.parseInt(values[1]);
            int r = Integer.parseInt(values[2]);
            int g = Integer.parseInt(values[3]);
            int b = Integer.parseInt(values[4]);

            int rgb = (r << 16) | (g << 8) | b;  // Combine R, G, B into a single int
            bufferedImage.setRGB(x, y, rgb);  // Set pixel color
        }
        reader.close();
        return bufferedImage;
    }
}
