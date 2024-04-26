#include <SPI.h>
#include <WiFiNINA.h>
#include <MFRC522.h>
#include <ArduinoJson.h>

// WIFI
char SSID[] = "Test2Connexion";
char PASS[] = "testdetest";
int status = WL_IDLE_STATUS;
WiFiClient client;

// QUERIES
IPAddress SERVER(192,168,107,199);

//RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {;};

  do {
    Serial.print("Connecting to SSID : ");
    Serial.println(SSID);

    status = WiFi.begin(SSID, PASS);

    delay(10000);
  } while (status != WL_CONNECTED);

  SPI.begin();
  rfid.PCD_Init();
  Serial.println("RFID listening...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  String data = "{\"rfid\": \"";
  for (byte i = 0; i < 4; i++) {
    data += rfid.uid.uidByte[i];
    Serial.print(rfid.uid.uidByte[i]);
  }
  data += "\"}";
  Serial.println();

  if (postQuery("/api/students/find", data)) {
    Serial.println("Agree");
  } else {
    Serial.println("Wrong");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

bool postQuery(String path, String data) {
  if (!client.connect(SERVER, 3001)) {
    Serial.println("Failed to connect to the API");
    return false;
  }

  Serial.println("Successfully connected to the API");
  client.print("POST ");
  client.print(path);
  client.println(" HTTP/1.1");
  client.println("Host: 192.168.107.199");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(data.length());
  client.println("Connection: close");
  client.println();
  client.println(data);
  Serial.println("Data successfully send");

  JsonDocument response;

  bool alreadyReceived = false;
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      if (c == '{') {
        deserializeJson(response, c);
      }
      Serial.print(c);
      alreadyReceived = true;
    } else if (alreadyReceived) {
      client.stop();
    }
  }

  client.stop();
  return response["status"];
}