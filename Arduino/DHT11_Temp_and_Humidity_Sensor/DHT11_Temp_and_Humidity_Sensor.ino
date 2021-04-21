#include <dht.h>

dht DHT;

#define DHT11_PIN 7
#define DELAY_MS 10000

void setup(){
  Serial.begin(9600);
}

void loop(){
  int chk = DHT.read11(DHT11_PIN);
  if(chk == -1) {
    Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
    Serial.print("Humidity = ");
    Serial.println(DHT.humidity);    
  }
  delay(DELAY_MS);
}
