/* Test script for makers unified controller. 
    Author: Matthew Bellafaire
    Date: December 17th, 2021

    This script is designed to test that a controller is properly assembled and show that all buttons
    and joysticks are read properly. The buttons and joystick values are displayed on the SSD1306 display. 
    This script requires the SSD1306 Adafruit library along with the Adafruit GFX library, both of which
    can be installed through the library manager by navigating to tools > manage libraries. 
*/

#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>

//function signitures
void initIO();
void drawTestData();

//screen size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//button defines (probably going to want to copy these to any other script for the controller)
#define LEFT_JOY_Y 13
#define LEFT_JOY_X 14
#define LEFT_JOY_SW 4

#define RIGHT_JOY_X 32
#define RIGHT_JOY_Y 33
#define RIGHT_JOY_SW 35

#define SW1 17
#define SW2 16
#define SW3 19
#define SW4 18
#define SW5 25
#define SW6 34
#define SW7 36
#define SW8 26

#define LEFT_TRIG 23
#define RIGHT_TRIG 27

//array for simplification of button reading code. 
int buttons[] = {
  SW1,
  SW2,
  SW3,
  SW4,
  SW5,
  SW6,
  SW7,
  SW8,
  LEFT_TRIG,
  RIGHT_TRIG,
  LEFT_JOY_SW,
  RIGHT_JOY_SW
};

//init display.
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, & Wire, -1);

void setup() {
  Serial.begin(115200);

  //wait for display.
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  //initialize IO
  initIO();

  delay(500);
  display.clearDisplay();
}

void loop() {
  //read read every button and joystick then draw the results to the screen.
  drawTestData();
}

void initIO() {
  pinMode(LEFT_JOY_Y, INPUT);
  pinMode(LEFT_JOY_X, INPUT);
  pinMode(LEFT_JOY_SW, INPUT);

  pinMode(RIGHT_JOY_Y, INPUT);
  pinMode(RIGHT_JOY_X, INPUT);
  pinMode(RIGHT_JOY_SW, INPUT);

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);
  pinMode(SW5, INPUT);
  pinMode(SW6, INPUT);
  pinMode(SW7, INPUT);
  pinMode(SW8, INPUT);

  pinMode(LEFT_TRIG, INPUT);
  pinMode(RIGHT_TRIG, INPUT);
}

#define BUTTON_DISPLAY_GRID_SIZE SCREEN_WIDTH / 6

//reads each button and joystick and displays the value on the display. 
//buttons that are pressed will show a label on the screen, whereas buttons that are not
//will show nothing. 
void drawTestData() {

  //clear display
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  //makers :)
  display.println("Makers @ OU");

  //loop through each button in the array, arrange them onto a 6x2 grid
  for (int a = 0; a < 12; a++) {

    //move to grid position
    display.setCursor((a % 6) * BUTTON_DISPLAY_GRID_SIZE, 10 + (10 * (a / 6)));

    //if button is pressed display white, otherwise display black.
    if (digitalRead(buttons[a])) {
      display.setTextColor(WHITE);
    } else {
      display.setTextColor(BLACK);
    }

    //print button with above formatting and location.
    display.print("S" + String(a + 1));

  }

  //read joysticks. 
  display.setTextColor(WHITE);

  //left joystick
  display.setCursor(0, 30);
  display.print("Left x:" + String(analogRead(LEFT_JOY_X)) + " y:" + String(analogRead(LEFT_JOY_Y)));

  //right joystick
  display.setCursor(0, 40);
  display.print("Right x:" + String(analogRead(RIGHT_JOY_X)) + " y:" + String(analogRead(RIGHT_JOY_Y)));

  //push to display.
  display.display();

}