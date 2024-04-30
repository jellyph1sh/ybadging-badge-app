#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "Test2Connexion";
char pass[] = "testdetest";

int status = WL_IDLE_STATUS;

IPAddress server(192,168,107,199);

WiFiClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);

    delay(10000);
  }

  Serial.println("\nStarting connection to server...");
  if (client.connect(server, 3000)) {
    Serial.println("Connected to API");
    client.println("POST /api/students/find HTTP/1.1");
    client.println("Host: 192.168.107.199");
    client.println("Content-Type: application/json");
    client.println("Content-Length: 16");
    client.println("Connection: close");

    client.println();
    client.println("{\"rfid\": \"test\"}");
  } else {
    Serial.println("Can't connect to API");
  }
}

void loop() {
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
}
