/* this program is to detect IC2 device connected to Arduino
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"            // DHT11のライブラリを読み込みます。
#define DHTPIN 12           // DHT11のDAT端子との接続をデジタルピン12番に設定します。
#define DHTTYPE DHT11       // 温湿度モジュールの型番を設定します（他にDHT21、DHT22が使用可能）。

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);  // 上記接続ピンとモジュールの型番を登録します。

int temp; // 『temp』という名前の保存場所（メモリ領域）を作ります。
int humi; // 『humi』という名前の保存場所（メモリ領域）を作ります。

void setup()
{
  lcd.init();
  lcd.backlight();
  dht.begin();         // 温湿度モジュールの動作を開始します。


}


void loop()
{
  delay(2000);
  temp = dht.readTemperature(); // 温度の測定結果をモジュールから読み込みます。
  humi = dht.readHumidity();    // 湿度の測定結果をモジュールから読み込みます。

  lcd.clear();
  lcd.print("TEMP: ");  // シリアルモニタ上に"TEMP:"を表示します。
  lcd.print(temp);      // シリアルモニタ上に『temp』の値を表示します。
  lcd.print("C");    // シリアルモニタ上に"C"を表示して改行します。
  lcd.setCursor(0, 1);
  lcd.print("HUMI: ");  // シリアルモニタ上に"HUMI:"を表示します。
  lcd.print(humi);      // シリアルモニタ上に『humi』の値を表示します。
  lcd.print("%");    // シリアルモニタ上に"%"を表示して改行します。


}
