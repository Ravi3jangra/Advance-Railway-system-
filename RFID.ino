
 /* Typical pin layout used:
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
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
// byte accessUID1[4] = {0x , 0x , 0x  , 0x};
// byte accessUID2[4] = {0x , 0x , 0x  , 0x};
// byte accessUID3[4] = {0x , 0x , 0x  , 0x};F3 3D B7 1C
byte accessUID1[4] = { 0xF3, 0x96, 0x46, 0xF7 };
byte accessUID2[4] = { 0xF3, 0x47, 0xBD, 0x24 };
byte accessUID3[4] = { 0xF3, 0x3D, 0xB7, 0x1C };
void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	if(mfrc522.uid.uidByte[0] == accessUID1[0] && mfrc522.uid.uidByte[1] == accessUID1[1] && mfrc522.uid.uidByte[2] == accessUID1[2] && mfrc522.uid.uidByte[3] == accessUID1[3]  )
  {Serial.println ("Train 1");}
  	else if(mfrc522.uid.uidByte[0] == accessUID2[0] && mfrc522.uid.uidByte[1] == accessUID2[1] && mfrc522.uid.uidByte[2] == accessUID2[2] && mfrc522.uid.uidByte[3] == accessUID2[3]  )
  {Serial.println ("Train 2");}
  	else if(mfrc522.uid.uidByte[0] == accessUID3[0] && mfrc522.uid.uidByte[1] == accessUID3[1] && mfrc522.uid.uidByte[2] == accessUID3[2] && mfrc522.uid.uidByte[3] == accessUID3[3] )
  {Serial.println ("Train 3");}
  else{ Serial.println ("NO DATA");}
  mfrc522.PICC_HaltA();
}
