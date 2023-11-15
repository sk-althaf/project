
#define SS_PIN 4                 // D2
#define RST_PIN 5                // D1
#include <SPI.h>
#include <MFRC522.h>
MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup()
{ 
  SPI.begin();
  mfrc522.PCD_Init();            // Initiate MFRC522
  Serial.begin(9600);
  
    pinMode(16, OUTPUT);         // D0
    pinMode(0, OUTPUT);          // D3
    pinMode(2, OUTPUT);          // D4

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
    
    
  

    SPI.begin();
    Serial.println("Stop !");
    digitalWrite(2, HIGH); 
    int z=0;
    while(z<12)
    {
      an();
      delay(250);
      z++;
    }
    SPI.end();
    digitalWrite(2, LOW);

}

void an()
 {
 
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
  return;
  }
  
  //Show UID on serial monitor
  Serial.print("Vehicle No :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  
}
