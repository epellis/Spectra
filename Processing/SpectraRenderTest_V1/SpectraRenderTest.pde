/*
  3D matrix used to store the pixels displayed to the screen
  Format: {X-Coordinate, Y-Coordinate, RGB Value}
*/
int[][][] display;

int spacer;  // Space between the center of each dot
int displayResolution = 8;  // Amount of LEDs on each side of the display

final int temperature = (int)(Math.random() * 255);

final int targetRed = 64 + (temperature / 2);
final int targetGreen = 192 - Math.abs(128 - temperature);
final int targetBlue = 192 - (temperature / 2);

void setup() {
  
  /* Initialize overhead variables */
  size(360, 360);
  display = new int[displayResolution][displayResolution][3];
  spacer = height / displayResolution;
  strokeWeight(32);
  
  println("Temperature: " + temperature);
  println("Colors: " + targetRed + " " + targetGreen + " " + targetBlue);
  
  /* Iterate through each subpixel (e.g. red, green, blue) */
  for (int i = 0; i <  display.length; i++) {
    for (int j = 0; j <  display[0].length; j++) {
      for (int k = 0; k < 3; k++) {
        /* Apply color biasing */
        if (k == 0) {
          display[i][j][k] = targetRed + (int)(Math.random() * 18 - 9);
        } else if (k == 1) {
          display[i][j][k] = targetGreen + (int)(Math.random() * 18 - 9);
        } else if (k == 2) {
          display[i][j][k] = targetBlue + (int)(Math.random() * 18 - 9);;
        }
        
        /* Make sure value is within [0, 255] */
        if (display[i][j][k] < 0) {
          display[i][j][k] = 0;
        } else if (display[i][j][k] > 255) {
          display[i][j][k] = 255;
        }
      }
    }
  }
}

void draw() {
  background(0);  // Render a black background
  
  /*
    Stochastic Pixel Drift Code
    - Generate three random pixels between (0, 8]
    - If any pixel's index is equal, change that pixel by another color's random value;
    - This processing is done in real time during display to optimize rendering times
  */
  int randRed = (int)(Math.random() * displayResolution);
  int randGreen = (int)(Math.random() * displayResolution);
  int randBlue = (int)(Math.random() * displayResolution);
  
  //println("RGB:" + (round((randRed * 4.5/8.0)) - 2) + " " + (int)(randGreen * (9.0 / 8.0) - 4) + " " + (int)(randBlue * (9.0 / 8.0) - 4));


  /* For loop iterates through all 64 spaces on the display */
  for (int y = 0; y < height; y += spacer) {
    for (int x = 0; x < width; x += spacer) {
      
      /* Translate display coordinates to indexes in display[][][] */
      int i = y / spacer;
      int j = x / spacer;
      
      /* Now we execute the Stochastic Pixel Drift Code */
      if (i == randRed || j == randRed) {
        display[i][j][0] += (round((randGreen * 4.5/8.0)) - 2);
        
        /* Make sure value is within [0, 255] */
        if (display[i][j][0] < 0) {
          display[i][j][0] = 0;
        } else if (display[i][j][0] > 255) {
          display[i][j][0] = 255;
        }
      }
      
      /* Now we execute the Stochastic Pixel Drift Code */
      if (i == randGreen || j == randGreen) {
        display[i][j][1] += (round((randBlue * 4.5/8.0)) - 2);
        
        /* Make sure value is within [0, 255] */
        if (display[i][j][1] < 0) {
          display[i][j][1] = 0;
        } else if (display[i][j][1] > 255) {
          display[i][j][1] = 255;
        }
      }
      
      /* Now we execute the Stochastic Pixel Drift Code */
      if (i == randBlue || j == randBlue) {
        display[i][j][2] += (round((randRed * 4.5/8.0)) - 2);
        
        /* Make sure value is within [0, 255] */
        if (display[i][j][2] < 0) {
          display[i][j][2] = 0;
        } else if (display[i][j][2] > 255) {
          display[i][j][2] = 255;
        }
      }
            
      /* Set the correct coordinate */
      point(x + spacer/2, y + spacer/2);
      
      /* Render a dot to the screen in RGB order, retrieved from display[][][] */
      stroke(display[i][j][0], display[i][j][1], display[i][j][2]);
    }
  }
  
  /* Debugging tool to determine if the algorithm is sufficiently efficient */
  if (frameCount % 60 == 0) {
    println(frameRate);
  }
}