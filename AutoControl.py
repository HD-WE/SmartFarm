import serial
import datetime
import time

ser = serial.Serial('/dev/ttyACM0')

date_count = 0

while 1:

    date = datetime.datetime.now()

    hour_and_min = date.strftime("%H%M")

    hour = hour_and_min[:2]
    minute = hour_and_min[2:]

    if date_count == 0:
        if hour == "8" and minute == "30":
            ser.write("LEDON\n".encode())
            date_count += 1

    if date_count == 1:
        if hour == "20" and minute == "30":
            ser.write("LEDOFF\n".encode())
            date_count -= 1

    time.sleep(2)   