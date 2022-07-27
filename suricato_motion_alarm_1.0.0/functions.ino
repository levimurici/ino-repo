void setup_wifi(){
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID_WIFI);

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_WIFI, PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  { 
    digitalWrite(status_led, LOW);
    delay(500);
    Serial.print(".");
    digitalWrite(status_led, HIGH);
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(status_led, HIGH);
}

void callback(char *topic, byte *payload, unsigned int length) {
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
    output_request(topic_str, payload_str);
  }
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

void output_request(String topic_in , String payload_in)
{  
  Serial.println(topic_in);
  Serial.println(payload_in);
  if (topic_in == "device5/motion-request")  {
    if(payload_in == "true") {
//      motion_check();      
    }
  }
}

void motion_check()
{ 
  Serial.print("Valor do Sensor PIR: ");
  Serial.println(LeituraPIR);

  LeituraPIR = digitalRead(PIR);
  if (LeituraPIR == HIGH) {
    state_motion = "HIGH";
  } else {
      state_motion = "LOW";
    }
   
  delay(50);
  serialize_update();
  client.publish(post1, json_to_send);
  Serial.println("PIC501 Posted");
}
