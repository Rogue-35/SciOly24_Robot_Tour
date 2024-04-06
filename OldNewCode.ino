#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
Encoder knobLeft(0, 6);
Encoder knobRight(1, 7);
int targetR = 0;
int targetL = 0;

enum Direction {
  start             = 0,
  forwardDefault    = 1,
  leftTurn          = 2,
  rightTurn         = 3,
  end               = 4,
  forwardStart      = 5,
  forwardTurnLeft   = 6,
  forwardTurnRight  = 7,
  pause              = 8

  //if runinng ff need to run ffs
  //if running sf need run ssss
  //
};

unsigned int directions[] = {1,0,1 ,4};
unsigned int directionsIndexL = 0;
unsigned int directionsIndexR = 0;
unsigned int directionsValue = 0;
bool directionR;
bool directionL;
unsigned int var1 = 0;
unsigned int var2 = 1;
unsigned int trueIndex = 0;

constexpr int directionPinR = 12;
constexpr int pwmPinR = 3;
constexpr int brakePinR = 9;
constexpr int directionPinL = 13;
constexpr int pwmPinL = 11;
constexpr int brakePinL = 8;
constexpr int startDist = 44;
constexpr int forwardDist = 106;
constexpr int turnDistR = 37; //34
constexpr int turnDistL = 38; //34

constexpr int forwardTurn = 126;

bool tempL = 0;
bool tempR = 0;
long positionLeft = -999;
long positionRight = -999;
long newLeft, newRight;

void setup() {
  delay(2500);
}

void loop() {
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    positionLeft = newLeft;
    positionRight = newRight;
  }
  if (directionsIndexL == directionsIndexR) {
    directionsValue = directions[directionsIndexL];
    var1 = directionsIndexL;
    trueIndex = directionsIndexL;
  }
  if (var1 == var2) {
    var2++;
    tempR = 0;
    tempL = 0;
  }
  if (directionsIndexL > directionsIndexR) {
    brakeL();
  }
  if (directionsIndexR > directionsIndexL) {
    brakeR();
  }
  drive();
}

void drive() {
  if (directionsValue == 1) {
    if (tempR == 0) {
      targetR = newRight - forwardDist;
      tempR++;
      directionR = true;
    }
    if (tempL == 0) {
      targetL = newLeft + forwardDist;
      tempL++;
      directionL = true;
    }
    if (targetL > newLeft) {
      forwardL();
    } else {
      brakeL();
      directionsIndexL = trueIndex + 1;
    }
    if (targetR < newRight) {
      forwardR();
    } else {
      brakeR();
      directionsIndexR = trueIndex + 1;
    }
  } else if (directionsValue == 2) {
    if (tempR == 0) {
      targetR = newRight - turnDistL;
      tempR++;
      directionR = true;
    }
    if (tempL == 0) {
      targetL = newLeft - turnDistL;
      tempL++;
      directionL = true;
    }
    if (targetL < newLeft) {
      reverseL();
    } else {
      brakeL();
      directionsIndexL = trueIndex + 1;
    }
    if (targetR < newRight) {
      forwardR();
    } else {
      brakeR();
      directionsIndexR = trueIndex + 1;
    }
  } else if (directionsValue == 3) {
    if (tempR == 0) {
      targetR = newRight + turnDistR;
      tempR++;
      directionR = true;
    }
    if (tempL == 0) {
      targetL = newLeft + turnDistR;
      tempL++;
      directionL = true;
    }
    if (targetL > newLeft) {
      forwardL();
    } else {
      brakeL();
      directionsIndexL = trueIndex + 1;
    }
    if (targetR > newRight) {
      reverseR();
    } else {
      brakeR();
      directionsIndexR = trueIndex + 1;
    }
  } else if (directionsValue == 0) {
    if (tempR == 0) {
      targetR = newRight - startDist;
      tempR++;
      directionR = true;
    }
    if (tempL == 0) {
      targetL = newLeft + startDist;
      tempL++;
      directionL = true;
    }
    if (targetL > newLeft) {
      forwardL();
    } else {
      brakeL();
      directionsIndexL = trueIndex + 1;
    }
    if (targetR < newRight) {
      forwardR();
    } else {
      brakeR();
      directionsIndexR = trueIndex + 1;
    }
  } else if (directionsValue == 4) {
    brakeL();
    brakeR();
  } else if (directionsValue == 5){
    if (tempR == 0) {
      targetR = newRight - forwardStart;
      tempR++;
      directionR = true;
    }
    if (tempL == 0) {
      targetL = newLeft + forwardStart;
      tempL++;
      directionL = true;
    }
    if (targetL > newLeft) {
      forwardL();
    } else {
      brakeL();
      directionsIndexL = trueIndex + 1;
    }
    if (targetR < newRight) {
      forwardR();
    } else {
      brakeR();
      directionsIndexR = trueIndex + 1;
    }
  }else if(directionsValue == 6){
if (tempR == 0) {
      targetR = newRight - forwardTurn;
      tempR++;
      directionR = true;
    }
    if (tempL == 0) {
      targetL = newLeft + forwardTurn/1.3;
      tempL++;
      directionL = true;
    }
    if (targetL > newLeft) {
      forwardL();
    } else {
      brakeL();
      directionsIndexL = trueIndex + 1;
    }
    if (targetR < newRight) {
      forwardR();
    } else {
      brakeR();
      directionsIndexR = trueIndex + 1;
    }
  }else if(directionsValue == 7){
    if (tempR == 0) {
      targetR = newRight - forwardTurn/1.3;
      tempR++;
      directionR = true;
    }
    if (tempL == 0) {
      targetL = newLeft + forwardTurn;
      tempL++;
      directionL = true;
    }
    if (targetL > newLeft) {
      forwardL();
    } else {
      brakeL();
      directionsIndexL = trueIndex + 1;
    }
    if (targetR < newRight) {
      forwardR();
    } else {
      brakeR();
      directionsIndexR = trueIndex + 1;
    }
  }else {
    brakeL();
    brakeR();
    pauser(1000);
  }
}
void forwardR() {
  digitalWrite(directionPinR, LOW);
  digitalWrite(brakePinR, LOW);
  analogWrite(pwmPinR, 145);
}
void forwardL() {
  digitalWrite(directionPinL, HIGH);
  digitalWrite(brakePinL, LOW);
  analogWrite(pwmPinL, 145);
}
void reverseR() {
  digitalWrite(directionPinR, HIGH);
  digitalWrite(brakePinR, LOW);
  analogWrite(pwmPinR, 145);
}
void reverseL() {
  digitalWrite(directionPinL, LOW);
  digitalWrite(brakePinL, LOW);
  analogWrite(pwmPinL, 145);
}
void brakeR() {
  digitalWrite(brakePinR, HIGH);
  analogWrite(pwmPinR, 0);
}
void brakeL() {
  digitalWrite(brakePinL, HIGH);
  analogWrite(pwmPinL, 0);
}
void pauser(int time){
  delay(time);
}
