

void setup()
{
  pinMode(16, OUTPUT);      //d0
  pinMode(0, OUTPUT);       //d3
  pinMode(2, OUTPUT);       //d4
  
  Serial.begin(9600);
  
  digitalWrite(16,LOW);
  digitalWrite(0,LOW);
  digitalWrite(2,LOW);

}


void loop()
{

    Serial.println("Go !");
    digitalWrite(16,HIGH);
    delay(3000);
    digitalWrite(16,LOW);
    
    Serial.println("Reduce Speed !");
    digitalWrite(0,HIGH);
    delay(3000);
    digitalWrite(0,LOW);
    
    Serial.println("STOP!");
    digitalWrite(2,HIGH);
    delay(3000);
    digitalWrite(2,LOW);

}
