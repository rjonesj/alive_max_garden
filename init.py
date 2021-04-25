import os
from datetime import datetime
from pathlib2 import Path

delay_seconds = 10
rtemp_path = "data/rtemp_c.csv"
stemp_path = "data/stemp_f.csv"
atemp_path = "data/atemp_f.csv"
humidity_path = "data/humidity.csv"
moisture_path = "data/moisture.csv"

def convertToF(temp_c):
    return temp_c * 9.0 / 5.0 + 32.0

#Script initializes folders and files for data collection

temp_file = Path(rtemp_path)
if not temp_file.exists():
    try:        
        p_path = os.path.join(str(Path().absolute()), "data")
        
        try:
            Path(p_path).mkdir(exist_ok=True)
            print("Data directory initialized at: "+p_path)
        except OSError as error:
            print("Warning: Directory could not be created at: "+p_path)
        
        with open(rtemp_path,'w') as f:
            f.write("datetime,temperature\n")
        with open(stemp_path,'w') as f:
            f.write("datetime,temperature\n")
        with open(humidity_path,'w') as f:
            f.write("datetime,humidity\n")
        with open(atemp_path,'w') as f:
            f.write("datetime,temperature\n")
        with open(moisture_path,'w') as f:
            f.write("datetime,moisture\n")
    except IOError as e:
        print(e)
