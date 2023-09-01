#include <WiFi.h>
#include <ESP32Servo.h>

const char* ssid = "username";
const char* password = "password";

const char* server = "api.thingspeak.com";
const int serverPort = 80;
const String writeAPIKey = "write_api_key_thingspeak";
const String readAPIKey = "read_api_key_thingspeak";
const int servoPin = 14;

WiFiClient client;
Servo myservo;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  myservo.attach(servoPin);
  myservo.write(0);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int field1Value = readThingSpeakStatus();
    if (field1Value == 1) {
      // Perform the servo action
      myservo.write(180);
      delay(5000);
      myservo.write(0);
    }
  }
  delay(5000);
}

int readThingSpeakStatus() {
  int field1Value = 0;

  if (client.connect(server, serverPort)) {
    String url = "/channels/2244783/feeds/last.json?api_key=" + readAPIKey;
    client.println("GET " + url + " HTTP/1.1");
    client.println("Host: " + String(server));
    client.println("Connection: close");
    client.println();
    delay(1000);

    String response = client.readString();
    Serial.println("ThingSpeak response: " + response);

    client.stop();

    // Parse the JSON response to extract field1 value
    if (response.indexOf("\"field1\":\"1\"") != -1) {
      field1Value = 1;
    }
  } else {
    Serial.println("Connection to ThingSpeak failed");
  }

  return field1Value;
}
