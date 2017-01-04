# Spectra is an Internet Enabled Smart Display

## Currently, it has four operating modes

### Real Time Climate Display
  - Daytime: Display a matrix with colors and patterns corellating with humidity, temperature and windspeed.
  - Nightime: Display an accurate version of the Moon including the correct phase.

### Interactive Fireplace
  - Displays an approximation of a fireplace
  - Fire intensity can be adjusted through a potentiometer
  
### Music Frequency Visualizer
  - Performs a real-time FFT analysis of a microphone input and outputs respective frequencies to the matrix
  
### UI Gradients Viewer
  - Displays a colorful gradient from a given list from the team behind UI Gradients
  
## Hardware Stack

### ESP8266
  - Evaulates three physical inputs to change the matrix
  - Connects via WiFi, giving Spectra the ability to access API's and be managed via the cloud
  - Drives the matrix via the FastLED Library
  
### WS2812 Matrix
  - Each LED has it's own IC, allowing for it to be accesed via a serial input method
  - Blends three 8-bit RGB Values, enabling a total gamut of over 16,000,000 colors
  
### Custom Designed Control Board
  - Enables rapid construction of each Spectra by minimizing soldering number of components
  - Allows for a professional design easing repairs and improving lifespan
