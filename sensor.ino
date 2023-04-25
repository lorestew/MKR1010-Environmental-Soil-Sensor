#include <Wire.h>
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

#include <DFRobot_BME280.h>
#include <DFRobot_ENS160.h>

#define SEA_LEVEL_PRESSURE 1015.0f

typedef DFRobot_BME280_IIC BME; 
typedef DFRobot_ENS160_I2C ENS;
BME bme(&Wire, 0x76);
ENS ENS160(&Wire, 0x53);
float values[8]; //0=temp, 1=pressure, 2=altitude, 3=humidity, 4=air quality
                  //5=volatile compounds, 6=carbon dioxide, 7=soil moisture

const int air = 840;
const int water = 600;
int moisture;
int moisturePercent;

void printLastOperateStatus(BME::eStatus_t eStatus){
  switch(eStatus) {
  case BME::eStatusOK:    Serial.println("everything ok"); break;
  case BME::eStatusErr:   Serial.println("unknow error"); break;
  case BME::eStatusErrDeviceNotDetected:    Serial.println("device not detected"); break;
  case BME::eStatusErrParameter:    Serial.println("parameter error"); break;
  default: Serial.println("unknow status"); break;
  }
}
void BME280_setup(){
  Serial.begin(9600);
  Serial.println("BME Config Test");
  while(bme.begin() != BME::eStatusOK){
    Serial.println("BME Begin failed");
    printLastOperateStatus(bme.lastOperateStatus);
    delay(2000);
  }
  Serial.println("BME Begin Success");
  delay(1000);
}
void BME280_loop(float arr[]){
  float   temp = bme.getTemperature();
  uint32_t    press = bme.getPressure();
  float   alti = bme.calAltitude(SEA_LEVEL_PRESSURE, press);
  float   humi = bme.getHumidity();

  *(arr+0) = temp;
  *(arr+1) = float(press);
  *(arr+2) = alti;
  *(arr+3) = humi;
}
void ENS160_loop(float arr[]){
  uint8_t AQI = ENS160.getAQI();
  uint16_t TVOC = ENS160.getTVOC();
  uint16_t ECO2 = ENS160.getECO2();
  arr[4] = float(AQI);
  arr[5] = float(TVOC);
  arr[6] = float(ECO2);
}
void soilsensor_loop(float arr[]){
  moisture = analogRead(A0);
  moisturePercent = map(moisture, air, water, 0, 100);

  arr[7] = float(moisturePercent);
}

void setup() {
  BME280_setup();

  ENS160.setPWRMode(ENS160_STANDARD_MODE);
  ENS160.setTempAndHum(bme.getTemperature(), bme.getHumidity());
}

void loop() {
  BME280_loop(values);
  ENS160_loop(values);
  soilsensor_loop(values);

  Serial.println();
  Serial.println("====== ======== ======== ======== ======== ======== ======== ======");
  Serial.print("temperature (unit Celsius):   "); Serial.println(values[0]); //BME280
  Serial.print("pressure (unit pa):           "); Serial.println(values[1]); //BME280
  Serial.print("altitude (unit meter):        "); Serial.println(values[2]); //BME280
  Serial.print("humidity (unit percent):      "); Serial.println(values[3]); //BME280
  Serial.print("air quality index:            "); Serial.println(values[4]); //ENS160
  Serial.print("soil moisture (unit percent): "); Serial.println(values[7]); //SOIL SENSOR
  Serial.print("concentration of total volatile organic compounds (unit ppb): "); Serial.println(values[5]); //EMS160
  Serial.print("carbon dioxide equivalent concentration (unit ppm): "); Serial.println(values[6]); //ENS160
  Serial.println("====== ======== ======== ======== ======== ======== ======== ======");

  delay(500);
}
