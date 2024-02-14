/*
Thruster Configuration :

4         1

5         6

3         2

*/

#include <Servo.h>
#include <Math.h>
#include <dht11.h>

const int p_side2 = 9;
const int p_side1 = 8;

Servo esc[7];
dht11 DHT; // Creats a DHT object

int e[7];

int heave[2], surge, sway, yaw;

int pwm, motor, flag = 0;

//unsigned long delay[3] = {};

void setup() {
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
  Serial.println("Enter mode : ");
}

void loop() {
  while(Serial.available() > 0) {
    String input = Serial.readString();
    input.trim();
    //heave control
    if(input == "heave") {
      Serial.println("Enter pwm value 5 :");
      while(!Serial.available()) { } //wait for serial input.
      heave[0] = Serial.parseInt();
      Serial.println("Enter pwm value 6 :");
      while(!Serial.available()) { } //wait for serial input.
      heave[1] = Serial.parseInt();
      for(int i = 5; i < 7; i++) {
        e[i] = heave[i - 5];
        esc[i].writeMicroseconds(e[i]);
      }
    }
    //surge control
    else if(input == "surge") {
      Serial.println("entered");
      Serial.println("Enter pwm value :");
      while(!Serial.available()) { } //wait for serial input.
      surge = Serial.parseInt();
      for(int i = 1; i < 5; i++) {
        e[i] = surge;
        esc[i].writeMicroseconds(e[i]);
      }
      // if(flag == 2) {
      //   delay[2] = millis();
      //   flag = 3;
      //   continue;
      // }
      // delay[0] = millis();
      // flag = 1;
    }
    //sway control
    else if(input == "sway") {
      Serial.println("Enter pwm value :");
      while(!Serial.available()) { } //wait for serial input.
      sway = Serial.parseInt();
      for(int i = 1; i < 5; i++) {
        e[i] = 1500 + sway * pow(-1, i); 
        esc[i].writeMicroseconds(e[i]);
      }
    }
    //yaw control
    else if(input == "yaw") {
      Serial.println("Enter pwm value :");
      while(!Serial.available()) { } //wait for serial input.
      yaw = Serial.parseInt();

      for(int i = 1; i < 5; i++) {
        e[i] = 1500 + yaw * pow(-1, (i/3));
        esc[i].writeMicroseconds(e[i]);
      }
    }
    //revolve manoeuver
    else if(input == "revolve") {
      Serial.println("Enter surge pwm value :");
      while(!Serial.available()) { } //wait for serial input.
      surge = Serial.parseInt();
      Serial.println("Enter yaw diff value :");
      while(!Serial.available()) { } //wait for serial input.
      yaw = Serial.parseInt();
      for(int i = 1; i < 5; i++) {
        e[i] = surge + yaw * pow(-1,(i/3));
        esc[i].writeMicroseconds(e[i]);
      }
      // delay[1] = millis();
      // flag = 2;
    }
    //stopping all thrusters
    else if(input == "stop all") {
      for(int i = 1; i < 7; i++) {
        e[i] = 1500;
        esc[i].writeMicroseconds(e[i]);
      }
    }
    //test loop
    else if(input == "test") {
      Serial.println("Enter motor value :");
      while(!Serial.available()) { } //wait for serial input.
      motor = Serial.parseInt();
      Serial.println("Enter pwm :");
      while(!Serial.available()) { } //wait for serial input.
      e[motor] = Serial.parseInt();
      esc[motor].writeMicroseconds(e[motor]);
    }
    //restart
    // else if(input == "restart") {
    //   delay[3] = {0,0,0};
    //   flag = 0;
    // }
    //stoping only 4 planar thrusters
    else {
      for(int i = 1; i < 5; i++) {
        e[i] = 1500;
        esc[i].writeMicroseconds(e[i]);
      }
      // if(flag == 1) {
      //   delay[0] = millis() - delay[0];
      // }
      // else if(flag == 2) {
      //   delay[1] = millis() - delay[1];
      // }
      // else if(flag == 3) {
      //   delay[2] = millis() - delay[2];
      // }
    }
  }

  Serial.print("T1 : ");
  Serial.print(e[1]);
  Serial.print(" | T2 : ");
  Serial.print(e[2]);
  Serial.print(" | T3 : ");
  Serial.print(e[3]);
  Serial.print(" | T4 : ");
  Serial.print(e[4]);
  Serial.print(" | T5 : ");
  Serial.print(e[5]);
  Serial.print(" | T6 : ");
  Serial.print(e[6]);
  // Serial.print(" | Delay 1 : ");
  // Serial.print(delay[0]);
  // Serial.print(" | Delay 2 : ");
  // Serial.print(delay[1]);
  // Serial.print(" | Delay 3 : ");
  // Serial.print(delay[2]);
  Serial.print(" | P-side1 moisture : ");
  Serial.print(getMoisture(p_side1));
  Serial.print(" | P-side2 moisture : ");
  Serial.println(getMoisture(p_side2));
}

float getMoisture(int pin) {
  int readData = DHT.read(pin); // Reads the data from the sensor
  float h = DHT.humidity; // Gets the values of the humidity

  return h;
}

