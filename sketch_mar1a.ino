#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

//encoder pins
Encoder knobLeft(0, 6);
Encoder knobRight(1, 7);

// enum to allow for writing direction names in directions[]
enum Direction {
  start = 0,
  forwardDefualt = 1,
  rightTurn = 2,
  leftTurn = 3,
  end = 4,
};

constexpr int directions[] = { rightTurn, end };  // creates a list of the directions

//all of the pins for the robot
constexpr int DIRECTION_PIN_R = 12;
constexpr int PWM_PIN_R = 3;
constexpr int BRAKE_PIN_R = 9;
constexpr int DIRECTION_PIN_L = 13;
constexpr int PWM_PIN_L = 11;
constexpr int BRAKE_PIN_L = 8;

constexpr int directionsOffsetsLeft[] = { 10, 36, 5, -5, 0 };  // start-forward-left right-stop encoder offsets
constexpr int directionsOffsetsRight[] = { 10, 36, -5, 5, 0 };  // start-forward-left right-stop encoder offsets
//creating intial pos, unsure why they are big num, but thats how the example code had it
int posRight = -999,
    posLeft = -999;

//sets the prev values to 0, unsure why they are 0, but thats how the example
int prevLeft = 0,
    prevRight = 0;

//bool to allow for tracking of its state of completion
bool rightReached = false,
     leftReached = false;


int indexA = 0;                   //index of what direction you are on in dirctions
int indexB = directions[indexA];  //index of what offset from directionsOffsets

//sets all pins to outputs and sets their speed to 0
void setup() {
  pinMode(DIRECTION_PIN_R, OUTPUT);
  pinMode(PWM_PIN_R, OUTPUT);
  pinMode(BRAKE_PIN_R, OUTPUT);
  pinMode(DIRECTION_PIN_L, OUTPUT);
  pinMode(PWM_PIN_L, OUTPUT);
  pinMode(BRAKE_PIN_L, OUTPUT);
  digitalWrite(BRAKE_PIN_R, LOW);
  digitalWrite(BRAKE_PIN_L, LOW);
  digitalWrite(DIRECTION_PIN_R, LOW);
  digitalWrite(DIRECTION_PIN_L, HIGH);
  delay(2500);
  Serial.begin(9600);
}

//makes the code not error out
void drive(int index);
void stopR();
void stopL();
void forwardR();
void forwardL();

//main
void loop() {
  //reads encoder
  posLeft = knobLeft.read();
  posRight = knobRight.read();

  // checks if the right has been reached by comparing the posRight to the position before the current direction minus the offset of the current direction, stops if true
  float targetRight = (prevRight - directionsOffsetsRight[indexB]);

  rightReached = (posRight == targetRight);
  if (rightReached) {
    stopR();
  }
  // checks if the left has been reached by comparing the posRight to the position before the current direction plus the offset of the current direction, stops if true
  float targetLeft = (prevLeft + directionsOffsetsLeft[indexB]);
  
  leftReached = (posLeft >= targetLeft);
  if (leftReached) {
    stopL();
  }
  //if both left and right have been reached, move on to the next command by setting the new prev right and left values, increasing the directions index and assigning the new offset index
  if (leftReached && rightReached) {
    indexA++;
    indexB = directions[indexA];
    prevLeft = posLeft;
    prevRight = posRight;
  }
  //run the drive
  drive(indexA);
}

void drive(int index) {
  switch (directions[index]) {
    case forwardDefualt:  //if forward
      if (!rightReached)
        forwardR();
      if (!leftReached)
        forwardL();
      break;
    case rightTurn:  //if right
      if (!rightReached)
        reverseR();
      if (!leftReached)
        forwardL();
      break;
    case leftTurn:  //if left
      if (!rightReached)
        forwardR();
      if (!leftReached)
        reverseL();
      break;
    case end:  //if stop
      stopL();
      stopR();
      break;
    case start:  // if start
      if (!rightReached)
        forwardR();
      if (!leftReached)
        forwardL();
      break;
  }
}

void stopL() {  //stops left motors
  digitalWrite(BRAKE_PIN_L, HIGH);
  analogWrite(PWM_PIN_L, 0);
}

void stopR() {  //stops right motors
  digitalWrite(BRAKE_PIN_R, HIGH);
  analogWrite(PWM_PIN_R, 0);
}

void forwardR() {  //starts right motors
  digitalWrite(DIRECTION_PIN_R, LOW);
  digitalWrite(BRAKE_PIN_R, LOW);
  analogWrite(PWM_PIN_R, 105);
}

void forwardL() {  //starts left motors
  digitalWrite(DIRECTION_PIN_L, HIGH);
  digitalWrite(BRAKE_PIN_L, LOW);
  analogWrite(PWM_PIN_L, 105);
}

void reverseL() {  //reverse left motors
  digitalWrite(DIRECTION_PIN_L, LOW);
  digitalWrite(BRAKE_PIN_L, LOW);
  analogWrite(PWM_PIN_L, 105);
}

void reverseR() {  //reverse right motors
  digitalWrite(DIRECTION_PIN_R, HIGH);
  digitalWrite(BRAKE_PIN_R, LOW);
  analogWrite(PWM_PIN_R, 105);
}
