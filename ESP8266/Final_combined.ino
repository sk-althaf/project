#include <ESP8266WiFi.h>
#define SS_PIN 4                 // D2
#define RST_PIN 5                // D1
#include <SPI.h>
#include <MFRC522.h>
//#include <WiFi.h>
//#include <MySQL_Connection.h>
//#include <MySQL_Cursor.h>

WiFiClient client;

String MakerIFTTT_Key ;
String MakerIFTTT_Event;
char *append_str(char *here, String s) {  int i=0; while (*here++ = s[i]){i++;};return here-1;}
char *append_ul(char *here, unsigned long u) { char buf[20]; return append_str(here, ultoa(u, buf, 10));}
char post_rqst[256];char *p;char *content_length_here;char *json_start;int compi;

MFRC522 mfrc522(SS_PIN, RST_PIN); 


void setup()
{
  
  SPI.begin();
  mfrc522.PCD_Init();            // Initiate MFRC522
  Serial.begin(9600);


  WiFi.disconnect();
  delay(1000);
  Serial.println("START WIFI");
  WiFi.begin("POCO F1","87654321");
  
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print(".");
 }
 
  Serial.println();
  Serial.println("Connected");

  // Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
    pinMode(16, OUTPUT);         // D0
    pinMode(0, OUTPUT);          // D3
    pinMode(2, OUTPUT);          // D4

    digitalWrite(16,LOW);
    digitalWrite(0,LOW);
    digitalWrite(2,LOW);
}


void loop()
{
    SPI.begin();
    Serial.println("Go !");       
    digitalWrite(16,HIGH);
   
    int x=0;    
    while(x<12)
    {
      ani();
      delay(250);
      x++;
    }
   
    digitalWrite(16,LOW);
    SPI.end();
    
    SPI.begin();
    Serial.println("Reduce Speed !");
    digitalWrite(0,HIGH);       
   
    int y=0;    
    while(y<12)
    {
      ani();
      delay(250);
      y++;
    }
    
    digitalWrite(0,LOW);
    SPI.end();
    
  

    SPI.begin();
    Serial.println("Stop !");
    digitalWrite(2, HIGH); 
    
    int z=0;
    while(z<8)
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
  Serial.print("   FINED");
  Serial.println();
  content.toUpperCase();
  String phn;
   if (content.substring(1) == "63 DC 4F 0B") 
  {
    phn="919492910529";
  }
 
 else if (content.substring(1) == "2A 16 53 19") 
  {
    phn="919492910529";
  }
 else if (content.substring(1) == "43 7F 51 0B") 
  {
    phn="919492910529";
  }
  else if (content.substring(1) == "2B 44 C4 0C") 
  {
    phn="919492910529";
  }
  
 if (client.connect("maker.ifttt.com",80)) {
    //Nikhil    mY-XQS8hkaO88vGdXcTue_pCy6KaA-QFwk-gLsqDdvq
    //shahshi fXd_5xaYKKXuJQeoHomtUYDCqDw50PICe-KimxBaFr7           updated   oOdl0JQ2We7ByiVjixLvdUptJMWjFCW3zuF278HNm0c
    MakerIFTTT_Key ="oOdl0JQ2We7ByiVjixLvdUptJMWjFCW3zuF278HNm0c";//kJIp_hhokuhLNTCeFk3ba4NWxEcIOWcR8kbrbuB8u-1
    MakerIFTTT_Event ="FINED";
    p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");
    content_length_here = p;
    p = append_str(p, "NN\r\n");
    p = append_str(p, "\r\n");
    json_start = p;
    p = append_str(p, "{\"value1\":\"");
    p = append_str(p,content.substring(1));
    p = append_str(p, "\",\"value2\":\"");
    p = append_str(p,phn);
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, "");
    p = append_str(p, "\"}");

    compi= strlen(json_start);
    content_length_here[0] = '0' + (compi/10);
    content_length_here[1] = '0' + (compi%10);
    client.print(post_rqst);

  }

}
void ani()
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
  Serial.print("   NOT FINED");
 

  Serial.println();
  
  
}
