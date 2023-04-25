#include <Wire.h>
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

#define SEA_LEVEL_PRESSURE 1015.0f

void I2C_setup(){
  Wire.begin();

  Serial.begin(9600);
  while(!Serial);
  Serial.println("\nI2C Scanner");
}
int I2C_loop(){
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++){
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if(error == 0){
      Serial.print("I2C Device found: 0x");
      if (address < 16){
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
  }
  return nDevices;
}

void setup(){
  WiFiDrv::pinMode(25, OUTPUT);
  WiFiDrv::pinMode(26, OUTPUT);
  WiFiDrv::pinMode(27, OUTPUT);
  I2C_setup();

}

void loop(){
  if(I2C_loop() > 2){   //sensors connected properly
    WiFiDrv::analogWrite(25, 0);
    WiFiDrv::analogWrite(26, 150);
    WiFiDrv::analogWrite(27, 0);
  }
  else{                 //default MKR1010 connected only
    WiFiDrv::analogWrite(25,150);
    WiFiDrv::analogWrite(26,0);
    WiFiDrv::analogWrite(27,0);
  }

  delay(2000);

  WiFiDrv::analogWrite(25, 0);
  WiFiDrv::analogWrite(26, 0);  
  WiFiDrv::analogWrite(27, 0);

  delay(5000);
}