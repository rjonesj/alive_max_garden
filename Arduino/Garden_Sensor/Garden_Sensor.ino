#include <dht.h>

dht DHT;

const int AirValue = 665;  //you need to replace this with sensor value in air dry
const int WaterValue = 360;  //you need to replace this value with sensor value submerged wet
int soilMoistureValue = 0;
int soilmoisturepercent=0;

#define DELAY_MS 10000
#define DHT11_PIN 7
#define SOIL_PIN A0

void setup() {
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
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
  int chk = DHT.read11(DHT11_PIN);
  if(chk == -1) {
    Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
    Serial.print("Humidity = ");
    Serial.println(DHT.humidity);    
  }
}

void loop() {
  readMoisture();
  readTempAndHumidity();
  delay(DELAY_MS);
}
