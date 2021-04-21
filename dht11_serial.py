import serial
import init
from datetime import datetime
from pathlib2 import Path

ser = serial.Serial('/dev/ttyACM0',9600)
s = [0,1]

while True:
	read_serial=ser.readline().strip().replace(" ", "")
	line_split=read_serial.split("=")
	value = line_split[1]
	path = None
	if line_split[0] == "Temperature":
	    path = init.atemp_path
	    temp_c = float(value)
	    temp_f = init.convertToF(temp_c)
	    value = temp_f
	    print "Air Temperature = " + str(temp_f) + "F, " + str(temp_c) +"C"
	elif line_split[0] == "Humidity":
	    path = init.humidity_path
	    print "Humidity = " + value + "%"
		
	try:                    
	    with open(path,'a') as f:
	        now = datetime.now()
	        dt_string = now.strftime("%m/%d/%Y %H:%M:%S")
	        f.write("{0},{1}\n".format(dt_string, str(value)))
	except IOError as e:
	    print(e)
