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

  String topic_str = String(topic);
  String payload_str;

  for (int i = 0; i < length; i++) {
    char c = (char)payload[i];
    payload_str += c; 
  }
    Serial.println();
    output_request(topic_str, payload_str);
}

void serialize_update()
{
  StaticJsonDocument<192> doc_send;

  doc_send["name"] = "suricato20";
  
  JsonObject info = doc_send.createNestedObject("info");
  info["type"] = "Motion";
  info["place"] = "quarto";
  info["ipaddr"] = WiFi.localIP();
  
  JsonObject data = doc_send.createNestedObject("data");
  data["status"] = state_motion;
  
  serializeJson(doc_send, json_to_send);
}

void motion_check()
{ 
  Serial.print("Valor do Sensor PIR: ");
  Serial.println(LeituraPIR);

  LeituraPIR = digitalRead(PIR);
  if (LeituraPIR == HIGH) {
    state_motion = "HIGH";
    delay(500);
    serialize_update();
    client.publish(AWS_IOT_PUBLISH_TOPIC, json_to_send);
    Serial.println("Suricato20-Motion Posted");
    delay(1000);
  } else {
      state_motion = "LOW";
      delay(500);
    }
}

void output_request(String topic_in , String payload_in)
{  
  Serial.println(topic_in);
  Serial.println(payload_in);
  if (topic_in == "suricato20/sub")  {
    if(payload_in == "true") {
      Serial.println("I'll do something");    
    }
  }
}
