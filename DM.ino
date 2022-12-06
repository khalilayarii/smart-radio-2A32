int Pir_Sensor = 0;

void setup() 
{
 pinMode(8,OUTPUT);
 pinMode(7,INPUT);
 Serial.begin(9600);
  digitalWrite(8,LOW );
  
}

void loop() 
{
  //Pir_Sensor =Serial.println(digitalRead(2));
  Pir_Sensor =digitalRead(7);

  if(Pir_Sensor == HIGH)
  {
    Serial.write("1");
    digitalWrite(8,HIGH );
     delay(5000);
     digitalWrite(8,LOW );
  }
 else
 {    Serial.write("0");
digitalWrite(8,LOW );
  
  }


 

  
}
