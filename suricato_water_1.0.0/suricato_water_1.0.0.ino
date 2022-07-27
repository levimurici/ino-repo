#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "constantes.h"
#include "objetos.h"

WiFiClient espClient;
PubSubClient client(espClient);

Relay relay1(relay_1);
Led led(status_led);

void setup_wifi()
{

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID_WIFI);

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_WIFI, PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Cria uma ID
    String clientId = "device1/relay";
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

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  if (strstr(topic, sub1))
  {
    String topic_str = String(topic);
    String payload_str;
  
    for (int i = 0; i < length; i++) {
      char c = (char)payload[i];
      payload_str += c; 
    }
    Serial.println();
    output_relay(topic_str, payload_str);
  }
}

void output_relay(String topic_in , String payload_in)
{  
  // Relay1
  if (topic_in == sub1)  {
    if(payload_in == "true") {
      relay1.on();
      led.on();
      state_relay = "WATERING_ON";      
    }
    else {
      relay1.off();
      led.off();
      state_relay = "WATERING_OFF";
    }
  }
}

void serialize_update()
{

  StaticJsonDocument<192> doc_send;

  doc_send["name"] = "suricato12";
  
  JsonObject info = doc_send.createNestedObject("info");
  info["type"] = "Garden";
  info["place"] = "quintal";
  info["ipaddr"] = WiFi.localIP();
  
  JsonObject data = doc_send.createNestedObject("data");
  data["watering"] = state_relay;

  serializeJson(doc_send, json_to_send);
}

void setup()
{
  pinMode(relay_1, OUTPUT);
  pinMode(status_led, OUTPUT);

  relay1.off();

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, porta);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000)
  { 
    serialize_update();
    client.publish("outTopic3", json_to_send); 
  }
}
