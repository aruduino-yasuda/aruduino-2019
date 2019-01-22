#include<Servo.h>
 
Servo servo1; //任意のサーボモータークラスを用意。
 
void setup(void){  
  servo1.attach(4); //デジタル4番ピンをサーボモーターの出力ピンとして設定
}
 
void loop(void){
  //定義したモーターに回転角度となる引数を入れる。
  servo1.write(30);
  delay(500);

   servo1.write(60);
  delay(500);
  
  servo1.write(90);
  delay(500);

  servo1.write(120);
  delay(500);
  
  servo1.write(150);
  delay(500);

  servo1.write(120);
  delay(500);
  
  servo1.write(90);
  delay(500);

    servo1.write(60);
  delay(500);

}
