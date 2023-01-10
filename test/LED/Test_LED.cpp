/////////////////////////////
// Tests LEDs on CANTool  //
///////////////////////////
#include "unity.h"
#include <Arduino.h>

#define GREEN_LED 21
#define RED_LED 3
#define YELLOW_LED 20
#define BLUE_LED 2

boolean GREEN_LED_state;
boolean RED_LED_state;
boolean YELLOW_LED_state;
boolean BLUE_LED_state;

boolean test_GreenLED_passed;
boolean test_YellowLED_passed;
boolean test_REDLED_passed;
boolean test_BLUELED_passed;

void setUp(void) { // Function name must be setUp(void)
    //LED Setup
    pinMode(GREEN_LED,OUTPUT);
    pinMode(RED_LED,OUTPUT);
    pinMode(YELLOW_LED,OUTPUT);
    pinMode(BLUE_LED,OUTPUT);
}

void tearDown(void) { // Function name must be tearDown(void)
    GREEN_LED_state = LOW;
    YELLOW_LED_state = LOW;
    RED_LED_state = LOW;
    BLUE_LED_state = LOW;
}



///////////////Helper Functions/////////////////////
/////LEDTest run a text script that asks user for visual confirmation that LED is working///
void GreenLEDTest(void){
    toggle_GreenLED();
    Serial.print("Did Green LED turn on?('Y/N')");
    String LEDGQuestion = Serial.readString();
    if(LEDGQuestion == "N" || LEDGQuestion == "n"){
        test_YellowLED_passed = false;
        toggle_GreenLED();
    }
    else if(LEDGQuestion == "Y" || LEDGQuestion == "y"){
        test_YellowLED_passed = true;
        toggle_GreenLED();
    }
    else{
        Serial.print("Please enter a valid input (Y or N)");
        toggle_GreenLED();
        GreenLEDTest();
    }
}

void YellowLEDTest(void){
    toggle_YELLOWLED();
    Serial.print("Did yellow LED turn on?('Y/N')");
    String LEDYQuestion = Serial.readString();
    if(LEDYQuestion == "N" || LEDYQuestion == "n"){
        test_YellowLED_passed = false;
        toggle_YELLOWLED();
    }
    else if(LEDYQuestion == "Y" || LEDYQuestion == "y"){
        test_YellowLED_passed = true;
        toggle_YELLOWLED();
    }
    else{
        Serial.print("Please enter a valid input (Y or N)");
        toggle_YELLOWLED();
        YellowLEDTest();
    }
}

void REDLEDTest(void){
    toggle_REDLED();
    Serial.print("Did Red LED turn on?('Y/N')");
    String LEDRQuestion = Serial.readString();
    if(LEDRQuestion == "N" || LEDRQuestion == "n"){
        test_REDLED_passed = false;
        toggle_REDLED();
    }
    else if(LEDRQuestion == "Y" || LEDRQuestion == "y"){
        test_REDLED_passed = true;
        toggle_REDLED();
    }
    else{
        Serial.print("Please enter a valid input (Y or N)");
        toggle_REDLED();
        REDLEDTest();
    }
}

void BLUELEDTest(void){
    toggle_BLUELED();
    Serial.print("Did Blue LED turn on?('Y/N')");
    String LEDBQuestion = Serial.readString();
    if(LEDBQuestion == "N" || LEDBQuestion == "n"){
        test_BLUELED_passed = false;
        toggle_BLUELED();
    }
    else if(LEDBQuestion == "Y" || LEDBQuestion == "y"){
        test_BLUELED_passed = true;
        toggle_BLUELED();
    }
    else{
        Serial.print("Please enter a valid input (Y or N)");
        toggle_BLUELED();
        BLUELEDTest();
    }
}

//Toggles on off for LEDS
void toggle_GreenLED(void){
    GREEN_LED_state = !GREEN_LED_state;
}
void toggle_REDLED(void){
    RED_LED_state = !RED_LED_state;
}
void toggle_YELLOWLED(void){
    YELLOW_LED_state = !YELLOW_LED_state;
}
void toggle_BLUELED(void){
    BLUE_LED_state = !BLUE_LED_state;
}



//Unity tests
//calls upon helper function
void test_LED_ROUTINE(void) {
    GreenLEDTest();
    YellowLEDTest();
    REDLEDTest();
    BLUELEDTest();
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_LED_ROUTINE);
    TEST_ASSERT(test_GreenLED_passed);
    TEST_ASSERT(test_YellowLED_passed);
    TEST_ASSERT(test_REDLED_passed);
    TEST_ASSERT(test_BLUELED_passed);
    return UNITY_END();
}

int main(void) {
    return runUnityTests();
}

void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}
void loop() {}


