/////////////////////////////
//  Serial Commincation   //
///////////////////////////
#include "unity.h"
#include <Arduino.h>

boolean confirmed;

void setUp(void) { // Function name must be setUp(void)
    confirmed = false;
}

void tearDown(void) { // Function name must be tearDown(void)

}

void test_Serial_Port(void) {

    String test = "ColoradoRams";
    Serial.print("ColoradoRams");
    
    String lastMessage = Serial.read();
    if(test == lastMessage){
        confirmed = true;
    }
    else{
        Serial.print("Serial not connected");
    }

    TEST_ASSERT(confirmed);
}




void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_Serial_Port);
    UNITY_END();
}
void loop() {}


