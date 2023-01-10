#include "FlexCAN_T4.h"
#include "unity.h"
#include <Arduino.h>
#include <SD.h>

FlexCAN_T4<CAN0, RX_SIZE_256, TX_SIZE_16> Can0;
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can2;

//CAN message set up
static CAN_message_t testMsg;
static uint8_t receivingBus1 = 0;
static uint8_t receivingBus2 = 0;
static uint8_t sendingBus = 0;
static uint16_t receivedCount1 = 0;
static uint16_t receivedCount2 = 0;
static uint16_t messagesToSend = 300000;
static int BAUDRATES[4] = {125000, 250000, 500000, 1000000};
int channel_recieved_2Write;

//SD Card setup
const int chipSelect = BUILTIN_SDCARD;
char* file_Name = "CSU_CAN_Tool_Test_File";
File myFile;


void setUp(void) { 
  SD.begin(chipSelect);         //SD Set up
  Can0.begin();
  Can1.begin();
  Can2.begin();
  receivingBus1 = 0;
  receivingBus2 = 0;
  receivedCount1 = 0; // Zero'ing these out before each test so previous tests don't mess with future tests.
  receivedCount2 = 0;
}

void tearDown(void) { 
    myFile.close(); //closes file if still open
    Can0.reset(); // Closing the can channels so we start with a clean slate (clear any buffers) before each test.
    Can1.reset();
    Can2.reset();
}

void receiveCallback(const CAN_message_t &rxmsg) { 
  if (rxmsg.bus == receivingBus1) { // rxmsg.bus indicates which channel it was received on. 
    receivedCount1++;
    channel_recieved_2Write = 1;
    CANMsg_Recieve_Write_To_File(rxmsg, channel_recieved_2Write);
  }else {
    receivedCount2++;
    channel_recieved_2Write = 2;
    CANMsg_Recieve_Write_To_File(rxmsg, channel_recieved_2Write);
  }
}
void CANMsg_Recieve_Write_To_File(const CAN_message_t &rxmsg, int channel){

    if(channel == 1){
        //Recieved on CAN 1
    }
    else{
        //Recieved on CAN 2
    }
}

//Sets up CAN 1 and 2 to recieve messages from CAN 0
void setupReceivingChannels(int receivingChannel1VAL, int receivingChannel2VAL, int baudrate) { // This is another helper function.
    //sets receiving channel 1
    if(receivingChannel1VAL == 1){
          Can1.setBaudRate(baudrate);
          Can1.setMaxMB(16);
          Can1.enableFIFO(true); // We need to use FIFO otherwise the receivers will drop messages.
          Can1.enableFIFOInterrupt();  // We need to use interrupt driven FIFO otherwise the receivers will drop messages.
          Can1.onReceive(receiveCallback);
    }
    else if(receivingChannel1VAL == 2){
          Can2.setBaudRate(baudrate);
          Can2.setMaxMB(16);
          Can2.enableFIFO(true); // We need to use FIFO otherwise the receivers will drop messages.
          Can2.enableFIFOInterrupt();  // We need to use interrupt driven FIFO otherwise the receivers will drop messages.
          Can2.onReceive(receiveCallback);
    }
    //Sets receiving channel 2
    if(receivingChannel2VAL == 1){
          Can1.setBaudRate(baudrate);
          Can1.setMaxMB(16);
          Can1.enableFIFO(true); // We need to use FIFO otherwise the receivers will drop messages.
          Can1.enableFIFOInterrupt();  // We need to use interrupt driven FIFO otherwise the receivers will drop messages.
          Can1.onReceive(receiveCallback);
    }
    else if(receivingChannel2VAL == 2){
          Can2.setBaudRate(baudrate);
          Can2.setMaxMB(16);
          Can2.enableFIFO(true); // We need to use FIFO otherwise the receivers will drop messages.
          Can2.enableFIFOInterrupt();  // We need to use interrupt driven FIFO otherwise the receivers will drop messages.
          Can2.onReceive(receiveCallback);
    }
}



void CANMsg_SENT_Write_to_File(CAN_message_t testMsg){
    int mb = testMsg.mb;
    int id = testMsg.id;
    boolean ext = testMsg.flags.extended;
    
}

//Sends messages over CAN0, and writes a message to SD and CAN 1 and 2. writes recieved message on can 2 and 3
void Write_floodCanBus(int SendingbusVal, int recievingBus1Val, int recievingBus2Val) {
//iterates through each baudrate
File myFile = SD.open(file_Name, FILE_WRITE);
    if (!myFile) {
            TEST_FAIL_MESSAGE("file failed to create/open");
            return;
        }
    for (int i = 0; i < 4; i++) {
        //if statements find the bus sending and run the flooding of the CANBUS
        if(SendingbusVal == 0){
        Can0.setBaudRate(BAUDRATES[i]);
        setupReceivingChannels(recievingBus1Val, recievingBus2Val, BAUDRATES[i]);
        int sendCount = 0;
        while (sendCount < messagesToSend) {
            if (Can0.getTXQueueCount() == 0) { // Only send the next message once we've finished sending the previous message.
            Can0.write(testMsg); // Before running these bus flooding tests, it would be a good idea to test if each CAN channel can send and receive 1 message so that we don't get errors here.
            CANMsg_SENT_Write_to_File(testMsg);
            sendCount++;
            }
        }
        }
    }
}



//Sends messages over CAN 0
void test_can0_bus_flooding(void) { // This is a test function. The name should begin with "test_" and describe what its testing. It must not return anything and cannot take any arguments.
  receivingBus1 = 1;
  receivingBus2 = 2;
  sendingBus = 0;
  Write_floodCanBus(sendingBus, receivingBus1, receivingBus2);
  uint16_t receivedCounts[2] = {receivedCount1, receivedCount2};
  TEST_ASSERT_EACH_EQUAL_UINT16(messagesToSend * 4, &receivedCounts, 2); // This will check if each element in the array is equal to 3000.
  // TEST_ASSERT_EACH_EQUAL_UINT16(messagesToSend * 4, &receivedCounts, 2, "Some addition info"); // Unity already generates failure messages, but if you need to add additional info on failure here is how.
}





int runUnityTests(void) {
  UNITY_BEGIN();

  return UNITY_END();
}




/**
  * Necessary For Arduino framework
  */
void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  // Put here any setup operations that only need to run once
  testMsg.id = 0x18F004CE;
  testMsg.flags.extended = true;
  testMsg.len = 8;
  testMsg.buf[0] = 0x00;
  testMsg.buf[1] = 0x01;
  testMsg.buf[2] = 0x02;
  testMsg.buf[3] = 0x03;
  testMsg.buf[4] = 0x04;
  testMsg.buf[5] = 0x05;
  testMsg.buf[6] = 0x06;
  testMsg.buf[7] = 0x07;

  runUnityTests();
}
void loop() {}
