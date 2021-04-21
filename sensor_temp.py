import glob
import time
import init
from datetime import datetime
from pathlib2 import Path

base_dir = '/sys/bus/w1/devices/'
device_folder = glob.glob(base_dir + '28*')[0]
device_file = device_folder + '/w1_slave'
 
def read_temp_raw():
    f = open(device_file, 'r')
    lines = f.readlines()
    f.close()
    return lines
 
def read_temp():
    lines = read_temp_raw()
    while lines[0].strip()[-3:] != 'YES':
        time.sleep(0.2)
        lines = read_temp_raw()
    equals_pos = lines[1].find('t=')
    if equals_pos != -1:
        temp_string = lines[1][equals_pos+2:]
        temp_c = float(temp_string) / 1000.0
        temp_f = init.convertToF(temp_c)
        try:                    
            with open(init.stemp_path,'a') as f:
                now = datetime.now()
                dt_string = now.strftime("%m/%d/%Y %H:%M:%S")
                f.write("{0},{1}\n".format(dt_string, temp_f))
        except IOError as e:
            print(e)
        
        return "Sensor temp = " + str(temp_f) + "F, "+ str(temp_c) + "C"

while True:
    print(read_temp())
    time.sleep(init.delay_seconds)
