#include "SPI.h"
#include "DHT.h"            // DHT11のライブラリを読み込みます。
#define DHTPIN 6           // DHT11のDAT端子との接続をデジタルピン12番に設定します。
#define DHTTYPE DHT11       // 温湿度モジュールの型番を設定します（他にDHT21、DHT22が使用可能）。
DHT dht(DHTPIN, DHTTYPE);  // 上記接続ピンとモジュールの型番を登録します。

int temp; // 『temp』という名前の保存場所（メモリ領域）を作ります。
int humi; // 『humi』という名前の保存場所（メモリ領域）を作ります。
// "int"では-32768から32767までの整数を保存できます。
const int cathode_pins[] = {2, 3, 4, 5};  // カソードに接続するArduinoのピン
const int number_of_cathode_pins = sizeof(cathode_pins) / sizeof(cathode_pins[0]);
int numbers_to_display = 0; // LEDに表示する数字を保持する変数

int buttomInput = 0;
int dispNum = 0;
 
const byte digits[] = {
  0b00010100, // 0
  0b11010111, // 1
  0b01001100, // 2
  0b01000101, // 0
  0b10000111, // 4
  0b00100101, // 5
  0b00100100, // 6
  0b00010111, // 7
  0b00000100, // 8
  0b00000101, // 9
};
 
// 1桁の数字(n)を表示する
void display_number (int n) {
  digitalWrite(SS, LOW);
  SPI.transfer(digits[n]);
  digitalWrite(SS, HIGH);
}
 
// アノードをすべてLOWにする
void clear_segments() {
  digitalWrite(SS, LOW);
  SPI.transfer(1);
  digitalWrite(SS, HIGH);
}
 
void display_numbers () {
  int n = numbers_to_display;  // number_to_displayの値を書き換えないために変数にコピー
  for (int i = 0; i < number_of_cathode_pins; i++) {
    digitalWrite(cathode_pins[i], HIGH);
    display_number(n % 10); // 最後の一桁を表示する
    delayMicroseconds(100);
    clear_segments();
    digitalWrite(cathode_pins[i], LOW);
    n = n / 10; // 10で割る
  }
}
 
void set_numbers(int n) {
  noInterrupts();
  numbers_to_display = n;
  interrupts();
}
 
void setup() {
  Serial.begin(9600); // Arduino－パソコン間の通信速度を「9600bps」に設定します。
  dht.begin();         // 温湿度モジュールの動作を開始します。
    SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setDataMode(SPI_MODE0);
   
  for (int i = 0; i < number_of_cathode_pins; i++) {
    pinMode(cathode_pins[i], OUTPUT);  // cathode_pinを出力モードに設定する
    digitalWrite(cathode_pins[i], LOW);
  }
 
//  // f = クロック周波数 / ( 2 * 分周比　*　( 1 + 比較レジスタの値))
//  // 分周比=32, 比較レジスタの1値=255 -> f = 16000000 / (2 * 32 * 256) = 976 Hz
//  OCR2A = 255; // 255クロックごとに割り込みをかける
//  TCCR2B = 0b100; // 分周比を32に設定する
//  bitWrite(TIMSK2, OCIE2A, 1); // TIMER2を
}
 
void loop () {
  display_numbers();
  int tmpVal = digitalRead(9);
  if (buttomInput != tmpVal && HIGH == tmpVal) {

  }
  //delay(2000);                  // 温湿度測定のために2000ms(2秒)待ちます。

  temp = dht.readTemperature(); // 温度の測定結果をモジュールから読み込みます。
  humi = dht.readHumidity();    // 湿度の測定結果をモジュールから読み込みます。
  set_numbers(temp); // 温度の測定結果をモジュールから読み込みます。
  display_numbers();
  
  Serial.print("TEMP: ");  // シリアルモニタ上に"TEMP:"を表示します。
  Serial.print(temp);      // シリアルモニタ上に『temp』の値を表示します。
  Serial.println(" C");    // シリアルモニタ上に"C"を表示して改行します。
  Serial.print("HUMI: ");  // シリアルモニタ上に"HUMI:"を表示します。
  Serial.print(humi);      // シリアルモニタ上に『humi』の値を表示します。
  Serial.println(" %");    // シリアルモニタ上に"%"を表示して改行します。
}
 
