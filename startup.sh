python init.py
python cpu_temp.py &
python sensor_temp.py &
python dht11_serial.py &
python garden_server.py

pkill python
echo "Server closed successfully."