/* Variáveis de interface e controle */
const int status_led = 0; //D3
const int status_led_gnd = 4; //D1
const int relay_1 = 5;

/* Controle de estados */
String state_relay;

/* Controle de estados e Json */
char json_to_send[256];
String MY_IP_ADDR, MY_MAC_ADDR;

unsigned long lastMillis = 0;
unsigned long previousMillis = 0;
const long interval = 5000;
