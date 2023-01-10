/////////////////////////////
//   CAN Communcation   //
///////////////////////////

#include "FlexCAN_T4.h"
#include "unity.h"
#include <Arduino.h>


// Global or static test variables to be shared across all tests in this file.

FlexCAN_T4<CAN0, RX_SIZE_256, TX_SIZE_16> Can0;
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can2;

static CAN_message_t testMsg;
static uint8_t receivingBus1 = 0;
static uint8_t receivingBus2 = 0;
static uint8_t sendingBus = 0;
static uint16_t receivedCount1 = 0;
static uint16_t receivedCount2 = 0;
static uint16_t messagesToSend = 3000;
static int BAUDRATES[4] = {125000, 250000, 500000, 1000000};

void setUp(void) { // Function name must be setUp(void)
  // This function runs BEFORE EACH test. Put any setup code here that needs to run before each test.
  Can0.begin();
  Can1.begin();
  Can2.begin();
  receivingBus1 = 0;
  receivingBus2 = 0;
  receivedCount1 = 0; // Zero'ing these out before each test so previous tests don't mess with future tests.
  receivedCount2 = 0;
}

void tearDown(void) { // Function name must be tearDown(void)
  // This function runs AFTER EACH test. Put any teardown code here that needs to run after each test.
  Can0.reset(); // Closing the can channels so we start with a clean slate (clear any buffers) before each test.
  Can1.reset();
  Can2.reset();
}

void receiveCallback(const CAN_message_t &rxmsg) { // This is a helper function. There are no abnormal requirements for the function name.
  if (rxmsg.bus == receivingBus1) { // rxmsg.bus indicates which channel it was received on. 
    receivedCount1++;
  }else {
    receivedCount2++;
  }
}

void setupReceivingChannels(int receivingChannel1VAL, int receivingChannel2VAL, int baudrate) { // This is another helper function.
    //sets receiving channel 1
    if(receivingChannel1VAL == 0){
          Can0.setBaudRate(baudrate);
          Can0.setMaxMB(16);
          Can0.enableFIFO(true); // We need to use FIFO otherwise the receivers will drop messages.
          Can0.enableFIFOInterrupt();  // We need to use interrupt driven FIFO otherwise the receivers will drop messages.
          Can0.onReceive(receiveCallback);
    }
    else if(receivingChannel1VAL == 1){
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
    if(receivingChannel2VAL == 0){
          Can0.setBaudRate(baudrate);
          Can0.setMaxMB(16);
          Can0.enableFIFO(true); // We need to use FIFO otherwise the receivers will drop messages.
          Can0.enableFIFOInterrupt();  // We need to use interrupt driven FIFO otherwise the receivers will drop messages.
          Can0.onReceive(receiveCallback);
    }
    else if(receivingChannel2VAL == 1){
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

void floodCanBus(int SendingbusVal, int recievingBus1Val, int recievingBus2Val) {
  //iterates through each baudrate
  for (int i = 0; i < 4; i++) {
    //if statements find the bus sending and run the flooding of the CANBUS
    if(SendingbusVal == 0){
      Can0.setBaudRate(BAUDRATES[i]);
      setupReceivingChannels(recievingBus1Val, recievingBus2Val, BAUDRATES[i]);
      int sendCount = 0;
      while (sendCount < messagesToSend) {
        if (Can0.getTXQueueCount() == 0) { // Only send the next message once we've finished sending the previous message.
          Can0.write(testMsg); // Before running these bus flooding tests, it would be a good idea to test if each CAN channel can send and receive 1 message so that we don't get errors here.
          sendCount++;
        }
      }
    }
    else if(SendingbusVal == 1){
      Can1.setBaudRate(BAUDRATES[i]);
      setupReceivingChannels(recievingBus1Val, recievingBus2Val, BAUDRATES[i]);
      int sendCount = 0;
      while (sendCount < messagesToSend) {
        if (Can1.getTXQueueCount() == 0) { 
          Can1.write(testMsg); 
          sendCount++;
        }
     }
    }
    else if(SendingbusVal == 2){
      Can2.setBaudRate(BAUDRATES[i]);
      setupReceivingChannels(recievingBus1Val, recievingBus2Val, BAUDRATES[i]);
      int sendCount = 0;
      while (sendCount < messagesToSend) {
        if (Can1.getTXQueueCount() == 0) { 
          Can1.write(testMsg); 
          sendCount++;
      }
     }
    }
 }
}

void test_can0_bus_flooding(void) { // This is a test function. The name should begin with "test_" and describe what its testing. It must not return anything and cannot take any arguments.
  receivingBus1 = 1;
  receivingBus2 = 2;
  sendingBus = 0;
  floodCanBus(sendingBus, receivingBus1, receivingBus2);
  uint16_t receivedCounts[2] = {receivedCount1, receivedCount2};
  TEST_ASSERT_EACH_EQUAL_UINT16(messagesToSend * 4, &receivedCounts, 2); // This will check if each element in the array is equal to 3000.
  // TEST_ASSERT_EACH_EQUAL_UINT16(messagesToSend * 4, &receivedCounts, 2, "Some addition info"); // Unity already generates failure messages, but if you need to add additional info on failure here is how.
}

void test_can1_bus_flooding(void) { // This is a test function. The name should begin with "test_" and describe what its testing. It must not return anything and cannot take any arguments.
  receivingBus1 = 0;
  receivingBus2 = 2;
  sendingBus = 1;
  floodCanBus(sendingBus, receivingBus1, receivingBus2);
  uint16_t receivedCounts[2] = {receivedCount1, receivedCount2};
  TEST_ASSERT_EACH_EQUAL_UINT16(messagesToSend * 4, &receivedCounts, 2); // This will check if each element in the array is equal to 3000.
}

void test_can2_bus_flooding(void) { // This is a test function. The name should begin with "test_" and describe what its testing. It must not return anything and cannot take any arguments.
  receivingBus1 = 0;
  receivingBus2 = 1;
  sendingBus = 2;
  floodCanBus(sendingBus, receivingBus1, receivingBus2);
  uint16_t receivedCounts[2] = {receivedCount1, receivedCount2};
  TEST_ASSERT_EACH_EQUAL_UINT16(messagesToSend * 4, &receivedCounts, 2); // This will check if each element in the array is equal to 3000.
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_can0_bus_flooding);
  RUN_TEST(test_can1_bus_flooding);
  RUN_TEST(test_can2_bus_flooding);
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
