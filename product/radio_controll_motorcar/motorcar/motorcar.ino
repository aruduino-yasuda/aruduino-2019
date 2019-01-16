#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define COMMAND_STOP '0'
#define COMMAND_FOWERD '1'
#define COMMAND_BACK '2'
#define COMMAND_TURN_RIGHT '3'
#define COMMAND_TURN_LEFT '4'

int right_motor_in1 = 8;
int right_motor_in2 = 7;
int right_motor_control = 9;

int left_motor_in1 = 6;
int left_motor_in2 = 5;
int left_motor_control = 4;

int speed_level = 0;

RF24 radio(2, 3);

void setup() {
  Serial.begin(9600);
  Serial.write("start server");


  pinMode(left_motor_in1, OUTPUT);
  pinMode(left_motor_in2, OUTPUT);
  pinMode(left_motor_control, OUTPUT);
  pinMode(right_motor_in1, OUTPUT);
  pinMode(right_motor_in2, OUTPUT);
  pinMode(right_motor_control, OUTPUT);

  // 通信開始
  radio.begin();

  // リトライ回数の設定
  //.setRetries(15, 15);

  // 書き込み用のパイプを開く
  const byte address_w[6] = "00002";
  const byte address_r[6] = "00001";
  //radio.openWritingPipe(0xF0F0F0F0D2LL);
  // 読み込み用のパイプを開く
  radio.openReadingPipe(0, address_r);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

int get_motor_speed() {

  if (speed_level > 8) {
    speed_level = 8;
  } else if (speed_level < 1) {
    speed_level = 0;
  }
  return 15 + (speed_level * 30);
}

void turn_right() {


  digitalWrite(left_motor_in1, LOW);
  digitalWrite(left_motor_in2, LOW);
  digitalWrite(right_motor_in1, LOW);
  digitalWrite(right_motor_in2, HIGH);
  analogWrite(right_motor_control, get_motor_speed());
}

void turn_left() {

  digitalWrite(right_motor_in1, LOW);
  digitalWrite(right_motor_in2, LOW);
  digitalWrite(left_motor_in1, LOW);
  digitalWrite(left_motor_in2, HIGH);
  analogWrite(left_motor_control, get_motor_speed());
}

void fowerd() {

  digitalWrite(right_motor_in1, LOW);
  digitalWrite(right_motor_in2, HIGH);
  analogWrite(right_motor_control, get_motor_speed());
  digitalWrite(left_motor_in1, LOW);
  digitalWrite(left_motor_in2, HIGH);
  analogWrite(left_motor_control, get_motor_speed());
}

void back() {

  digitalWrite(right_motor_in1, HIGH);
  digitalWrite(right_motor_in2, LOW);
  analogWrite(right_motor_control, get_motor_speed());
  digitalWrite(left_motor_in1, HIGH);
  digitalWrite(left_motor_in2, LOW);
  analogWrite(left_motor_control, get_motor_speed());
}

void stop() {

  digitalWrite(right_motor_in1, LOW);
  digitalWrite(right_motor_in2, LOW);
  digitalWrite(left_motor_in1, LOW);
  digitalWrite(left_motor_in2, LOW);
}

void command_input(char command) {

  Serial.println(command);
  if (command == COMMAND_FOWERD) {
    fowerd();
  } else if (command == COMMAND_BACK) {
    back();
  } else if (command == COMMAND_TURN_RIGHT) {
    turn_right();
  } else if (command == COMMAND_TURN_LEFT) {
    turn_left();
  }else {
    stop();
    //back();
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  char c[] = " ";

  //Serial.println("start receive");
  if ( radio.available() ) {
    //Serial.print("received char = ");
    bool done = false;
    radio.read(&c, sizeof(c) );


    speed_level = 8;
    command_input(c[0]);

  } else {
    //radio.write('a', sizeof(char) );
  }
  delay(10);

}
