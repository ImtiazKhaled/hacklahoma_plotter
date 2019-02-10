#include<math.h>
#define EN        8
#define Dmm 12

//Direction pin
#define X_DIR     5
#define Y_DIR     6
#define Z_DIR     7

//Step pin
#define X_STP     2
#define Y_STP     3
#define Z_STP     4


//DRV8825   o989
int delayTime = 2000; //Delay between each pause (uS)
int stps = 640; // Steps to move
char val ='F';
String a = "";
float x = 0;
float y = 0;
float x2=0;
float y2=0;
int i = 0;
int b = 0;
String xtemp = "";
String ytemp = "";
boolean com = false;
boolean penState = false;
int StepDis (float inch) {
  int steps = ((inch * 25.4) / (2 * M_PI * (Dmm / 2))) * 200;

  return steps;
}

void step(byte stepperPin, int steps) {

  for (int i = 0; i < steps; i++) {

    digitalWrite(stepperPin, HIGH);

    delayMicroseconds(delayTime);

    digitalWrite(stepperPin, LOW);

    delayMicroseconds(delayTime);

  }

}

void penAction(boolean state) {
  int steps = StepDis(0.25);
  if (state == false) {
    digitalWrite(Z_DIR, false);
    for (int i = 0; i < steps; i++) {

      digitalWrite(Z_STP, HIGH);

      delayMicroseconds(delayTime);

      digitalWrite(Z_STP, LOW);

      delayMicroseconds(delayTime);

    }
  } else {
    digitalWrite(Z_DIR, true);
    for (int i = 0; i < steps; i++) {

      digitalWrite(Z_STP, HIGH);

      delayMicroseconds(delayTime);

      digitalWrite(Z_STP, LOW);

      delayMicroseconds(delayTime);

    }
  }

}

void XY(float x, float y) {
  boolean Ydir = false;
  boolean Xdir = false;
  int tsteps;
  int Xsteps = abs(StepDis(x));
  int Ysteps = abs(StepDis(y));
  Serial.print(Xsteps);
  Serial.print("*");
  Serial.print(Ysteps);
  Serial.print("=");
  if (x > 0) {
    Xdir = true;
  }
  if (y > 0) {
    Ydir = true;
  }
  digitalWrite(X_DIR, Xdir);
  digitalWrite(Y_DIR, Ydir);
  delay(100);
  if (x == 0) {

    tsteps = abs(Ysteps);
    Serial.println(tsteps);
    Serial.println("CASE 1");
    step(Y_STP, Ysteps);
  } else if (y == 0) {

    tsteps = abs(Xsteps);
    Serial.println(tsteps);
    Serial.println("CASE 2");
    step(X_STP, Xsteps);
  } else {

    tsteps = abs(Xsteps * Ysteps);
    Serial.println(tsteps);
    Serial.println("CASE 3");
    for (int i = 0; i < tsteps; i++) {
      if (i % Xsteps == 0) {
        Serial.print(i);
        Serial.print("X ");
        Serial.println(Xdir);
        digitalWrite(X_STP, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(X_STP, LOW);
        delayMicroseconds(delayTime);
      }
      if (i % Ysteps == 0) {
        Serial.print(i);
        Serial.print("Y ");
        Serial.println(Ydir);
        digitalWrite(Y_STP, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(Y_STP, LOW);
        delayMicroseconds(delayTime);
      }
    }
  }


}

void setup() {

  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);

  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);

  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);

  pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW);

  Serial.begin(9600);
}

void loop() {

  while (Serial.available()) {
    val = Serial.read();
    a=a+val;
    if(a.charAt(a.length()-1)=='E'){
      
      for (i = 0; i < a.length(); i++) {
        if (a.charAt(i) == 'Y') {
          com = true;
          b = i;
        }
      }
      xtemp = a.substring(1, b);
      ytemp = a.substring(b + 1, a.length()-1);
      x = xtemp.toFloat();
      y = ytemp.toFloat();
      Serial.println(x-x2);
      Serial.println(y-y2);
      XY(x-x2,y-y2);
      Serial.print(x-x2);
      Serial.print(",");
      Serial.println(y-y2);
      x2=x;
      y2=y;
      a="";
      break;
    }
    /*Serial.println(a);
    if (a == "T") {
      penAction(true);
      Serial.println("Pen Engaged");
    } else if (a == "F") {
      penAction(false);
      Serial.println("Pen Disengaged");
    } 
    else {

      for (i = 0; i < a.length(); i++) {
        if (a.charAt(i) == ',') {
          com = true;
          b = i;
        }
      }
      xtemp = a.substring(0, b);
      ytemp = a.substring(b + 1, a.length());
      x = xtemp.toFloat();
      y = ytemp.toFloat();
      Serial.print(x);
      Serial.print(",");
      Serial.println(y);
      xtemp = "";
      ytemp = "";
      b = 0;
    
    //step(false, X_DIR, X_STP, StepDis(x));
    //step(true, X_DIR, X_STP, StepDis(x));
    //step(false, Y_DIR, Y_STP, StepDis(y));

    if (x != 0 || y != 0) {
      XY(x, y);
    }

    x = 0;
    y = 0;
    com = false;
  }*/
  }
}
