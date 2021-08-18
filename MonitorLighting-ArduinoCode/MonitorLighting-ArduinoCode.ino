#include "FastLED.h"

//#define DEBUG //Uncomment to enable debugging

// How many leds are in the strip?
#define NUM_LEDS 120
// Data pin that led data will be written out over
#define DATA_PIN 3

//Analog pins for colours
#define R_POT 3
#define G_POT 4
#define B_POT 5

//Pin to turn on/off strip. Must support external interrupts.
#define ONOFF_BTN 2

//Analog pin definitions
#define POT_VARIANCE 2
#define POT_BRIGHTNESS 1

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

bool ignore_button = true; //prevent button interrupts falsely triggering on startup
void setup() {
#if defined(DEBUG)
  Serial.begin(115200);
  Serial.println("MonitorLighting");
#endif

  pinMode(ONOFF_BTN, INPUT_PULLUP); //configure button as input with internal pullup resistors.
  //External interrupts, ONOFF_BTN is active low. We do this later to prevent false triggers on startup
  //attachInterrupt(digitalPinToInterrupt(ONOFF_BTN), Interrupt_Button, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ONOFF_BTN), Interrupt_Button, FALLING);

  //Setup mode advance timer
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 32767; //Start counting at half the 16 bit limit, for 500ms interrupts
  TCCR1B |= (1 << CS12); //Prescaler 256

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  //startup flash
  leds[NUM_LEDS - 21].r = 255;
  leds[NUM_LEDS - 21].g = 0;
  leds[NUM_LEDS - 21].b = 0;
  FastLED.show();
  delay(200);
  leds[NUM_LEDS - 11].r = 0;
  leds[NUM_LEDS - 11].g = 255;
  leds[NUM_LEDS - 11].b = 0;
  FastLED.show();
  delay(200);
  leds[NUM_LEDS - 1].r = 0;
  leds[NUM_LEDS - 1].g = 0;
  leds[NUM_LEDS - 1].b = 255;
  FastLED.show();
  delay(700);

  ignore_button = false; //Now the startup animation has finished, start listening to the button presses.
#if defined(DEBUG)
  Serial.println("setup() done");
#endif
}

volatile bool enable = true;
void Interrupt_Button() {
  enable = !enable;
}
/*
  volatile uint8_t mode = 0;
  volatile unsigned long button_start_time = 0;
  void Interrupt_Button() {
  if (ignore_button) return;
  Serial.println(TCNT1);

  TCNT1 = 0; //Reset timer counter to 0

  if (!digitalRead(ONOFF_BTN)) {
    //PRESS
  #if defined(DEBUG)
    Serial.println("!");
  #endif

    button_start_time = millis(); //keep track of when we started
    //start timer, so holding the button cycles modes
    TIMSK1 |= (1 << TOIE1); //Enable timer overflow
  }
  else {
    //DEPRESS
  #if defined(DEBUG)
    Serial.println("~");
  #endif

    TIMSK1 = 0; //Disable timer overflow

    //check if it was a short press. if so, toggle power.
    if (millis() - button_start_time > 500) enable = !enable;
  }
  }
  //Timer interrupts happen once a second to advance modes.
  ISR(TIMER1_OVF_vect) {   //This is the interrupt request
  #if defined(DEBUG)
  Serial.println("INT");
  #endif

  TCNT1 = 0; //Reset timer counter to 0

  //Interrupt has triggered, so it's a long press.
  mode++; //advance mode
  if (mode > 2) mode = 0; //mode overflow

  #if defined(DEBUG)
  Serial.print("mode=");
  Serial.println(mode);
  #endif
  }
*/

int adjustment;
void loop() {
  int global_brightness = map(analogRead(POT_BRIGHTNESS), 0, 1023, 20, 190); //20-190 soft limits for power. due to current limits, above 190 starves the arduino of power.
  FastLED.setBrightness(global_brightness);

  //there is a second adjustment knob with different effects in different modes.
  int adjustment = map(analogRead(POT_VARIANCE), 0, 1023, 0, 255);

  //read rgb slider pots
  int r = map(analogRead(R_POT), 0, 1023, 0, 255);
  int g = map(analogRead(G_POT), 0, 1023, 0, 255);
  int b = map(analogRead(B_POT), 0, 1023, 0, 255);

  if (enable) {
    if (adjustment <= 5)
    {
      //solid colour
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].r = r;
        leds[i].g = g;
        leds[i].b = b;
      }
    }
    else {
      //flickering
      for (int i = 0; i < NUM_LEDS; i++) {
        int brightness = random(5, adjustment); //random brightness value
        //apply that to the selected base colour. Second knob is used to control how much the leds flicker
        leds[i].r = map(brightness, 0, adjustment, 0, r);
        leds[i].g = map(brightness, 0, adjustment, 0, g);
        leds[i].b = map(brightness, 0, adjustment, 0, b);
      }
    }
    /*
          for (int i = 0; i < NUM_LEDS; i++) {
            int brightness = random(5, adjustment); //random brightness value
            //apply that to the selected base colour. Second knob is used to control how much the leds flicker
            leds[i].r = 255;
            leds[i].g = 0;
            leds[i].b = 0;
          }
          break;
        case 1:
          for (int i = 0; i < NUM_LEDS; i++) {
            int brightness = random(5, adjustment); //random brightness value
            //apply that to the selected base colour. Second knob is used to control how much the leds flicker
            leds[i].r = 0;
            leds[i].g = 255;
            leds[i].b = 0;
          }
          break;
        case 2:
          for (int i = 0; i < NUM_LEDS; i++) {
            int brightness = random(5, adjustment); //random brightness value
            //apply that to the selected base colour. Second knob is used to control how much the leds flicker
            leds[i].r = 0;
            leds[i].g = 0;
            leds[i].b = 255;
          }
          break;
        default: break;
      }*/
  }
  else {
    //turn strip off
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].r = 0;
      leds[i].g = 0;
      leds[i].b = 0;
    }
  }
  noInterrupts();
  FastLED.show(); //interrupting this function can crash the board, best leave it alone.
  interrupts();
  delay(100); //delay(map(analogRead(POT_DELAY), 0, 255, 20, 1000));
}
