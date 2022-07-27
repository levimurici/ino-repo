void NTPConnect(void)
{
  Serial.print("Setting time using SNTP");
  configTime(TIME_ZONE * 3600, 0 * 3600, "pool.ntp.org", "time.nist.gov");
  now = time(nullptr);
  while (now < nowish)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("done!");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}

void connectAWS(){
  delay(3000);
  // We start by connecting to a WiFi network

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_WIFI, PASSWORD);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID_WIFI);

  while (WiFi.status() != WL_CONNECTED)
  { 
    digitalWrite(status_led, LOW);
    delay(1000);
    Serial.print(".");
    digitalWrite(status_led, HIGH);
  }

  NTPConnect();

  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);
 
  client.setServer(MQTT_HOST, 8883);
  client.setCallback(messageReceived);
 
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(1000);
  }
 
  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  Serial.println("AWS IoT Connected!");
  
  digitalWrite(status_led, HIGH);
}

void messageReceived(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  if (strstr(topic, AWS_IOT_SUBSCRIBE_TOPIC)){
    String topic_str = String(topic);
    String payload_str;
  
    for (int i = 0; i < length; i++) {
      char c = (char)payload[i];
      payload_str += c; 
    }
      Serial.println();
      output_request(topic_str, payload_str);
  }
}

void serialize_update()
{
  StaticJsonDocument<192> doc_send;

  doc_send["name"] = "suricato12";
  
  JsonObject info = doc_send.createNestedObject("info");
  info["type"] = "Watering";
  info["place"] = "quintal";
  info["ipaddr"] = WiFi.localIP();
  
  JsonObject data = doc_send.createNestedObject("data");
  data["state"] = state_relay;
  
  serializeJson(doc_send, json_to_send);
}

void water_check(String topic_in , String payload_in)
{ 
  // Relay1
  if (topic_in == AWS_IOT_SUBSCRIBE_TOPIC)  {
    if(payload_in == "true") {
      relay1.on();
      led.on();
      state_relay = "RELAY_ON";      
    }
    else {
      relay1.off();
      led.off();
      state_relay = "RELAY_OFF";
    }
  }
}


void output_request(String topic_in , String payload_in)
{  
  Serial.println(topic_in);
  Serial.println(payload_in);
  water_check(topic_in, payload_in);
  serialize_update();
  client.publish(AWS_IOT_PUBLISH_TOPIC, json_to_send);
  Serial.println("Suricato12-garden-watering Posted");
}
