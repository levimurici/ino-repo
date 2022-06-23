/* defines - wi-fi */
#define SSID_WIFI "Familia Murici"
#define PASSWORD "murici1020"
#define INTERVALO_DE_ENVIO 1000
//#define SERVER_IP "192.168.1.6:3000"
const char* mqtt_server = "192.168.1.16";
const int porta = 1883;

//#define sub1 "device1/alarm1"
#define sub1 "device1/relay"
#define post1 "device1/alarm"

/* Variáveis de api e wi-fi */
unsigned long last_connection_time;

/* Variáveis de interface e controle */
const int relay_1 = 15; //D8
const int encoder = 12; //D6
const int status_led = 15; //D7
const int buzzer = 13;

/* Controle de estados */
String state_alarm1;
String state_relay1;

/* Controle de estados e Json */
char json_to_send[256];
String MY_IP_ADDR, MY_MAC_ADDR;

#define MSG_BUFFER_SIZE (50)
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;
