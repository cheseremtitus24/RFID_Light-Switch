/*
Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *

*/



#include <SPI.h>
#include <MFRC522.h>
#define RelayInputPin 4
#define SS_PIN 10
#define RST_PIN 9

 
MFRC522 mfrc522 ( SS_PIN, RST_PIN ) ;
String readid;
String card1="cc40cc73";                //Change this value to the UID of your card.
 


	
void setup( ) 
{
	
 pinMode(RelayInputPin,OUTPUT);
 Serial.begin(9600);
 SPI.begin();
 mfrc522.PCD_Init();
 digitalWrite(RelayInputPin,LOW); //initially lights are off
}

String temp(byte *buffer, byte bufferSize)//function to store card uid as a string datatype.
{
  readid="";
  for(byte i = 0;i<bufferSize; i++)
  {
    readid=readid+String(buffer[i], HEX);
  }
	return readid;
}
void loop( ) 
{
	unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  
	
 if(!mfrc522.PICC_IsNewCardPresent())
 {
  return;
 }
 if(!mfrc522.PICC_ReadCardSerial()) 
 {
  return;
 }
 //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));  // Display card details in serial Monitor.
	
 String ruid = temp(mfrc522.uid.uidByte, mfrc522.uid.size);
	Serial.println(ruid);
	static bool status = false;
 if(ruid==card1)
	 { 
		if (!status){
			Serial.println("lights are being turned on...");
          digitalWrite(RelayInputPin,HIGH);
			status = true;
			delay(1000);
		}
		else
		{
			Serial.println("lights are being turned off as no one is around...");
          digitalWrite(RelayInputPin,LOW);
			status = false;
			delay(1000);
		}
  
 
		
 }
	/*
 else if (ruid != card1)
 {
  Serial.println("lights are being turned off as no one is around...");
  digitalWrite(RelayInputPin,LOW);
 }
	 */
	
	else
	{
		return;
	}
}
