#define TRIG 8
#define ECHO 9

void setup()
{
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop()
{
  long duration, distance;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn (ECHO, HIGH);
  distance = duration * 17 / 1000; 
  Serial.println(duration );
  Serial.print("  DIstance : ");
  Serial.print(distance);
  Serial.println(" Cm");
  delay(100);
  
  if(duration < 2100)
  {
    Serial.print('Replenish Water');
  }
/*NO WATER = 1700*/
  /*if(duration > 꽉참) 
  {
    //물 100%
  }else if(duration <)
  {
    
  }else if(duration < )
  {
    
  }else if(duration < )
  {
    
  }else 
  {
    
  }*/
}
