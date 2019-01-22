#define COMMAND_STOP 0
#define COMMAND_FOWERD 1
#define COMMAND_BACK 2
#define COMMAND_TURN_RIGHT 3
#define COMMAND_TURN_LEFT 4

int right_motor_in1 = 9;
int right_motor_in2 = 8;
int right_motor_control = 10;

int left_motor_in1 = 7;
int left_motor_in2 = 6;
int left_motor_control = 5;

int speed_level = 0;
void setup() {

  pinMode(left_motor_in1, OUTPUT);
  pinMode(left_motor_in2, OUTPUT);
  pinMode(left_motor_control, OUTPUT);
  pinMode(right_motor_in1, OUTPUT);
  pinMode(right_motor_in2, OUTPUT);
  pinMode(right_motor_control, OUTPUT);
  Serial.begin(9600);

}

int get_motor_speed() {

  if (speed_level > 8) {
    speed_level = 8;
  } else if (speed_level < 1) {
    speed_level = 0;
  }
  return 15 + (speed_level * 30);
}

void turn_right() {


  digitalWrite(left_motor_in1, LOW);
  digitalWrite(left_motor_in2, LOW);
  digitalWrite(right_motor_in1, LOW);
  digitalWrite(right_motor_in2, HIGH);
  analogWrite(right_motor_control, get_motor_speed());
}

void turn_left() {

  digitalWrite(right_motor_in1, LOW);
  digitalWrite(right_motor_in2, LOW);
  digitalWrite(left_motor_in1, LOW);
  digitalWrite(left_motor_in2, HIGH);
  analogWrite(left_motor_control, get_motor_speed());
}

void fowerd() {

  digitalWrite(right_motor_in1, LOW);
  digitalWrite(right_motor_in2, HIGH);
  analogWrite(right_motor_control, get_motor_speed());
  digitalWrite(left_motor_in1, LOW);
  digitalWrite(left_motor_in2, HIGH);
  analogWrite(left_motor_control, get_motor_speed());
}

void back() {

  digitalWrite(right_motor_in1, HIGH);
  digitalWrite(right_motor_in2, LOW);
  analogWrite(right_motor_control, get_motor_speed());
  digitalWrite(left_motor_in1, HIGH);
  digitalWrite(left_motor_in2, LOW);
  analogWrite(left_motor_control, get_motor_speed());
}

void stop() {

  digitalWrite(right_motor_in1, LOW);
  digitalWrite(right_motor_in2, LOW);
  digitalWrite(left_motor_in1, LOW);
  digitalWrite(left_motor_in2, LOW);
}

void command_input(int command) {
  if (command == COMMAND_FOWERD) {
    fowerd();
  } else if(command == COMMAND_BACK) {
    back();
  } else if(command == COMMAND_TURN_RIGHT) {
    turn_right();
  } else if(command == COMMAND_TURN_LEFT) {
    turn_left();
  }

}
void loop() {

  speed_level = 3;
  command_input(COMMAND_FOWERD);
  delay(3000);

  command_input(COMMAND_BACK);
  delay(3000);

  speed_level = 8;
  command_input(COMMAND_TURN_RIGHT);
  delay(3000);

  command_input(COMMAND_TURN_LEFT);
  delay(3000);
}
