#define IR_SENSOR_MID 4
#define IR_SENSOR_RIGHT1 11
#define IR_SENSOR_RIGHT2 12
#define IR_SENSOR_LEFT1 3
#define IR_SENSOR_LEFT2 2

#define defaultspeed 220
#define slowerturnspeed 150
#define sharpturnspeed 240
#define sidemidsensoralignment 130
#define extremesensoralignment 255

// Right motor
int enableRightMotor = 6;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;

// Left motor
int enableLeftMotor = 5;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;

static int doublelineright = 0;
static int doublelineleft = 0;
static int tripleline = 0;

const int sharpleftturn = 1;
const int slightleftturn = 2;
const int straight = 3;
const int slightrightturn = 4;
const int sharprightturn = 5;
const int plusjunction = 6;
const int leftjunction = 9;
const int rightjunction = 10;
const int right_mid_signal = 11;
const int left_mid_signal = 12;
const int right_extreme_signal = 13;
const int left_extreme_signal = 14;

int currentstate = 7;
int previousstate = 8;

void setup() {
  // The problem with TT gear motors is that at very low PWM values, they may not rotate.
  // If we increase the PWM value, the motor rotates faster and the robot may go out of the line.
  // For better control, we need to increase the frequency of analogWrite.
  // The following line sets the frequency of PWM signal on pins D5 and D6 to 7812.5 Hz.
  TCCR0B = TCCR0B & B11111000 | B00000010;

  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT1, INPUT);
  pinMode(IR_SENSOR_RIGHT2, INPUT);

  pinMode(IR_SENSOR_LEFT1, INPUT);
  pinMode(IR_SENSOR_LEFT2, INPUT);

  pinMode(IR_SENSOR_MID, INPUT);

  Serial.begin(9600);
  rotateMotor(0, 0);
}

void loop() {

  int outerrightIRSensorValue = digitalRead(IR_SENSOR_RIGHT2);
  int innerrightIRSensorValue = digitalRead(IR_SENSOR_RIGHT1);

  int outerleftIRSensorValue = digitalRead(IR_SENSOR_LEFT2);
  int innerleftIRSensorValue = digitalRead(IR_SENSOR_LEFT1);

  int midIRSensorValue = digitalRead(IR_SENSOR_MID);

  // If none of the sensors detects the black line, then go straight
  if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == HIGH && outerleftIRSensorValue == HIGH && innerleftIRSensorValue == HIGH && midIRSensorValue == HIGH) {
    currentstate = straight;
    if (currentstate != previousstate) {
      rotateMotor(defaultspeed, defaultspeed);
      previousstate = currentstate;
    }
  }

  // If right sensor detects the black line, then turn right
  else if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == HIGH && midIRSensorValue == LOW && innerleftIRSensorValue == HIGH && outerleftIRSensorValue == HIGH) {
    currentstate = straight;

    if (currentstate != previousstate) {
      rotateMotor(defaultspeed, defaultspeed);
      previousstate = currentstate;
    }
  }

  else if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == HIGH && midIRSensorValue == LOW && innerleftIRSensorValue == LOW && outerleftIRSensorValue == HIGH) {
    currentstate = slightrightturn;
    if (currentstate != previousstate) {
      rotateMotor(defaultspeed, slowerturnspeed);
      delay(200);
      previousstate = currentstate;
    }
  }

  else if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == LOW && midIRSensorValue == LOW && innerleftIRSensorValue == HIGH && outerleftIRSensorValue == HIGH) {
    currentstate = slightleftturn;
    if (currentstate != previousstate) {
      rotateMotor(slowerturnspeed, defaultspeed);
      delay(200);
      previousstate = currentstate;
    }
  }

  else if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == LOW && midIRSensorValue == LOW && innerleftIRSensorValue == LOW && outerleftIRSensorValue == HIGH) {
    currentstate = straight;
    if (currentstate != previousstate) {
      rotateMotor(defaultspeed, defaultspeed);
      previousstate = currentstate;
    }
  }

  else if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == LOW && midIRSensorValue == HIGH && innerleftIRSensorValue == HIGH && outerleftIRSensorValue == HIGH) {
    currentstate = right_mid_signal;
    if (currentstate != previousstate) {
      rotateMotor(sidemidsensoralignment, defaultspeed);
      delay(200);
      previousstate = currentstate;
    }
  }

  else if (outerrightIRSensorValue == LOW && innerrightIRSensorValue == HIGH && midIRSensorValue == HIGH && innerleftIRSensorValue == HIGH && outerleftIRSensorValue == HIGH) {
    currentstate = right_extreme_signal;
    if (currentstate != previousstate) {
      rotateMotor(defaultspeed, extremesensoralignment);
      delay(200);
      previousstate = currentstate;
    }
  }

  else if (outerrightIRSensorValue == LOW && innerrightIRSensorValue == LOW && midIRSensorValue == HIGH && innerleftIRSensorValue == HIGH && outerleftIRSensorValue == HIGH) {
    currentstate = right_extreme_signal;
    if (currentstate != previousstate) {
      currentstate = right_extreme_signal;
      rotateMotor(defaultspeed, extremesensoralignment);
      delay(200);
      previousstate = currentstate;
    }
  }

  else if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == HIGH && midIRSensorValue == LOW && innerleftIRSensorValue == LOW && outerleftIRSensorValue == LOW) {
    currentstate = leftjunction;

    if (currentstate != previousstate) {
      delay(300);

      if (midIRSensorValue == LOW && outerrightIRSensorValue == LOW && innerrightIRSensorValue == LOW && innerleftIRSensorValue == LOW && outerleftIRSensorValue == LOW) {
        triplelinefunc();
      }

      else if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == HIGH && midIRSensorValue == LOW && innerleftIRSensorValue == LOW && outerleftIRSensorValue == LOW) {
        Serial.print("doublelineleft: ");
        Serial.println(doublelineleft);

        if (doublelineleft >= 1 && doublelineleft < 2) {
          currentstate = straight;
          rotateMotor(defaultspeed, defaultspeed);
          previousstate = currentstate;
          delay(400);
          doublelineleft++;
        }

        else if (doublelineleft == 0) {
          currentstate = leftjunction;
          rotateMotor(0, 0);
          delay(2000);
          rotateMotor(sharpturnspeed, -sharpturnspeed);
          delay(1850);
          previousstate = currentstate;
          doublelineleft++;
        }

        else if (doublelineleft == 2) {
          currentstate = leftjunction;
          rotateMotor(0, 0);
          delay(2000);
          rotateMotor(sharpturnspeed, -sharpturnspeed);
          delay(1850);
          previousstate = currentstate;
          doublelineleft++;
        }

        else if (doublelineleft == 4) {
          doublelineleft++;
        }

        else if (doublelineleft == 5) {
          currentstate = leftjunction;
          rotateMotor(0, 0);
          delay(2000);
          rotateMotor(sharpturnspeed, -sharpturnspeed);
          delay(1850);
          previousstate = currentstate;
          doublelineleft++;
        }

        else if (doublelineleft == 7) {
          currentstate = leftjunction;
          rotateMotor(0, 0);
          delay(2000);
          rotateMotor(sharpturnspeed, -sharpturnspeed);
          delay(1850);
          rotateMotor(defaultspeed, defaultspeed);
          delay(1500);
          rotateMotor(0, 0);
          previousstate = currentstate;
          doublelineleft++;
        }

        else if (doublelineleft == 8) {
          currentstate = leftjunction;
          rotateMotor(0, 0);
          delay(2000);
          rotateMotor(sharpturnspeed, -sharpturnspeed);
          delay(1850);
          previousstate = currentstate;
          doublelineleft++;
        }

        else {
          currentstate = leftjunction;
          rotateMotor(0, 0);
          delay(2000);
          rotateMotor(sharpturnspeed, -sharpturnspeed);
          delay(1850);
          previousstate = currentstate;
          doublelineleft++;
        }
      }
    }
  }

  else if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == LOW && midIRSensorValue == LOW && innerleftIRSensorValue == LOW && outerleftIRSensorValue == LOW) {
    currentstate = leftjunction;

    if (currentstate != previousstate) {
      delay(300);

      if (midIRSensorValue == LOW && outerrightIRSensorValue == LOW && innerrightIRSensorValue == LOW && innerleftIRSensorValue == LOW && outerleftIRSensorValue == LOW) {
        triplelinefunc();
      }

      else if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == LOW && midIRSensorValue == LOW && innerleftIRSensorValue == HIGH && outerleftIRSensorValue == LOW) {
        Serial.print("doublelineleft: ");
        Serial.println(doublelineleft);

        if (doublelineleft >= 1 && doublelineleft < 2) {
          currentstate = straight;
          rotateMotor(defaultspeed, defaultspeed);
          previousstate = currentstate;
          delay(400);
          doublelineleft++;
        }

        else if (doublelineleft == 0) {
          currentstate = leftjunction;
          rotateMotor(0, 0);
          delay(2000);
          rotateMotor(sharpturnspeed, -sharpturnspeed);
          delay(1800);
          previousstate = currentstate;
          doublelineleft++;
        }

        else if (doublelineleft == 2) {
          currentstate = leftjunction;
          rotateMotor(0, 0);
          delay(2000);
          rotateMotor(sharpturnspeed, -sharpturnspeed);
          delay(1800);
          previousstate = currentstate;
          doublelineleft++;
        }

        else if (doublelineleft == 4) {
          doublelineleft++;
        }

        else if (doublelineleft == 6) {
          doublelineleft++;
        }

        else if (doublelineleft == 5) {
          currentstate = leftjunction;
          rotateMotor(0, 0);
          delay(2000);
          rotateMotor(sharpturnspeed, -sharpturnspeed);
          delay(1800);
          previousstate = currentstate;
          doublelineleft++;
        }

        else if (doublelineleft == 7) {
          currentstate = leftjunction;
          rotateMotor(0, 0);
          delay(2000);
          rotateMotor(sharpturnspeed, -sharpturnspeed);
          delay(1800);
          previousstate = currentstate;
          doublelineleft++;
        }

        else if (doublelineleft == 8) {
          currentstate = leftjunction;
          rotateMotor(defaultspeed, defaultspeed);
          delay(1500);
          rotateMotor(0, 0);
          previousstate = currentstate;
          doublelineleft++;
        }

        else {
          currentstate = leftjunction;
          rotateMotor(0, 0);
          delay(2000);
          rotateMotor(sharpturnspeed, -sharpturnspeed);
          delay(1800);
          previousstate = currentstate;
          doublelineleft++;
        }
      }
    }
  }

  else if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == HIGH && midIRSensorValue == HIGH && innerleftIRSensorValue == LOW && outerleftIRSensorValue == HIGH) {
    currentstate = left_mid_signal;

    if (currentstate != previousstate) {
      rotateMotor(defaultspeed, sidemidsensoralignment);
      delay(300);
      previousstate = currentstate;
    }
  }

  else if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == HIGH && midIRSensorValue == HIGH && innerleftIRSensorValue == HIGH && outerleftIRSensorValue == LOW) {
    currentstate = left_extreme_signal;

    if (currentstate != previousstate) {
      rotateMotor(extremesensoralignment, defaultspeed);
      delay(200);

      previousstate = currentstate;
    }
  }

  else if (outerrightIRSensorValue == HIGH && innerrightIRSensorValue == HIGH && midIRSensorValue == HIGH && innerleftIRSensorValue == LOW && outerleftIRSensorValue == LOW) {
    currentstate = left_extreme_signal;

    if (currentstate != previousstate) {
      rotateMotor(extremesensoralignment, defaultspeed);
      delay(200);

      previousstate = currentstate;
    }
  }

  else if (midIRSensorValue == LOW && outerrightIRSensorValue == LOW && innerrightIRSensorValue == LOW && innerleftIRSensorValue == LOW && outerleftIRSensorValue == LOW) {
    currentstate = plusjunction;

    if (currentstate != previousstate) {
      Serial.print("tripleline: ");
      Serial.println(tripleline);

      if (tripleline == 2) {
        currentstate = plusjunction;
        rotateMotor(0, 0);
        delay(2100);
        rotateMotor(sharpturnspeed, -sharpturnspeed);
        previousstate = currentstate;
        delay(1800);
        tripleline++;

      }

      else if (tripleline == 4) {
        currentstate = plusjunction;
        rotateMotor(0, 0);
        delay(2100);
        rotateMotor(sharpturnspeed, -sharpturnspeed);
        previousstate = currentstate;
        delay(1800);
        tripleline++;
      }

      else {
        currentstate = plusjunction;
        rotateMotor(defaultspeed, defaultspeed);
        previousstate = currentstate;
        delay(150);
        tripleline++;
      }
    }
    previousstate = currentstate;
  }

  // If both sensors detect the black lineelse
  else {
    currentstate = straight;
    if (currentstate != previousstate) {
      rotateMotor(defaultspeed, defaultspeed);
      previousstate = currentstate;
    }
  }
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  }

  else if (rightMotorSpeed > 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }

  else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  }

  else if (leftMotorSpeed > 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }

  else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}

void triplelinefunc() {
  currentstate = plusjunction;

  if (currentstate != previousstate) {
    Serial.print("tripleline: ");
    Serial.println(tripleline);

    if (tripleline == 2) {
      currentstate = plusjunction;
      rotateMotor(0, 0);
      delay(2000);
      rotateMotor(sharpturnspeed, -sharpturnspeed);
      previousstate = currentstate;
      tripleline++;
      delay(1750);
    }

    else if (tripleline == 4) {
      currentstate = plusjunction;
      rotateMotor(0, 0);
      delay(2000);
      rotateMotor(sharpturnspeed, -sharpturnspeed);
      previousstate = currentstate;
      tripleline++;
      delay(1750);
    }

    else {
      currentstate = plusjunction;
      rotateMotor(defaultspeed, defaultspeed);
      previousstate = currentstate;
      delay(150);
      tripleline++;
    }
  }

  previousstate = currentstate;
}