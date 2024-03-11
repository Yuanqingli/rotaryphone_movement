#include <ESP32Servo.h>

Servo myservo1;  // create servo object to control servo1 dial
int servoPin1 = 4;
int buttonPin1 = 6; 
int pos1 = 0;    
bool servo1Moved = false; 
bool movement1Completed = false; 

Servo myservo2;  // create servo object to control servo2 sound
int servoPin2 = 7; 
int buttonPin2 = 2; 
int pos2 = 0;    
bool servo2Moved = false; 
bool movement2Completed = false; 

void setup() {
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  myservo1.setPeriodHertz(50);    
  myservo1.attach(servoPin1, 1000, 2000); // servo1 dial

  myservo2.setPeriodHertz(50);    
  myservo2.attach(servoPin2, 1000, 2000); // servo2 sound
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT_PULLUP);
}

void loop() {
  // Dial Servo1 control
  if (digitalRead(buttonPin1) == LOW && !servo1Moved && !movement1Completed) {
    for (pos1 = 0; pos1 <= 180; pos1+=3) {
      myservo1.write(pos1);
      delay(5);
    }
    for (pos1 = 180; pos1 >= 0; pos1-=3) {
      myservo1.write(pos1);
      delay(5);
    }
    servo1Moved = true;
    movement1Completed = true;
  } else if (digitalRead(buttonPin1) == HIGH && servo1Moved && movement1Completed) {
    servo1Moved = false;
    movement1Completed = false;
  }

  // Sound Servo2 control
  int buttonState2 = digitalRead(buttonPin2);
  static int lastButtonState2 = HIGH;
  static bool isMoving2 = false;

  if (buttonState2 != lastButtonState2) {
    if (buttonState2 == LOW) {
      isMoving2 = !isMoving2;
      delay(100);
    }
  }

  lastButtonState2 = buttonState2;

  if (isMoving2) {
    for (pos2 = 0; pos2 <= 95; pos2 += 4) {
      myservo2.write(pos2);
      delay(2);
    }
    for (pos2 = 95; pos2 >= 0; pos2 -= 4) {
      myservo2.write(pos2);
      delay(2);
    }
  } else {
    myservo2.write(0);
  }
}
