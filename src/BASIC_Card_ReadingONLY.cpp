//Libraries
#include <Arduino.h>
#include <SPI.h>//https://www.arduino.cc/en/reference/SPI
#include <MFRC522.h>//https://github.com/miguelbalboa/rfid

//Constants
#define SS_PIN 5
#define RST_PIN 4

//Parameters
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
//MFRC522::MIFARE_Key key; 

void setup() 
{
//for RFID
 Serial.begin(115200);
   SPI.begin();      // Initiate  SPI bus
   mfrc522.PCD_Init();   // Initiate MFRC522
   Serial.println("Approximate your card to the reader...");  

}

//CARD READING
int readc()
{
  int card;

// Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
while ( ! mfrc522.PICC_IsNewCardPresent()) 
 {
    //return card;
    //delay(50);
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return card;
  }
  
  byte buffer1[18];
  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return card;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return card;
  }
String jina = "";

  //PRINT Card #
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      jina += (char)buffer1[i];
    }    
  }
jina.trim();
card=jina.toInt(); 




  //Serial.print(" ");
  //Serial.println(F("\n**End Reading**\n"));
  //delay(1000); //change value if you want to read cards faster
   mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1(); 
return card;  
}

void loop() 
{
 
int KADI;

KADI = readc();

if (KADI>0)
{
Serial.print("Card tapped = ");
Serial.println(KADI);
delay(500);
}
}
