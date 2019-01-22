#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(5, 6);

void setup() {
  Serial.begin(9600);
  Serial.write("start client");

  // 通信開始
  radio.begin();

  // リトライ回数の設定
  //radio.setRetries(15, 30);

  // 書き込み用のパイプを開く 
  const byte address_w[6] = "00001";
  const byte address_r[6] = "00002";
  
  radio.openWritingPipe(address_w);
  // 読み込み用のパイプを開く
  //radio.openReadingPipe(1, address_r);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
}

void loop() {
  delay(100);
  char c[] = "test";
  bool ok;
 
  // サーバーに１文字送信する
  //Serial.println(c);
  ok = radio.write( &c, sizeof(c) );
  if (ok) {
    Serial.println(c);
    // サーバーからの返信を待つ

//    radio.startListening();
//    // 200ms待っても返信が無ければタイムアウト
//    unsigned long started_waiting_at = millis();
//    bool timeout = false;
//    while ( ! radio.available() && ! timeout ) {
//      if (millis() - started_waiting_at > 200 ) {
//        timeout = true;
//      }
//    }
//
//    radio.stopListening();
//
//    if ( timeout )  {
//      Serial.write("response timed out");
//    } else {
//      radio.read( &c, sizeof(char) );
//      Serial.write(c);
//    }
  } else {
    Serial.write("Send error");
  }


}
