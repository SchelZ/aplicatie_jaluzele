#include <TinyMqtt.h>
#include <ESP32Servo.h>

const std::string topic="ser/mot";
const char *ssid     = "Jaluzele_Smart";
const char *password = "";

// IPAddress local_IP(192, 168, 249, 184);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 0, 0);

Servo servo1;
MqttBroker broker(1883);
MqttClient mqtt_a(&broker);


void onPublishA(const MqttClient*, const Topic& topic, const char* payload, size_t) { 
  Serial << "--> client A received " << topic.c_str() << ", " << payload << endl; 
  if (topic.c_str() == "up")
    servo1.write(180);
  else if (topic.c_str() == "down")
    servo1.write(0);

}

void setup()
{
  Serial.begin(9600);
  servo1.attach(13);


  delay(500);

  // if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    // Serial.println("STA Failed to configure");
  // }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to AC...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial << ".";
    delay(500);
  }

  Serial.print("Connected!  IP addr: ");
  Serial.println(WiFi.localIP());

  broker.begin();
  mqtt_a.setCallback(onPublishA);
  mqtt_a.subscribe(topic);
}

void loop() {
  broker.loop(); 
  mqtt_a.loop();
}
