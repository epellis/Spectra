import java.util.Random;

final int LEDCount = 16;  // Number of LED's per side of the matrix

/*
  3D matrix used to store the pixels displayed to the screen
  Format: {X-Coordinate, Y-Coordinate, RGB Value}
*/
int[][][] display = new int[LEDCount][LEDCount][3];

int lunarPhase = 7;  // Int that describes the phase of the moon, ranges from [0, 32];
final int MAXPHASE = 16;  // Maximum value for the phase

int[] lunarColor = {255, 255, 255};  // RGB value for the moon
int[] shadowColor = {0, 255, 0};  // RGB value for the shadow

Random random = new Random();

void setup() {
  
  /* Processing specific code to ensure correct rendering */
  size(1024, 1024);  // Size of display in pixels
  strokeWeight(0);  // Thickness of rendered lines
  background(0);  // Set a black background
  rectMode(CORNER);  // Specify that rectangles are given two opposing corner coordinates
  
  int radius = LEDCount / 2;
  
  /* Renders a circle to the screen, this is our full moon*/
  for (int i = 0; i < LEDCount; i++) {
    int x = i - radius;
    if (x >= 0) { x += 1; }  // Made so that the matrix would skip over all points including a 0
    for (int j = 0; j < LEDCount; j++) {
      
      /* Transform i and j so that the center of the grid is the center of the matrix */
      int y = j - radius;
      
      if (y >= 0) { y += 1; }  // Made so that the matrix would skip over all points including a 0
        if (x * x + y * y >= radius * radius) {  // Circle Equation, X^2 + Y^2 = Radius^2
        /* Fill with a dark pixel */
        display[i][j][0] = 0;
        display[i][j][1] = 0;
        display[i][j][2] = 0;
    }
    else {
        display[i][j][0] = 255;
        display[i][j][1] = 255;
        display[i][j][2] = 255;
      }
    }
  }
    
  for (int i = 0; i < LEDCount; i++) {
    
    int x = i - radius;
    if (x >= 0) { x += 1; }  // Made so that the matrix would skip over all points including a 0
    for (int j = 0; j < LEDCount; j++) {
      
      int y = i - radius;
      if (y >= 0) { x += 1; }  // Made so that the matrix would skip over all points including a 0
      
      /* To keep the code easy to read, the height and width will be calculated before being inputted into the if statement */
      float shadowHeight = (lunarPhase * radius) / MAXPHASE + x;
      float shadowWidth = (MAXPHASE * y * (1.0/ (radius + lunarPhase)));
      println("Translating: " + i + ", " + j + " to: " + x + ", " + y);
      
      if (shadowHeight * shadowHeight + shadowWidth * shadowWidth <= radius * radius) {
        display[i][j][0] = shadowColor[0];
        display[i][j][1] = shadowColor[1];
        display[i][j][2] = shadowColor[2];
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