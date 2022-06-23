#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DHT.h"; 

#include "constantes.h"

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHT22);

void callback(char *topic, byte *payload, unsigned int length);
void setup_wifi();
void serialize_update();
void temp_json();

void setup() {
  Serial.begin(115200);
  pinMode(status_led, OUTPUT);
  pinMode(status_led_gnd, OUTPUT);
  digitalWrite(status_led_gnd, LOW);
  
  setup_wifi();
  client.setServer(mqtt_server, porta);
  client.setCallback(callback);

  dht.begin();
  Serial.println("Setup Concluído");
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Cria uma ID
    String clientId = "ESP-SuricatoTemp";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      // Colhe informações
      Serial.println(sub1);
      client.subscribe(sub1);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}
