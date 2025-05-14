#include <FlexCAN_T4.h>
/* load the libaries needed to use 2 CAN channels on the Teensy 4*/
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can2;

/* Setup the pin numbers that corresond to the different LEDs*/
#define GREEN_LED 21
#define RED_LED 3
#define YELLOW_LED 20
#define BLUE_LED 2

/* Define a timeout in milliseconds to turn off the LEDs if the have been turned on*/
#define LED_TIMEOUT 200

/* Declare the state of the LEDs*/
boolean GREEN_LED_state;
boolean RED_LED_state;
boolean YELLOW_LED_state;
boolean BLUE_LED_state;

/* Setup the timers for tracking how long the LEDs are on. This is a utility funtion 
supplied with the Teensyduino Addon to Arduino*/
elapsedMillis green_toggle_timer;
elapsedMillis red_toggle_timer;
elapsedMillis yellow_toggle_timer;
elapsedMillis blue_toggle_timer;

elapsedMillis light_send;

#define TRIGGER_PIN 10
bool trigger_state;

void send_light_command();

void setup(void) {
  // set mode for trigger pin
  pinMode(TRIGGER_PIN,INPUT);


  //Keep the Builtin LED (pin 13) on the whole time to show it's plugged in
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  /*Start the CAN channels. Adjust the bit rate as needed */
  Can1.begin();
  Can1.setBaudRate(250000);
  Can1.setMaxMB(16);
  Can1.enableFIFO();
  Can1.enableFIFOInterrupt();
  Can1.onReceive(can1Sniff);
  Can1.mailboxStatus();

  Can2.begin();
  Can2.setBaudRate(250000);
  Can2.setMaxMB(16);
  Can2.enableFIFO();
  Can2.enableFIFOInterrupt();
  Can2.onReceive(can2Sniff);
  Can2.mailboxStatus();

  /* Startup the LEDs*/
  pinMode(GREEN_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(YELLOW_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
  GREEN_LED_state = HIGH;
  YELLOW_LED_state = HIGH;
  RED_LED_state = HIGH;
  BLUE_LED_state = HIGH;
  
  check_led_timers();
}

/*
Show the CAN messages as they come in over Serial. This function "
is not necessary and is supplied for debugging.
*/
void print_CAN(const CAN_message_t &msg){

 // Serial.print("MB "); Serial.print(msg.mb);
 // Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
 // Serial.print("  LEN: "); Serial.print(msg.len);
 // Serial.print(" EXT: "); Serial.print(msg.flags.extended);
 // Serial.print(" TS: "); Serial.print(msg.timestamp);
 // Serial.print(" ID: "); 
  Serial.print(msg.id, HEX);
  Serial.print(" ");
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.printf("%02X ",msg.buf[i]);
  } Serial.println();
}

void can1Sniff(const CAN_message_t &msg) {
  YELLOW_LED_state = !YELLOW_LED_state;
  yellow_toggle_timer = 0;
  print_CAN(msg); 

  //Make a new message based on the old one.
  CAN_message_t new_msg = msg;
  
  // Determine the J1939 Parameter Group Number
  // only handle PDU 2 formatted messages now
  unsigned long pgn = (msg.id & 0x00FFFF00) >> 8;
  
  // Change the message values for each byte as you wish
  //0CEFC180#5A64FF00FFFFFFFF
  // if (pgn == 0xEFC1){ //0xFEF1
  //   new_msg.buf[0]=byte(.2*msg.buf[0]);
  //   // new_msg.buf[1]=0x11;
  //   // new_msg.buf[2]=0x22;
  //   // new_msg.buf[3]=0x33;
  //   // new_msg.buf[4]=0x44;
  //   // new_msg.buf[5]=0x55;
  //   // new_msg.buf[6]=0x66;
  //   // new_msg.buf[7]=0x77;
  //   new_msg.id=0x0CEFC780;
  // }
  // else if (pgn == 0xEFC7){ // Look for another PGN
  //   new_msg.id=0x0CEFC180;
  // }
  // else {
  //   //Do nothing. the new message is the same as the old one.
  // }
  
  // Write the new message on the other channel.
  Can2.write(new_msg);
  GREEN_LED_state = !GREEN_LED_state;
  green_toggle_timer = 0;
}

/*
This routine is sends messages the other direction.
*/
void can2Sniff(const CAN_message_t &msg) {
  BLUE_LED_state = !BLUE_LED_state;
  blue_toggle_timer = 0;
  //print_CAN(msg);

  CAN_message_t new_msg = msg;
  //Add code to look for Ids and manipulate them here.
  Can1.write(new_msg);
  RED_LED_state = !RED_LED_state;
  red_toggle_timer = 0;
}

void check_led_timers(){
  if (red_toggle_timer > LED_TIMEOUT){RED_LED_state = LOW;}
  if (blue_toggle_timer > LED_TIMEOUT){BLUE_LED_state = LOW;}
  if (green_toggle_timer > LED_TIMEOUT){GREEN_LED_state = LOW;}
  if (yellow_toggle_timer > LED_TIMEOUT){YELLOW_LED_state = LOW;}
  digitalWrite(GREEN_LED,GREEN_LED_state);
  digitalWrite(RED_LED,RED_LED_state);
  digitalWrite(YELLOW_LED,YELLOW_LED_state);
  digitalWrite(BLUE_LED,BLUE_LED_state);
}

void loop() {
  Can1.events(); // These calls write events to the network
  Can2.events();
  check_led_timers();

}
