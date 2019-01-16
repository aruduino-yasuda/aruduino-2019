#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define STX A1
#define STY A0

RF24 radio(5, 6);

char prev_message = 'x';

void setup() {
  Serial.begin(9600);
  Serial.write("start client");

  pinMode(STX, INPUT);
  pinMode(STY, INPUT);

  // 通信開始
  radio.begin();

  // 書き込み用のパイプを開く
  const byte address_w[6] = "00001";

  radio.openWritingPipe(address_w);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}

void loop() {

  char message =  get_control_message();
  if (prev_message != message && message == "0") {
    prev_message = 'x';
  } else if (prev_message != message) {
    Serial.print(message);
    Serial.println();
    bool ok;
    ok = radio.write( &message, sizeof(message));

//    if(ok == false) {
//      Serial.println("send error");
//    }
    prev_message = message;
  }

  delay(200);

}
char get_control_message() {

  int x_status = get_position(analogRead(STX));
  int y_status = get_position(analogRead(STY));
  if (x_status == 0 && y_status == 0) {


  } else if (x_status == 0 && y_status == 0) {
    return '0';
  } else if (x_status == 0 && y_status == 1) {
    return '1';
  } else if (x_status == 0 && y_status == -1) {
    return '2';
  } else if (x_status == 1 && y_status == 0) {
    return '3';
  } else if (x_status == -1 && y_status == 0) {
    return '4';
  } else if (x_status == 1 && y_status == 1) {
    return '5';
  } else if (x_status == -1 && y_status == 1) {
    return '6';
  } else if (x_status == 1 && y_status == -1) {
    return '7';
  } else if (x_status == -1 && y_status == -1) {
    return '8';
  }
  return '0';
}
int get_position(int point) {

  if (point < 300 ) {
    return -1;
  } else if (point > 700) {
    return 1;
  } else {
    return 0;
  }
}
