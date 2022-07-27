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

  doc_send["name"] = "suricato11";
  
  JsonObject info = doc_send.createNestedObject("info");
  info["type"] = "Garden";
  info["place"] = "quintal";
  info["ipaddr"] = WiFi.localIP();
  
  JsonObject data = doc_send.createNestedObject("data");
  data["temperature"] = state_temp;
  data["humidity"] = state_hum;
  data["soil"] = "data";
  
  serializeJson(doc_send, json_to_send);
}

void temp_check()
{ 
  float real_temp = dht.readTemperature() - 1;
  float real_hum = dht.readHumidity();
  state_temp = String(real_temp, 1);
  state_hum = String(real_hum, 1);

  Serial.print(state_temp);
  Serial.print("\t");
  Serial.print(state_hum);
  Serial.print("\t");  
  delay(50);
}


void output_request(String topic_in , String payload_in)
{  
  Serial.println(topic_in);
  Serial.println(payload_in);
  temp_check();
  serialize_update();
  client.publish(AWS_IOT_PUBLISH_TOPIC, json_to_send);
  Serial.println("Suricato11-garden-temp Posted");
}
