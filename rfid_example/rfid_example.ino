#include <SPI.h> // SPI
#include <MFRC522.h> // RFID

#define SS_PIN 10
#define RST_PIN 9
    
// Déclaration 
MFRC522 rfid(SS_PIN, RST_PIN); 

// Tableau contentent l'ID
byte nuidPICC[4];

void setup() 
{ 
  // Init RS232
  Serial.begin(9600);

  // Init SPI bus
  SPI.begin(); 

  // Init MFRC522 
  rfid.PCD_Init(); 
}
 
void loop() 
{
  // Initialisé la boucle si aucun badge n'est présent 
  if ( !rfid.PICC_IsNewCardPresent())
    return;

  // Vérifier la présence d'un nouveau badge 
  if ( !rfid.PICC_ReadCardSerial())
    return;

  // Enregistrer l'ID du badge (4 octets) 
  for (byte i = 0; i < 4; i++) 
  {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  
  // Affichage de l'ID 
  Serial.println("Un badge est détecté");
  Serial.println(" L'UID du tag est:");
  for (byte i = 0; i < 4; i++) 
  {
    Serial.print(nuidPICC[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Re-Init RFID
  rfid.PICC_HaltA(); // Halt PICC
  rfid.PCD_StopCrypto1(); // Stop encryption on PCD
}
/*
#include <SPI.h>
#include <WiFiNINA.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

char ssid[] = "Test2Connexion";
char pass[] = "testdetest";
int status = WL_IDLE_STATUS;
byte nuidPICC[4];

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.println("You're connected to the network");
  Serial.println(WiFi.localIP());

  //Bridge.begin();
  SPI.begin();  
  rfid.PCD_Init(); 
  Serial.println("RFID listening");
}

void loop() {
  // Initialisé la boucle si aucun badge n'est présent 
  if ( !rfid.PICC_IsNewCardPresent())
    return;

  // Vérifier la présence d'un nouveau badge 
  if ( !rfid.PICC_ReadCardSerial())
    return;

  String data = "{\"rfid\": \"";
  for (byte i = 0; i < 4; i++) 
  {
    data += rfid.uid.uidByte[i];
    Serial.print(rfid.uid.uidByte[i]);
  }
  Serial.println();
  data += "\"}";

  // Re-Init RFID
  rfid.PICC_HaltA(); // Halt PICC
  rfid.PCD_StopCrypto1(); // Stop encryption on PCD
}
*/
/*
#include <SPI.h>
#include <WiFi.h>
#include <MFRC522.h>
//#include <Bridge.h>
//#include <BridgeHttpClient.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
 
char ssid[] = "Test2Connexion";    // your network SSID (name)
char pass[] = "testdetest"; // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;

void setup() 
{ 
  Serial.begin(9600);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // print your WiFi shield's IP address:
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  //SPI.begin(); 
  //rfid.PCD_Init(); 
}
 
void loop() 
{
  if ( !rfid.PICC_IsNewCardPresent())
    return;
  if ( !rfid.PICC_ReadCardSerial())
    return;

  Serial.println("OK");

  String data = "{\"rfid\": \"";
  for (byte i = 0; i < 4; i++) 
  {
    data += rfid.uid.uidByte[i];
    Serial.print(rfid.uid.uidByte[i]);
  }
  Serial.println();
  data += "\"}";

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
*/

/*
BridgeHttpClient client;

init
//Bridge.begin();

loop
client.addHeader("Accept: application/json");
client.addHeader("Content-Type: application/json");
client.enableInsecure();
client.postAsync("http://10.44.19.149:3000/api/students/find", data);
*/