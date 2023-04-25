# MKR1010 Environmental & Soil Sensor

Created a soil and enivornmental sensor combination using the Arduino MKR1010, DFRobot SEN0335, and a capacitive soil moisture sensor. Made to improve precision agricultre and can be used for home plants, gardens, ect.
- Measures temperature, soil moisture, humidity, CO2, altitude, AQI, pressure, and volatile organic compounds. 

<p align="left">
    <img width="50%" src="IMAGES/IMG_4878.jpg" style="max-width:50%;"></a>
    <img width="47%" src="IMAGES/IMG_4850.jpg" style="max-width:50%;"></a>
<sub> left is an image of the sensors in action, right is closeup of the circuit</sub>

# Guide
- **sensor.ino** Main program. used to track the combination of both the capacitive soil sensor and environmental sensor.
- **environmental_sensor.ino** used to track the measurements from the environmental sensor.
- **check_esensor_status.ino** is used to check for I2C devices. Can find the address of the environmental sensor. Green light indicates additional sensors are found, red indicates only default is detected.
- **calibrate_soil_sensor.ino** is used to calibrate the capacitve soil sensor. The water and air variables may need to be adjusted according to your device and sensor.

# Todo
- Add display of soil moisture using LCD display.
- Add RGB indicator to indicate if levels are good/bad
