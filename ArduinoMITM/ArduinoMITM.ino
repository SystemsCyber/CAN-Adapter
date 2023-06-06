#include <FlexCAN_T4.h>
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can2;

#define GREEN_LED 21
#define RED_LED 3
#define YELLOW_LED 20
#define BLUE_LED 2

#define LED_TIMEOUT 200

boolean GREEN_LED_state;
boolean RED_LED_state;
boolean YELLOW_LED_state;
boolean BLUE_LED_state;

elapsedMillis green_toggle_timer;
elapsedMillis red_toggle_timer;
elapsedMillis yellow_toggle_timer;
elapsedMillis blue_toggle_timer;

void setup(void) {
  //LED Setup
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

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

void print_CAN(const CAN_message_t &msg){
  Serial.print("MB "); Serial.print(msg.mb);
  Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
  Serial.print("  LEN: "); Serial.print(msg.len);
  Serial.print(" EXT: "); Serial.print(msg.flags.extended);
  Serial.print(" TS: "); Serial.print(msg.timestamp);
  Serial.print(" ID: "); Serial.print(msg.id, HEX);
  Serial.print(" Buffer: ");
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.print(msg.buf[i], HEX); Serial.print(" ");
  } Serial.println();
}

void can1Sniff(const CAN_message_t &msg) {
  YELLOW_LED_state = !YELLOW_LED_state;
  yellow_toggle_timer = 0;
  //print_can(msg); 

  CAN_message_t new_msg = msg;
  
  unsigned long pgn = (msg.id & 0x00FFFF00) >> 8;
  
  if (pgn == 65248){
    Serial.println(msg.id,HEX);  
    new_msg.buf[0]=0x00;
    new_msg.buf[1]=0x11;
    new_msg.buf[2]=0x22;
    new_msg.buf[3]=0x33;
    new_msg.buf[4]=0x44;
    new_msg.buf[5]=0x55;
    new_msg.buf[6]=0x66;
    new_msg.buf[7]=0x77;
  }
  if (pgn == 65248){
    
    new_msg.buf[0]=0x00;
    new_msg.buf[3]=0x33;
  }
 
  Can2.write(new_msg);
  GREEN_LED_state = !GREEN_LED_state;
  green_toggle_timer = 0;
}


void can2Sniff(const CAN_message_t &msg) {
  BLUE_LED_state = !BLUE_LED_state;
  blue_toggle_timer = 0;
  
  CAN_message_t new_msg = msg;
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
  Can1.events();
  Can2.events();

  check_led_timers();
}
