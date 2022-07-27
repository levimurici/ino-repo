/* Variáveis de interface e controle */
const int status_led = 0; //D3
const int status_led_gnd = 5; //D1

#define DHTPIN 12 //
#define DHTTYPE DHT22

int LeituraPIR = 0;

/* Controle de estados */
String state_temp;
String state_hum;

/* Controle de estados e Json */
char json_to_send[256];
String MY_IP_ADDR, MY_MAC_ADDR;

unsigned long lastMillis = 0;
unsigned long previousMillis = 0;
const long interval = 5000;
