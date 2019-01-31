#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

static const char* hotspotSSID = "";
static const char* hotspotPassword = "";
static const char* mqttServer = "";

const int buttonPin = 2;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(hotspotSSID);

  WiFi.begin(hotspotSSID, hotspotPassword);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("#");
    delay(500);
  }

  Serial.println("Connection to hotpot established!");
  Serial.println("Local IP address: ");
  Serial.println(WiFi.localIP());

  // Set mqtt server (probably running on raspi which is also the hotspot)
  client.setServer(mqttServer, 1883);

  Serial.print("Connecting to mqtt server");
  Serial.println(mqttServer);
  while(!client.connect("CLIENT-NAME")) {
    Serial.print("#");
    delay(1000);
  }

  Serial.println("MQTT client connected to server!");
  // Subscribe
  client.subscribe("TOPICNAME/ON/RASPI");

  pinMode(buttonPin, INPUT);
}

void loop() {
  if (client.connected()) {
    client.loop();
    // TODO: Add the button handling.
    // TODO: set callback for mqttClient: client.setCallback(callback);
    // TODO: Actually publish stuff: client.publish("TOPICNAME", MESSAGE-AS-STRING);
  }
}
