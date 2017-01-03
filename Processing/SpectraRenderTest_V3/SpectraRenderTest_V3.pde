
final int LEDCount = 128;  // Number of LED's per side of the matrix

/*
  3D matrix used to store the pixels displayed to the screen
  Format: {X-Coordinate, Y-Coordinate, RGB Value}
*/
int[][][] display = new int[LEDCount][LEDCount][3];
int[][][] colorA = new int[LEDCount][LEDCount][3];
int[][][] colorB = new int[LEDCount][LEDCount][3];

final float intensity = 255;

//double redA = Math.random();
//double greenA = Math.random();
//double blueA = Math.random();

//double redB = Math.random();
//double greenB = Math.random();
//double blueB = Math.random();

double redA = 0xFC / 255.0;
double greenA = 0x00 / 255.0;
double blueA = 0xFF / 255.0;

double redB = 0x00 / 255.0;
double greenB = 0xDB / 255.0;
double blueB = 0xDE / 255.0;

void setup() {
  
  /* Processing specific code to ensure correct rendering */
  size(1024, 1024);  // Size of display in pixels
  strokeWeight(0);  // Thickness of rendered lines
  background(0);  // Set a black background
  rectMode(CORNER);  // Specify that rectangles are given two opposing corner coordinates
  
  println("RGB: " + redA + " " + greenA + " " + blueA);
  println("RGB: " + redB + " " + greenB + " " + blueB);

  /* Assign initial values to display by iterating through each subpixel */
  for (int i = 0; i < LEDCount; i++) {
    for (int j = 0; j < LEDCount; j++) {
      colorA[i][j][0] = (int)(redA * (intensity / LEDCount) * (i + j));
      colorA[i][j][1] = (int)(greenA * (intensity / LEDCount) * (i + j));
      colorA[i][j][2] = (int)(blueA * (intensity / LEDCount) * (i + j));
    }
  }
  
  /* Assign initial values to display by iterating through each subpixel */
  for (int i = 0; i < LEDCount; i++) {
    for (int j = 0; j < LEDCount; j++) {
      colorB[i][j][0] = (int)(redB * (intensity / LEDCount) * (i + j));
      colorB[i][j][1] = (int)(greenB * (intensity / LEDCount) * (i + j));
      colorB[i][j][2] = (int)(blueB * (intensity / LEDCount) * (i + j));
    }
  }
  
  /* Crossfade the pixels by averaging them */
  for (int i = 0; i < LEDCount; i++) {
    for (int j = 0; j < LEDCount; j++) {
      display[i][j][0] = (colorA[i][j][0] + colorB[LEDCount - i - 1][LEDCount - j - 1][0]) / 2;
      display[i][j][1] = (colorA[i][j][1] + colorB[LEDCount - i - 1][LEDCount - j - 1][1]) / 2;
      display[i][j][2] = (colorA[i][j][2] + colorB[LEDCount - i - 1][LEDCount - j - 1][2]) / 2;
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
      
      //fill(colorA[i][j][0], colorA[i][j][1], colorA[i][j][2]);
      //stroke(colorA[i][j][0], colorA[i][j][1], colorA[i][j][2]);
      rect(x1 , y1, x2, y2);  // Draw the rectangle
    }
  }
  //save("gradient12.png");
}