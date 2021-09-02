#define LED 10
#define BIGLED 11
#define PUMP 12

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BIGLED, OUTPUT);
  pinMode(PUMP, OUTPUT);
}

int ledst = 0;
int bigledst = 0;
int pumpst = 0;
char ch;

void loop() {
  if (Serial.available()) {
    ch = Serial.read();
    if (ch == "LED") {
      if (ledst == 1) {
        digitalWrite(LED, HIGH);
        delay(500);
        ledst = 0;
      } else if (ledst == 0) {
        digitalWrite(LED, LOW);
        delay(500);
        ledst = 1;
      }


    }
    if (ch == "BIGLED") {
      if (bigledst == 1) {
        digitalWrite(BIGLED, HIGH);
        delay(500);
        bigledst = 0;
      } else if (bigledst == 0) {
        digitalWrite(BIGLED, LOW);
        delay(500);
        bigledst = 1;
      }
    }
    if (ch == "PUMP") {
      if (pumpst == 1) {
        digitalWrite(PUMP, HIGH);
        delay(500);
        pumpst = 0;
      } else if (pumpst == 0) {
        digitalWrite(PUMP, LOW);
        delay(500);
        pumpst = 1;
      }
    }
  }


}
