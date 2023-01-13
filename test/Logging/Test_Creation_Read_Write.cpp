/////////////////////////////
//  Logging Capabilities  //
//      SD CARD          //
//////////////////////////
#include "unity.h"
#include <Arduino.h>
#include <SD.h>

// Get a uniqueName for the Logger File
const int chipSelect = BUILTIN_SDCARD;
boolean file_open;             //Boolean to check if file is open or closed
char* file_Name = "CSU_CAN_Tool_Test_File";
File myFile;
File dataFile;

void setUp(void) { 
    SD.begin(chipSelect);
}

void tearDown(void) { 
    myFile.close();
}


//Checks that the device can connect to the SD card, Create a new file, Write to that file, and read that file. 
void test_Create_New_File_Read_Write(void) {
    //Test that we can Write to the file
    File myFile = SD.open(file_Name, FILE_WRITE);
    if (!myFile) {
        TEST_FAIL_MESSAGE("file failed to create/open");
        return;
    }
    else{
        myFile.write("Intialization Test");
        TEST_PASS_MESSAGE("File WRITE Intialization Passed");
    }
    myFile.close();

    //Check that we wrote to card
    File dataFile = SD.open("CSU_CAN_Tool_Test_File.txt");
    if (dataFile) {
        String DataContent = dataFile.read();
        if(DataContent != "-1"){
            TEST_PASS_MESSAGE("File READ Intialization Passed");
            
        }
        else{
            TEST_FAIL_MESSAGE("File Write Intialization failed. Did not read any contents");
        }
    }
    else{
        TEST_FAIL_MESSAGE("file failed to reopen to read intialization Test");
        dataFile.close();
        return;
    }
    dataFile.close();
}



void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_Create_New_File_Read_Write);
    UNITY_END();
}
void loop() {}


