import datetime

date = datetime.datetime.now()

hour_and_min = date.strftime("%H%M")

hour = hour_and_min[:2]
minute = hour_and_min[2:]

print(hour)
print(minute)