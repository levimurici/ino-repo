/* defines - wi-fi */
#define SSID_WIFI "Familia Murici"
#define PASSWORD "murici1020"
#define INTERVALO_DE_ENVIO 1000
//#define SERVER_IP "192.168.1.6:3000"

const char* mqtt_server = "192.168.1.101";
const int porta = 1883;

#define sub1 "device4/temp-request"
#define post1 "device4/temperature"

/* Variáveis de interface e controle */
const int status_led = 0; //D3
const int status_led_gnd = 5; //D1

#define DHTPIN 12 //
#define DHTTYPE DHT22

/* Controle de estados */
String state_temp;
String state_hum;

/* Controle de estados e Json */
char json_to_send[256];
String MY_IP_ADDR, MY_MAC_ADDR;

#define MSG_BUFFER_SIZE (50)
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;
