/*
Thruster Configuration :

4         1

5         6

3         2

*/

#include <Servo.h>
#include <math.h>

Servo esc[7];

int e[7];

int heave[2], surge, sway, yaw;

int killsw=50;

void setup() {
  pinMode(killsw, INPUT);
  Serial.begin(115200);

  // for(int i = 1; i < 7; i++) {
  //   esc[i].attach(i + 23);
  // }
  esc[1].attach(5);
  esc[2].attach(3);
  esc[3].attach(2);
  esc[4].attach(4);
  esc[5].attach(6);
  esc[6].attach(7);

  //initialising thrusters
  for(int i = 1; i < 7; i++) {
    e[i] = 1500;
    esc[i].writeMicroseconds(e[i]);
  }

  delay(2000);

  Serial.println("working");


}

void loop() {
  int val = digitalRead(killsw);
  if (val == 0){
    // heave1(1600, 1600);
    // delay(3000);
    // Serial.println("working");

    for(int i = 5; i < 7; i++) {
    e[i] = 1600;
    esc[i].writeMicroseconds(e[i]);
    }

    delay(3000);

    surge1(1600);
    delay(4500);
    Serial.println("working");
    
    revolve(1550, 50);
    delay(10000);
    Serial.println("working");
    
    surge1(1600);
    delay(4500);
    Serial.println("working");

  }
  else{
    for(int i = 1; i < 7; i++) {
    e[i] = 1500;
    esc[i].writeMicroseconds(e[i]);
    }
  }
}

void heave1(int pwm1, int pwm2) {
  Serial.println("heave");
  heave[0] = pwm1;
  heave[1] = pwm2;
  for(int i = 5; i < 7; i++) {
    e[i] = heave[i - 5];
    esc[i].writeMicroseconds(e[i]);
}
}

void surge1(int pwm) {
  surge = pwm;
      for(int i = 1; i < 5; i++) {
        e[i] = surge;
        esc[i].writeMicroseconds(e[i]);
      }
}


void revolve(int pwm1, int pwm2) {
  surge = pwm1;
  yaw = pwm2;
  for(int i = 1; i < 5; i++) {
    e[i] = surge + yaw * pow(-1,(i/3));
    esc[i].writeMicroseconds(e[i]);
  }
}

void yaw1(int diff) {
  yaw = diff;
  for(int i = 1; i < 5; i++) {
    e[i] = 1500 + yaw * pow(-1, (i/3));
    esc[i].writeMicroseconds(e[i]);
  }
}

void stop() {
  for(int i = 1; i < 5; i++) {
        e[i] = 1500;
        esc[i].writeMicroseconds(e[i]);
}
}