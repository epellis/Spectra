final int LEDCount = 128;  // Number of LED's per side of the matrix

/*
  3D matrix used to store the pixels displayed to the screen
  Format: {X-Coordinate, Y-Coordinate, RGB Value}
*/
int[][][] display = new int[LEDCount][LEDCount][3];

double redMod = Math.random() * 3;
double greenMod = Math.random() * 3;
double blueMod = Math.random() * 3;

void setup() {
  
  /* Processing specific code to ensure correct rendering */
  size(900, 900);  // Size of display in pixels
  strokeWeight(0);  // Thickness of rendered lines
  background(0);  // Set a black background
  rectMode(CORNER);  // Specify that rectangles are given two opposing corner coordinates
  
  println("RGB: " + redMod + " " + greenMod + " " + blueMod);
  
  /* Assign initial values to display by iterating through each subpixel */
  for (int i = 0; i < LEDCount; i++) {
    for (int j = 0; j < LEDCount; j++) {
      display[i][j][0] = (int)(255 * redMod * (1.0 / LEDCount) * (1.0 / LEDCount) * i * j);
      display[i][j][1] = (int)(255 * greenMod * (1.0 / LEDCount) * (1.0 / LEDCount) * i * j);
      display[i][j][2] = (int)(255 * blueMod * (1.0 / LEDCount) * (1.0 / LEDCount) * i * j);
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
      rect(x1 , y1, x2, y2);  // Draw the rectangle
    }
  }
}