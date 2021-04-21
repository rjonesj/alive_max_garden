import os
import time
import init
from datetime import datetime
from pathlib2 import Path

max_temp_c = 80

def measure_temp():
        temp = os.popen("vcgencmd measure_temp").readline()
        temp = temp.replace("temp=","").strip().split("'")[0]
        
        temp_c = float(temp)
        temp_f = init.convertToF(temp_c)
        try:                    
            with open(init.rtemp_path,'a') as f:
                now = datetime.now()
                dt_string = now.strftime("%m/%d/%Y %H:%M:%S")
                f.write("{0},{1}\n".format(dt_string, temp_c))
        except IOError as e:
            print(e)
        
        if temp_c > max_temp_c:
                print("Warning: CPU temp of "+str(temp_c)+"'C has exceeded Max temp of "+str(max_temp_c)+".")
            
        return "CPU Temp = " +str(temp_f)+ "F, " +str(temp_c)+"C"

while True:
        print(measure_temp())
        time.sleep(init.delay_seconds)
