//sensor
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
//servo
#include <Servo.h>

Servo pivot; //main servo
Servo adjust; //second servo

Adafruit_LIS3DH lis = Adafruit_LIS3DH(); //I2C interface

float gravity = 9.5; //default gravity
int upSpeed = 0;  //dictates movement of arms
int downSpeed = 0;

int pos1 = 0;    // variable to store the servo position
int pos2 = 0;

void setup(void) {

  pivot.attach(9);
  adjust.attach(8);

  Serial.begin(9600);
  //Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");

}

void loop() {
  lis.read();      // get X Y and Z data at once
  
  sensors_event_t event; //normalize data
  lis.getEvent(&event);

  //Serial.print("Z: "); Serial.print(event.acceleration.z); 
  gravity = event.acceleration.z;
  //Serial.println(" m/s^2 ");

  if(9 <= gravity && gravity <= 10){
    //Serial.print("steady");
  }else if(gravity < 9){
    //Serial.print("up");
  }else{
    //Serial.print("down");
  }

   int a = 10 - round(gravity);
   Serial.println(a);

   //pivot.write(90 + a);
   Serial.print(a);
   Serial.println();
   Serial.print(90+a);
   Serial.println();
   delay(500);
}
