#include <FastLED.h>

// Define the LED pin and number of LEDs
#define LED_PIN     48
#define NUM_LEDS    1

// Define the LED brightness and color fade speed
CRGB leds[NUM_LEDS];
int ledBrightness = 255;
int colorFadeSpeed = 20;

// Define the colors to cycle through
CRGB colors[] = {
  CRGB(255, 0, 0),    // Red
  CRGB(0, 255, 0),    // Green
  CRGB(0, 0, 255),    // Blue
  CRGB(255, 255, 0),  // Yellow
  CRGB(255, 0, 255),  // Magenta
  CRGB(0, 255, 255)   // Cyan
};
int numColors = sizeof(colors) / sizeof(colors[0]);
int currentColor = 0;

// Define the button pin and state
int buttonPin = 0;
int buttonState = 0;

void setup() {
  // Set up the FastLED library
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(ledBrightness);

  // Set up the button pin
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Read the button state
  buttonState = digitalRead(buttonPin);

  // Switch to the next color on button press
  if (buttonState == LOW) {
    currentColor++;
    if (currentColor >= numColors) {
      currentColor = 0;
    }
    setColor(colors[currentColor]);
  }
}

// Function to set the LED to a specific color
void setColor(CRGB color) {
  // Fade the LED to the new color
  fadeToColor(leds[0], color);
}

// Function to fade the LED from one color to another
void fadeToColor(CRGB startColor, CRGB endColor) {
  // Calculate the difference between the start and end colors
  int diffR = endColor.r - startColor.r;
  int diffG = endColor.g - startColor.g;
  int diffB = endColor.b - startColor.b;

  // Fade the LED through the color transition
  for (int i = 0; i < 256; i++) {
    int r = startColor.r + (i * diffR / 255);
    int g = startColor.g + (i * diffG / 255);
    int b = startColor.b + (i * diffB / 255);

    leds[0] = CRGB(r, g, b);
    FastLED.show();
    delay(colorFadeSpeed);
  }
}
