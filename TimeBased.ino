int directionPinR = 12;
int pwmPinR = 3;
int brakePinR = 9;
int directionPinL = 13;
int pwmPinL = 11;
int brakePinL = 8;

void setup() {
 pinMode(directionPinR, OUTPUT);
 pinMode(pwmPinR, OUTPUT);
 pinMode(brakePinR, OUTPUT);
 pinMode(directionPinL, OUTPUT);
 pinMode(pwmPinL, OUTPUT);
 pinMode(brakePinL, OUTPUT);
 digitalWrite(brakePinR, LOW);
 digitalWrite(brakePinL, LOW);
 digitalWrite(directionPinL, HIGH);
 digitalWrite(directionPinR, LOW);
 Serial.begin(9600);
 delay(1000);
}

void start() {
   digitalWrite(directionPinL, HIGH);
 digitalWrite(directionPinR, HIGH);
 digitalWrite(brakePinR, LOW);
 digitalWrite(brakePinL, LOW);
 analogWrite(pwmPinR, 120.5);
 analogWrite(pwmPinL, 124.5);
 delay(590);
 digitalWrite(brakePinR, HIGH);
 digitalWrite(brakePinL, HIGH);
 delay(1000);
}

void forward() {
   digitalWrite(directionPinL, HIGH);
 digitalWrite(directionPinR, HIGH);
 digitalWrite(brakePinR, LOW);
 digitalWrite(brakePinL, LOW);
 analogWrite(pwmPinR, 255);
 analogWrite(pwmPinL, 255);
 delay(1050);
 digitalWrite(brakePinR, HIGH);
 digitalWrite(brakePinL, HIGH);
 delay(1000);
}
void speed(){
     digitalWrite(directionPinL, HIGH);
 digitalWrite(directionPinR, HIGH);
 digitalWrite(brakePinR, LOW);
 digitalWrite(brakePinL, LOW);
 analogWrite(pwmPinR, 255);
 analogWrite(pwmPinL, 255);
 delay(650);
 digitalWrite(brakePinR, HIGH);
 digitalWrite(brakePinL, HIGH);
 delay(1000);
}
void left() {
 digitalWrite(brakePinR, LOW);
 digitalWrite(brakePinL, LOW);
 digitalWrite(directionPinR, HIGH);
  digitalWrite(directionPinL, LOW);
 analogWrite(pwmPinR, 120.5);
 analogWrite(pwmPinL, 125);
 delay(350);
 digitalWrite(brakePinR, HIGH);
 digitalWrite(brakePinL, HIGH);
 digitalWrite(directionPinL, LOW);
 digitalWrite(directionPinR, HIGH);
 delay(1000);
}

void right() {
 digitalWrite(brakePinR, LOW);
 digitalWrite(brakePinL, LOW);  
 digitalWrite(directionPinL, HIGH);
  digitalWrite(directionPinR, LOW);
 analogWrite(pwmPinR, 120.5);
 analogWrite(pwmPinL, 125);
 delay(360);
 digitalWrite(brakePinR, HIGH);
 digitalWrite(brakePinL, HIGH);
 digitalWrite(directionPinL, LOW);
 digitalWrite(directionPinR, HIGH);
 delay(1000);
}

void backward() {
 digitalWrite(brakePinR, HIGH);
 digitalWrite(brakePinL, LOW);
 digitalWrite(directionPinR, HIGH);
 digitalWrite(directionPinL, LOW);
 analogWrite(pwmPinR, 120.5);
 analogWrite(pwmPinL, 125);
 delay(1300);
 digitalWrite(brakePinR, HIGH);
 digitalWrite(brakePinL, HIGH);
 digitalWrite(directionPinL, HIGH);
 digitalWrite(directionPinR, HIGH);
 delay(1000);
}

double time=0;
  void loop(){
    if (time==0) {
      delay(1000);
  forward();
  forward();
  forward();
  forward();
  forward();
  forward();
  forward();
  forward();
  forward();
  forward();

  time++;
}
}
