/* Variáveis de interface e controle */
const int status_led = 0; //D3
const int status_led_gnd = 5; //D1

#define PIR 15 //
#define LED 13
int LeituraPIR = 0;

/* Controle de estados */
String state_motion;

/* Controle de estados e Json */
char json_to_send[256];
String MY_IP_ADDR, MY_MAC_ADDR;

unsigned long lastMillis = 0;
unsigned long previousMillis = 0;
const long interval = 5000;
