#include <dht.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"

dht DHT;

const int AirValue = 665;  //you need to replace this with sensor value in air dry
const int WaterValue = 360;  //you need to replace this value with sensor value submerged wet
int soilMoistureValue = 0;
int soilmoisturepercent=0;

#define DELAY_MS 10000
#define DHT11_PIN 7
#define SOIL_PIN A0

/* TSL2591 Digital Light Sensor */
/* Dynamic Range: 600M:1 */
/* Maximum Lux: 88K */

// Example for demonstrating the TSL2591 library - public domain!

// connect SCL to I2C Clock
// connect SDA to I2C Data
// connect Vin to 3.3-5V DC
// connect GROUND to common ground

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); // pass in a number for the sensor identifier (for your use later)

/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void displaySensorDetails(void)
{
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(sensor.max_value); Serial.println(F(" lux"));
  Serial.print  (F("Min Value:    ")); Serial.print(sensor.min_value); Serial.println(F(" lux"));
  Serial.print  (F("Resolution:   ")); Serial.print(sensor.resolution, 4); Serial.println(F(" lux"));  
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
  delay(500);
}

/**************************************************************************/
/*
    Configures the gain and integration time for the TSL2591
*/
/**************************************************************************/
void configureSensor(void)
{
  // You can change the gain on the fly, to adapt to brighter/dimmer light situations
  //tsl.setGain(TSL2591_GAIN_LOW);    // 1x gain (bright light)
  tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
  //tsl.setGain(TSL2591_GAIN_HIGH);   // 428x gain
  
  // Changing the integration time gives you a longer time over which to sense light
  // longer timelines are slower, but are good in very low light situtations!
  //tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);  // shortest integration time (bright light)
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_200MS);
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_400MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_500MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);  // longest integration time (dim light)

  /* Display the gain and integration time for reference sake */  
  /*
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Gain:         "));
  tsl2591Gain_t gain = tsl.getGain();
  switch(gain)
  {
    case TSL2591_GAIN_LOW:
      Serial.println(F("1x (Low)"));
      break;
    case TSL2591_GAIN_MED:
      Serial.println(F("25x (Medium)"));
      break;
    case TSL2591_GAIN_HIGH:
      Serial.println(F("428x (High)"));
      break;
    case TSL2591_GAIN_MAX:
      Serial.println(F("9876x (Max)"));
      break;
  }
  Serial.print  (F("Timing:       "));
  Serial.print((tsl.getTiming() + 1) * 100, DEC); 
  Serial.println(F(" ms"));
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
  */
}

void initializeLightSensor() {  
  if (!tsl.begin())  {
    Serial.println(F("No TSL2591 light sensor found ... check your wiring?"));
    while (1);
  }
    
  /* Display some basic information on this sensor */
  //displaySensorDetails();
  
  /* Configure the sensor */
  configureSensor();  
}

void setup() {
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
  initializeLightSensor();
}

/**************************************************************************/
/*
    Show how to read IR and Full Spectrum at once and convert to lux
*/
/**************************************************************************/
void readLight(void)
{
  // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
  // That way you can do whatever math and comparisons you want!
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  //Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
  //Serial.print(F("IR: ")); Serial.print(ir);  Serial.print(F("  "));
  //Serial.print(F("Full: ")); Serial.print(full); Serial.print(F("  "));
  //Serial.print(F("Visible: ")); Serial.print(full - ir); Serial.print(F("  "));
  Serial.print(F("Lux = ")); Serial.println(tsl.calculateLux(full, ir), 6);
}

void readMoisture() {
  soilMoistureValue = analogRead(SOIL_PIN);  //put Sensor insert into soil
  Serial.print("Moisture = ");
  Serial.println(soilMoistureValue);

  /*
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  
  Serial.print("Moisture = ");
  if(soilmoisturepercent >= 100)
  {
    Serial.println("100");
  }
  else if(soilmoisturepercent <= 0)
  {
    Serial.println("0");
  }
  else if(soilmoisturepercent >0 && soilmoisturepercent < 100)
  {
    Serial.println(soilmoisturepercent);
  }  
  */
}

void readTempAndHumidity() {
  int chk = 0;
  while(chk != -1) {
    chk = DHT.read11(DHT11_PIN);
  }
  
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);    
}

void loop() {
  readMoisture();
  readTempAndHumidity();
  readLight();
  delay(DELAY_MS);
}
