int val = 0;     // 読み取った値を保持する変数
int num = 0;

void setup() {
  // put your setup code here, to run once:

  //1～8番ピン　デジタル出力へセット
  for (int i=1; i<=8; i++){
    pinMode(i,OUTPUT);
  }
  pinMode(9,INPUT);
}

//LEDレイアウトを定義
//0,1,2,3,4,5,6,7,8,9,0,.　の順。
boolean Num_Array[11][8]={
  {1,1,1,0,1,1,1,0},{0,0,1,0,1,0,0,0},{1,1,0,0,1,1,0,1},{0,1,1,0,1,1,0,1},
  {0,0,1,0,1,0,1,1},{0,1,1,0,0,1,1,1},{1,1,1,0,0,1,1,1},{0,0,1,0,1,1,1,0},
  {1,1,1,0,1,1,1,1},{0,1,1,0,1,1,1,1},{0,0,0,1,0,0,0,0}
};
//LED表示関数を定義

void NumPrint(int Number){
  
  for (int w=0; w<=7; w++){
  digitalWrite(w+1,Num_Array[Number][w]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int tmpVal = digitalRead(9);
  if (val != tmpVal && HIGH == tmpVal) {
    ++num;
    if (num > 10) {
      num = 0;
    }
  }
//  if (HIGH == tmpVal) {
//    ++num;
//    if (num > 10) {
//      num = 0;
//    }
//  }

  val = tmpVal;
  NumPrint(num);
  delay(50);
}
