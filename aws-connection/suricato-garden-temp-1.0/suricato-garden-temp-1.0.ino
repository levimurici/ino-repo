#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>

#include "DHT.h"; 
#include "constantes.h"
#include "secrets.h"

WiFiClientSecure net;
 
BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

PubSubClient client(net);
DHT dht(DHTPIN, DHT22);

time_t now;
time_t nowish = 1510592825;

void NTPConnect();
void messageReceived(char *topic, byte *payload, unsigned int length);
void connectAWS();
void serialize_update();
void temp_check();


void setup() {
  Serial.begin(115200);
  pinMode(status_led, OUTPUT);
  pinMode(status_led_gnd, OUTPUT);
  digitalWrite(status_led_gnd, LOW);

  connectAWS();
  dht.begin();
  Serial.println("Setup Concluído");
}

void loop() {
  if (!client.connected())
  {
    connectAWS();
  }
//  temp_check();
  client.loop();
}
