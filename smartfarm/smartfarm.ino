/*
 * 수경 재배기의 코드입니다
 * 수경 재배기의 펌프, 조명, 화분 조명을 제어 하는 코드이다.
 * 라즈베리파이와의 시리얼 통신을 가지고 라즈베리파이에서
 */


#define LED1 10
#define LED2 11
#define PUMP 12
#define BIGLED 13

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BIGLED, OUTPUT);
  pinMode(PUMP, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(BIGLED, LOW);
  digitalWrite(PUMP, LOW);
  Serial.flush();
}


void loop() {

  Serial.flush();
  String ch = "";

  // 시리얼 통신으로 문자를 입력하기 위한 준비를 합니다.
  while (Serial.available() > 0)// 시리얼 입력이 있을때
  {
    ch += (char) Serial.read(); // 한번에 한문자를 읽으면
    delay(5); // 5밀리초 동안 대기하고 다음 문자를 읽을 준비를 합니다.
  }
  if (ch == "LEDON\n") {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    delay(500);
  } else if (ch == "LEDOFF\n") {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    delay(500);
  }else if (ch == "BIGON\n") {
    digitalWrite(BIGLED, HIGH);
    delay(500);
  } else if (ch == "BIGOFF\n") {
    digitalWrite(BIGLED, LOW);
    delay(500);
  }else if (ch == "WATERON\n") {
    digitalWrite(PUMP, HIGH);
    delay(500);
  } else if (ch == "WATEROFF\n") {
    digitalWrite(PUMP, LOW);
    delay(500);
  }

}
