
#define SS_PIN 4  //D2
#define RST_PIN 5 //D1
#include <SPI.h>
#include <MFRC522.h>
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.



void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}



void loop() 
{
an();

}

void an(){
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    delay(500);
    an();
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    delay(500);
    an();
  }
  
  
  Serial.print("Vehicle No: ");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println(content.substring(1) );
  delay(500);

} 
