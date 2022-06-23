/* defines - wi-fi */
#define SSID_WIFI "IPQ"
#define PASSWORD "inovacao"
#define INTERVALO_DE_ENVIO 1000
#define SERVER_IP "192.168.101.65:3000"
const char* mqtt_server = "192.168.101.28";
const int porta = 1883;

#define sub1 "device1/relay"

/* Variáveis de api e wi-fi */
unsigned long last_connection_time;

/* Variáveis de interface e controle */
const int relay_1 = 12;
const int status_led = 13;

/* Controle de estados e Json */
char json_to_send[256];
String state_relay1;
String MY_IP_ADDR, MY_MAC_ADDR;

#define MSG_BUFFER_SIZE (50)
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;
