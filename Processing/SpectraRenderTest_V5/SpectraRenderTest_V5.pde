import java.util.Random;

final int LEDCount = 32;  // Number of LED's per side of the matrix

/*
  3D matrix used to store the pixels displayed to the screen
  Format: {X-Coordinate, Y-Coordinate, RGB Value}
*/
int[][][] display = new int[LEDCount][LEDCount][3];

final float intensity = 255;
final int boundaries = 2;

Random random = new Random();

void setup() {
  
  /* Processing specific code to ensure correct rendering */
  size(1024, 1024);  // Size of display in pixels
  strokeWeight(0);  // Thickness of rendered lines
  background(0);  // Set a black background
  rectMode(CORNER);  // Specify that rectangles are given two opposing corner coordinates
  
  int center = LEDCount / 2;
  
  for (int i = 0; i < LEDCount; i++) {
    for (int j = 0; j < LEDCount; j++) {
      int distance = 8 / (int)Math.round(8 * Math.sqrt(Math.pow(center - i, 2) + Math.pow(center - j, 2)));
      if (distance < center / 2) {
        int rand = random.nextInt(2) + 1;
        display[i][j][0] = 190 + (rand * 10);
        display[i][j][1] = 200 + (rand * 15);
        display[i][j][2] = 210 + (rand * 20);
      } else {
        int rand = random.nextInt(1) + 1;
        display[i][j][0] = 10 * rand;
        display[i][j][1] = 25 * rand;
        display[i][j][2] = 30 * rand;
      }
    }
  }
  
  noLoop();  // Only render once
}

void draw() {
  /* Iterate through each pixel and render it to screen */
  for (int i = 0; i < LEDCount; i++) {
    for (int j = 0; j < LEDCount; j++) {
      /*
        Code to render a rectangle
        Corner 1: HEIGHT * (i / LEDCount), WIDTH * (j / LEDCount)
        Corner 2: HEIGHT * ((i + 1) / LEDCount), WIDTH * ((j + 1) / LEDCount)
      */
      int x1 = (int)(height * i * (1.0 / LEDCount));
      int y1 = (int)(width * j * (1.0 / LEDCount));
      int x2 = (int)(height * (i + 1) * (1.0 / LEDCount));
      int y2 = (int)(width * (j + 1) * (1.0 / LEDCount));      
      /* Set fill to color at pixel located at (i, j) */
      fill(display[i][j][0], display[i][j][1], display[i][j][2]);
      stroke(display[i][j][0], display[i][j][1], display[i][j][2]);
      rect(x1 , y1, x2, y2);  // Draw the rectangle
    }
  }
  //save("Moon2.png");
}