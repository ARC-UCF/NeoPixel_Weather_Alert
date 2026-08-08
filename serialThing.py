/* 
This script will take a command argument, convert it to raw string, and send
it to the specified serial device.
*/

import serial
import time
import sys

ser = serial.Serial('/dev/ttyACM0', 9600)   // Specify the proper serial port
time.sleep(2);
stringInput = sys.argv[1]
encodedString = stringInput.encode("utf-8")
print(encodedString)
ser.write(encodedString)
ser.close()
