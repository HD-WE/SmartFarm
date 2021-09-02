void setup() 
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() 
{
  if(Serial.available())
  {
    String str = Serial.readString();

    if(str == "ON")
    {
      digitalWrite(13,HIGH);
      Serial.println("LED on");
    }

    else if(str == "OFF")
    {
      digitalWrite(13,LOW);
      Serial.prinln("LED off");
    }
  }

}