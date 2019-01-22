// DHT11を使用して温湿度を測定するプログラム
// DHT11のDAT端子はデジタルピン12番に接続します。

#include "DHT.h"            // DHT11のライブラリを読み込みます。
#define DHTPIN 12           // DHT11のDAT端子との接続をデジタルピン12番に設定します。
#define DHTTYPE DHT11       // 温湿度モジュールの型番を設定します（他にDHT21、DHT22が使用可能）。
DHT dht(DHTPIN, DHTTYPE);  // 上記接続ピンとモジュールの型番を登録します。

int temp; // 『temp』という名前の保存場所（メモリ領域）を作ります。
int humi; // 『humi』という名前の保存場所（メモリ領域）を作ります。
// "int"では-32768から32767までの整数を保存できます。

void setup() {
  Serial.begin(9600); // Arduino－パソコン間の通信速度を「9600bps」に設定します。
  dht.begin();         // 温湿度モジュールの動作を開始します。
}

void loop() {
  delay(2000);                  // 温湿度測定のために2000ms(2秒)待ちます。
  temp = dht.readTemperature(); // 温度の測定結果をモジュールから読み込みます。
  humi = dht.readHumidity();    // 湿度の測定結果をモジュールから読み込みます。

  Serial.print("TEMP: ");  // シリアルモニタ上に"TEMP:"を表示します。
  Serial.print(temp);      // シリアルモニタ上に『temp』の値を表示します。
  Serial.println(" C");    // シリアルモニタ上に"C"を表示して改行します。
  Serial.print("HUMI: ");  // シリアルモニタ上に"HUMI:"を表示します。
  Serial.print(humi);      // シリアルモニタ上に『humi』の値を表示します。
  Serial.println(" %");    // シリアルモニタ上に"%"を表示して改行します。
}
