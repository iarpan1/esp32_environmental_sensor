#include <WiFi.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ135_PIN 34
#define GAS_THRESHOLD 20

const char* ssid = "ProudNepal";
const char* password = "karki@123";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.println("ESP32 IP: " + WiFi.localIP().toString());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("GET /data") >= 0) {
      // Read sensors
      float temp = dht.readTemperature();
      float hum = dht.readHumidity();
      int mqValue = analogRead(MQ135_PIN);
      String gasStatus = mqValue > GAS_THRESHOLD ? "Harmful" : "Safe";

      // Build JSON
      String json = "{";
      json += "\"temperature\":" + String(temp,1) + ",";
      json += "\"humidity\":" + String(hum,1) + ",";
      json += "\"gas\":\"" + gasStatus + "\"";
      json += "}";

      // Send JSON with CORS header
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: application/json");
      client.println("Access-Control-Allow-Origin: *");  // <-- Enables fetch from file://
      client.println("Connection: close");
      client.println();
      client.println(json);
    } else {
      // Serve a simple page if accessed directly
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/plain");
      client.println("Connection: close");
      client.println();
      client.println("ESP32 is running. Use /data endpoint for JSON.");
    }

    delay(1);
    client.stop();
  }
}
