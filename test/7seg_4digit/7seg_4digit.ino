#include "SPI.h"
 
const int cathode_pins[] = {2, 3, 4, 5};  // カソードに接続するArduinoのピン
const int number_of_cathode_pins = sizeof(cathode_pins) / sizeof(cathode_pins[0]);
int numbers_to_display = 0; // LEDに表示する数字を保持する変数
 
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
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setDataMode(SPI_MODE0);
   
  for (int i = 0; i < number_of_cathode_pins; i++) {
    pinMode(cathode_pins[i], OUTPUT);  // cathode_pinを出力モードに設定する
    digitalWrite(cathode_pins[i], LOW);
  }
 
  // f = クロック周波数 / ( 2 * 分周比　*　( 1 + 比較レジスタの値))
  // 分周比=32, 比較レジスタの1値=255 -> f = 16000000 / (2 * 32 * 256) = 976 Hz
  OCR2A = 255; // 255クロックごとに割り込みをかける
  TCCR2B = 0b100; // 分周比を32に設定する
  bitWrite(TIMSK2, OCIE2A, 1); // TIMER2を
}
 
void loop () {
  for (int i = 0; i < 10000; i++) {
    set_numbers(i);
    delay(100);
  }
//    set_numbers(1111);
    display_numbers();
}
 
ISR(TIMER2_COMPA_vect)
{
  display_numbers();
}
