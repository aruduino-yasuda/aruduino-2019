#define STX A1
#define STY A0

int prev_message;

void setup() {
  // put your setup code here, to run once:
  pinMode(STX, INPUT);
  pinMode(STY, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int message = get_control_message();
  if (prev_message != message && message == 0) {
    prev_message = -1;
  } if (prev_message != message) {
    Serial.print(message);
    Serial.println();
    prev_message = message;
  }

  delay(500);
}

int get_control_message() {

  int x_status = get_position(analogRead(STX));
  int y_status = get_position(analogRead(STY));

  if (x_status == 0 && y_status == 0) {

  } else if (x_status == 0 && y_status == 0) {
    return 0;
  } else if (x_status == 0 && y_status == 1) {
    return 1;
  } else if (x_status == 0 && y_status == -1) {
    return 2;
  } else if (x_status == 1 && y_status == 0) {
    return 3;
  } else if (x_status == -1 && y_status == 0) {
    return 4;
  } else if (x_status == 1 && y_status == 1) {
    return 5;
  } else if (x_status == -1 && y_status == 1) {
    return 6;
  } else if (x_status == 1 && y_status == -1) {
    return 7;
  } else if (x_status == -1 && y_status == -1) {
    return 8;
  }
  return 0;
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
