#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(5, 6);

void setup() {
  Serial.begin(9600);
  Serial.write("start server");
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

void loop() {
  // put your main code here, to run repeatedly:
  char c[] = "    ";

  //Serial.println("start receive");
  if ( radio.available() ) {
    Serial.print("received char = ");
    bool done = false;
    radio.read(&c, sizeof(c) );
    Serial.println(c);
    


    //    radio.stopListening();
    //
    //    radio.write(&c, sizeof(char) );
    //
    //    radio.startListening();
  } else {
    //radio.write('a', sizeof(char) );
  }
delay(10);

}
