import serial
import datetime
import time

ser = serial.Serial('/dev/ttyACM0')

led_date_count = 0
water_date_count = 0

while 1:

    date = datetime.datetime.now()

    hour_and_min = date.strftime("%H%M")

    hour = hour_and_min[:2]
    minute = hour_and_min[2:]

    if led_date_count == 0:
        if hour == "8" and minute == "30":
            ser.write("LEDON\n".encode())
            led_date_count += 1

    if led_date_count == 1:
        if hour == "20" and minute == "30":
            ser.write("LEDOFF\n".encode())
            led_date_count -= 1

    if water_date_count == 0:
        if hour == "8" and minute == "30":
            ser.write("WATERON\n".encode())
            led_date_count += 1

    if water_date_count == 1:
        if hour == "8" and minute == "35":
            ser.write("WATEROFF\n".encode())
            led_date_count -= 1

    time.sleep(2)   