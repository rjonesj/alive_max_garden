# alive_max_garden

## About
Software to run the ALIVE max garden sensor 205 application. Written for Python 2.7.16.

Remote gardening solution built using Raspberry Pi and Arduino.  Collects light, soil temperature / moisture, and air temperature / humidity data from sensor probes (DHT11, DS18B20, TSL2591, Capacitive Soil Moisture) and displays them in real time graphs in a web application. Could be enhanced for more garden automation.

Power wirelessly using batteries to run and collect data anywhere.


## Setup
1. Install DHT sensor library, Adafruit_Sensor, adafruit tsl2591, and Adafruit Unified Sensor libraries through the Arduino library manager.
2. Connect DHT11, TSL2591, and capacitive soil moisture sensors to Arduino and upload Garden_Sensor.ino to Arduino board. Verify readings are returned through the serial monitor. Connect the Arduino via USB to Raspberry Pi.
3. Connect the DS18B20 sensor to the Raspberry Pi using GPIO interface. Verify readings are returned by running sensor_temp.py after cloning the project.
4. From a fresh Raspberry Pi image, install dash and pandas Python modules
       
       pip install dash
       sudo apt-get install python-pandas

5. Clone project to Raspberry Pi
       
       git clone https://github.com/rjonesj/alive_max_garden

6. Change into directory and run startup script

       cd alive_max_garden
       chmod +x startup.sh
       ./startup.sh

7. Verify application is up by navigating to http://127.0.0.1:8080.  Other devices can connect on the local network by the ip listed in ifconfig.
