#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define TRIG 8
#define ECHO 9
#define PUMP1 10
#define PUMP2 11


#define SQUARE_CAPACITY_BASE (L_LENGTH * H_HEIGHT * W_WIDTH)/1000000 // 사각형 수조 용량 계산식
#define L_LENGTH 50.0 // 사각형 수조 – 세로 (cm)
#define H_HEIGHT 100.0 // 사각형 수조 – 높이 (cm)
#define W_WIDTH 50.0 // 사각형 수조 – 가로 (cm)

#define DISTANCE_PLUS 10 // 초음파 센서의 측정 단위 (mm)
#define THRESHOLD_ALARM_1 10 // 최저수위값 알람 높이 (cm)
#define THRESHOLD_ALARM_2 100 // 최고수위값 알람 높이 (cm)

void setup()
{
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(PUMP1, OUTPUT);
  pinMode(PUMP2, OUTPUT);
}

void loop()
{

  if (Serial.available()) {
    String ch = Serial.readString();
    if (ch == "ON") {
      digitalWrite(PUMP1, HIGH);
      digitalWrite(PUMP2, HIGH);
    }
    if (ch == "OFF") {
      digitalWrite(PUMP1, LOW);
      digitalWrite(PUMP2, LOW);
    }
  }

  int h = dht.readHumidity();
  int t = dht.readTemperature();
  long hWaterCm;
  int liters;

  hWaterCm = read_height();
  if (check_alarm(hWaterCm) != 0) /* read again water height */
    hWaterCm = read_height();
  if (hWaterCm <= 0) {
    Serial.print("Amount of Water : 0");
    Serial.println("L");
  } else {
    liters = floor(SQUARE_CAPACITY_BASE * hWaterCm * 10); //사각형 수조
    Serial.print("Amount of Water : ");
    Serial.print(liters);
    Serial.println("L");

    switch (check_alarm(hWaterCm)) {
      case 1 : //full
        Serial.println("FULL");
        break;
      case 2 : //empty
        Serial.println("EMPTY");
        break;
      case 0: //no
        delay(100);
        break;

    }
  }
}




long read_height() {
  /*
    초음파 센서의 핑 설정 및 거리와 센티미터의 변수 설정,
  */
  long hWaterCm;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(20);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  float distance = pulseIn(ECHO, HIGH);
  distance = distance / 29.387 / 2;
  Serial.print("Sensor Real Distance : ");
  Serial.print(distance);
  Serial.println("cm");
  Serial.println("——————————");
  delay(20);
  hWaterCm = H_HEIGHT - distance + DISTANCE_PLUS;
  if (hWaterCm < 0)
    return 0; if (hWaterCm > H_HEIGHT)
    return H_HEIGHT; return hWaterCm;
}

int check_alarm(int hWaterCm) {
  if (hWaterCm >= THRESHOLD_ALARM_2) {
    return 1;
  }
  if (hWaterCm <= THRESHOLD_ALARM_1) {
    return 2;
  }
  else {
    return 0;
  }
}
