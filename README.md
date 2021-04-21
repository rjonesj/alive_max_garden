# alive_max_garden

## About
Software to run the ALIVE max garden sensor 205 application.

Remote gardening solution built using Raspberry Pi and Arduino.  Collects air, soil, temperature and humidity data from sensor probes (DHT11 and DS18B20) and displays them in real time graphs on a web application. Could be enhanced for more garden automation.

Power wirelessly using batteries to run and collect data anywhere.


## Setup
1. Upload DHT11_Temp_and_Humidity_Sensor.ino to Arduino board and connect DHT11 sensor to Arduino.  Connect the Arduino via USB to Raspberry Pi.
2. Connect the DS18B20 sensor to the Raspberry Pi using GPIO interface.
3. From a fresh Raspberry Pi image, install dash and pandas Python modules
       
       pip install dash
       sudo apt-get install python-pandas

4. Clone project to Raspberry Pi
       
       git clone https://github.com/rjonesj/alive_max_garden

5. Change into directory and run startup script

       cd alive_max_garden
       chmod +x startup.sh
       ./startup.sh

6. Verify application is up by navigating to http://127.0.0.1:8080.  Other devices can connect on the local network by the ip listed in ifconfig.
