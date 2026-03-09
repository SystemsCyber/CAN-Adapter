/////////////////////////////
// Tests LEDs on CANTool  //
///////////////////////////
#include "unity.h"
#include <Arduino.h>

#define GREEN_LED 21
#define RED_LED 3
#define YELLOW_LED 20
#define BLUE_LED 2

boolean GREEN_LED_state = LOW;
boolean RED_LED_state = LOW;
boolean YELLOW_LED_state = LOW;
boolean BLUE_LED_state = LOW;
boolean LED_BUILTIN_state = LOW;

boolean test_GreenLED_passed = false;
boolean test_YellowLED_passed = false;
boolean test_REDLED_passed = false;
boolean test_BLUELED_passed = false;
boolean test_LED_BUILTIN_passed = false;

// Function prototypes
void toggle_GreenLED(void);
void toggle_REDLED(void);
void toggle_YELLOWLED(void);
void toggle_BLUELED(void);
void toggle_LED_BUILTIN(void);

void GreenLEDTest(void);
void YellowLEDTest(void);
void REDLEDTest(void);
void BLUELEDTest(void);
void LED_BUILTIN_Test(void);

void setUp(void) {
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    GREEN_LED_state = LOW;
    RED_LED_state = LOW;
    YELLOW_LED_state = LOW;
    BLUE_LED_state = LOW;
    LED_BUILTIN_state = LOW;

    digitalWrite(GREEN_LED, GREEN_LED_state);
    digitalWrite(RED_LED, RED_LED_state);
    digitalWrite(YELLOW_LED, YELLOW_LED_state);
    digitalWrite(BLUE_LED, BLUE_LED_state);
    digitalWrite(LED_BUILTIN, LED_BUILTIN_state);
}

void tearDown(void) {
    GREEN_LED_state = LOW;
    RED_LED_state = LOW;
    YELLOW_LED_state = LOW;
    BLUE_LED_state = LOW;
    LED_BUILTIN_state = LOW;

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(LED_BUILTIN, LOW);
}

/////////////// Helper Functions /////////////////////

void GreenLEDTest(void) {
    toggle_GreenLED();
    Serial.println("Did Green LED turn on? (Y/N)");

    String LEDGQuestion = Serial.readStringUntil('\n');
    LEDGQuestion.trim();

    if (LEDGQuestion == "N" || LEDGQuestion == "n") {
        test_GreenLED_passed = false;
        toggle_GreenLED();
    }
    else if (LEDGQuestion == "Y" || LEDGQuestion == "y") {
        test_GreenLED_passed = true;
        toggle_GreenLED();
    }
    else {
        Serial.println("Please enter a valid input (Y or N)");
        toggle_GreenLED();
        GreenLEDTest();
    }
}

void YellowLEDTest(void) {
    toggle_YELLOWLED();
    Serial.println("Did Yellow LED turn on? (Y/N)");

    String LEDYQuestion = Serial.readStringUntil('\n');
    LEDYQuestion.trim();

    if (LEDYQuestion == "N" || LEDYQuestion == "n") {
        test_YellowLED_passed = false;
        toggle_YELLOWLED();
    }
    else if (LEDYQuestion == "Y" || LEDYQuestion == "y") {
        test_YellowLED_passed = true;
        toggle_YELLOWLED();
    }
    else {
        Serial.println("Please enter a valid input (Y or N)");
        toggle_YELLOWLED();
        YellowLEDTest();
    }
}

void REDLEDTest(void) {
    toggle_REDLED();
    Serial.println("Did Red LED turn on? (Y/N)");

    String LEDRQuestion = Serial.readStringUntil('\n');
    LEDRQuestion.trim();

    if (LEDRQuestion == "N" || LEDRQuestion == "n") {
        test_REDLED_passed = false;
        toggle_REDLED();
    }
    else if (LEDRQuestion == "Y" || LEDRQuestion == "y") {
        test_REDLED_passed = true;
        toggle_REDLED();
    }
    else {
        Serial.println("Please enter a valid input (Y or N)");
        toggle_REDLED();
        REDLEDTest();
    }
}

void BLUELEDTest(void) {
    toggle_BLUELED();
    Serial.println("Did Blue LED turn on? (Y/N)");

    String LEDBQuestion = Serial.readStringUntil('\n');
    LEDBQuestion.trim();

    if (LEDBQuestion == "N" || LEDBQuestion == "n") {
        test_BLUELED_passed = false;
        toggle_BLUELED();
    }
    else if (LEDBQuestion == "Y" || LEDBQuestion == "y") {
        test_BLUELED_passed = true;
        toggle_BLUELED();
    }
    else {
        Serial.println("Please enter a valid input (Y or N)");
        toggle_BLUELED();
        BLUELEDTest();
    }
}

void LED_BUILTIN_Test(void) {
    toggle_LED_BUILTIN();
    Serial.println("Did LED_BUILTIN turn on? (Y/N)");

    String LED_BUILTINQuestion = Serial.readStringUntil('\n');
    LED_BUILTINQuestion.trim();

    if (LED_BUILTINQuestion == "N" || LED_BUILTINQuestion == "n") {
        test_LED_BUILTIN_passed = false;
        toggle_LED_BUILTIN();
    }
    else if (LED_BUILTINQuestion == "Y" || LED_BUILTINQuestion == "y") {
        test_LED_BUILTIN_passed = true;
        toggle_LED_BUILTIN();
    }
    else {
        Serial.println("Please enter a valid input (Y or N)");
        toggle_LED_BUILTIN();
        LED_BUILTIN_Test();
    }   
}

// Toggle LED states and write to hardware
void toggle_GreenLED(void) {
    GREEN_LED_state = !GREEN_LED_state;
    digitalWrite(GREEN_LED, GREEN_LED_state);
}

void toggle_REDLED(void) {
    RED_LED_state = !RED_LED_state;
    digitalWrite(RED_LED, RED_LED_state);
}

void toggle_YELLOWLED(void) {
    YELLOW_LED_state = !YELLOW_LED_state;
    digitalWrite(YELLOW_LED, YELLOW_LED_state);
}

void toggle_BLUELED(void) {
    BLUE_LED_state = !BLUE_LED_state;
    digitalWrite(BLUE_LED, BLUE_LED_state);
}

void toggle_LED_BUILTIN(void) {
    LED_BUILTIN_state = !LED_BUILTIN_state;
    digitalWrite(LED_BUILTIN, LED_BUILTIN_state);
}

// Unity test
void test_LED_ROUTINE(void) {
    GreenLEDTest();
    YellowLEDTest();
    REDLEDTest();
    BLUELEDTest();
    LED_BUILTIN_Test();

    TEST_ASSERT_TRUE(test_GreenLED_passed);
    TEST_ASSERT_TRUE(test_YellowLED_passed);
    TEST_ASSERT_TRUE(test_REDLED_passed);
    TEST_ASSERT_TRUE(test_BLUELED_passed);
    TEST_ASSERT_TRUE(test_LED_BUILTIN_passed);
}

void setup() {
    delay(2000);
    Serial.begin(115200);
    while (!Serial && millis() < 5000) { }
    UNITY_BEGIN();
    RUN_TEST(test_LED_ROUTINE);
    UNITY_END();
}

void loop() {}