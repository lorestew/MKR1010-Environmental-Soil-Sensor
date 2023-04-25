//dry soil 806
//moist; before water 667
//after water 615
//after after water 680-610

const int AirValue = 840;   //set to value in open air
const int WaterValue = 600;  //set to value submerged in water
int soilMoistureValue;
int percentage;

void setup(){
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
}
void loop(){
  soilMoistureValue = analogRead(A0);
  percentage = map(soilMoistureValue, AirValue, WaterValue, 0, 100);

  Serial.print("soil moisture value: "); Serial.println(soilMoistureValue);
  Serial.print("soil moisture (unit percent): "); Serial.println(percentage);
  
  delay(500);
}