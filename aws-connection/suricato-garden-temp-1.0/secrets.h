#include <pgmspace.h>
 
#define SECRET
 
#define SSID_WIFI "Familia Murici"
#define PASSWORD "murici1020"

#define AWS_IOT_SUBSCRIBE_TOPIC "suricato11-garden-temp/sub"
#define AWS_IOT_PUBLISH_TOPIC "suricato11-garden-temp/pub"
 
#define THINGNAME "suricato11-garden-temp"
 
int8_t TIME_ZONE = -3; //BAHIA(BR): -3 UTC
 
const char MQTT_HOST[] = "a267k5rhrr3q3s-ats.iot.us-west-1.amazonaws.com";
 
 
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
 
// Copy contents from XXXXXXXX-certificate.pem.crt here ▼
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAIeAAusDGFuQZUuoht22YtDRk5HfMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjA2MjUxNTEx
MTJaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDQa6u7uGkGZb5stC2R
E4KpGZLPK+53xL/l18gBFZLhB20GlDxISLiUG4nsXJskrl71G0e6BBjca41sRGsG
B/r2g5nHKxcXgLHR4Pp+VDDwGFjf2EVCaBfIkveslLJZV+/wd0FWsOhofdkqo5b8
LyARA7IqknwsdPKDb9CYvwCObrdDHOyMu4CLjTICfKEIb88fZa9utiJHr2WKt5L8
Z7ijyqCIxIOb6gRmsMS/0HDAvTB5lRJ31SKaXZ8RRTHrjUIztHwzkOxwJLa0NTb0
7zaxUj0DkM4MB8h0RCDgTHoY+CIrY4mqQymTDJAwmRM+f4jj4Xz/EYk2Fo6dAdUf
zFV/AgMBAAGjYDBeMB8GA1UdIwQYMBaAFM7zOy76kCnSK2hlafbhKuP9NOAbMB0G
A1UdDgQWBBQA35xb/g1D0v4BdUp2aGT9X411jjAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAE1fYDn6FNq2qR3mBpvs1s7s7
ZTaybTh2nV4F/D7YzdoZFpgBFf5rUNukMTkOPL+8/H/D+DqELkC+MnT/m+Da0Kd6
QJXIsW5QQ38lM7Cb5jaXwlLHmL/E8qWsCMqNXaiEoZj5EO2qWB+I0Oou67Xtnwnz
GpwZCwuSVohpBHjoGf4ZZrq/8/tG9QmQopWHctmXFOktYRsSX68xVcSvngGe4lDV
FAcloO4muSqQhgdacax4HcjExJy7v+QN4GxyKZKUvPaj4/WCBt/npbFwxmZmUEpx
RxASpBLVWGhbBMzqBfprav9SYSD4L/wNdyQhgB/9+1kkzZIZLusSdsyFMoXhKg==
-----END CERTIFICATE----- 
)KEY";
 
 
// Copy contents from  XXXXXXXX-private.pem.key here ▼
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEA0Guru7hpBmW+bLQtkROCqRmSzyvud8S/5dfIARWS4QdtBpQ8
SEi4lBuJ7FybJK5e9RtHugQY3GuNbERrBgf69oOZxysXF4Cx0eD6flQw8BhY39hF
QmgXyJL3rJSyWVfv8HdBVrDoaH3ZKqOW/C8gEQOyKpJ8LHTyg2/QmL8Ajm63Qxzs
jLuAi40yAnyhCG/PH2WvbrYiR69lireS/Ge4o8qgiMSDm+oEZrDEv9BwwL0weZUS
d9Uiml2fEUUx641CM7R8M5DscCS2tDU29O82sVI9A5DODAfIdEQg4Ex6GPgiK2OJ
qkMpkwyQMJkTPn+I4+F8/xGJNhaOnQHVH8xVfwIDAQABAoIBAQC9pDru5C0sFQfg
AVI033vUQeDDgUXK1MuHZ4Ak/GxZNViO0/LGEuVgXm5xExJXnhHpFJl/OJsmdPaJ
vPdk1X4VMEmMYDjyubcTMZK7v/+Hd5/mjfL3KZ/6cT/LWMGvacR5GQnqx62w5lHj
6lZHwNl8odBLzF4QVZkU33j+g00OSyn+Bqoq/zAB+t2dI1F6bpYuRcqTVqNeHjOf
WClPYFBftfo+jgfXi5/kuFAVhGlEjHSdcewL4ZF2kYkY+/Me/67XSSCTlNiXvLau
KkiKvi5R4Rk/on3f1l8s5uU+d+5ZpSgbT6YoA6APzhyri156Ck5qUy66KgU853Jm
nPfaQCoBAoGBAPlfSATIsiJwiNms9mYGEQJYnh+jf73lmKdT6Brf7CXNFbRN3GuG
4jNWU+jdjDaX2y7GEruCUjqjNV+EnFl9/7+LshB0dekxw5f5UHzJyLAVo1kxPaEa
eh8TmDpzFXBqUJ9HCZVnE40KN9xeCJ+DxWM8v1k4hWrZtIJDmaziKUNPAoGBANX1
waM1Q0sBWYUVkmTrJ0wjLp/T3KgoYlxpue7FjRcQGkNxwLVahyHW54TvKRnE6tP7
MPjvRV+EKSSCim7x5wUiK85T7dUZm8lN4a0YpQKW8jmcFGfMlL2gY0moXhD01p+r
lPNnwTH8GNsjpnU3ogBV3l/jkJX8TYN2ZVj6bP7RAoGBAK3DCMncltOMmq8i6GZa
38tEuJnPMZm+vEoMG3VuhnwolXEXt/ls+X1QMBPZHHSGCAJlnnPt8SJOy0gNfWyW
cXik/KSeofKl7GafIMhzSlX4HeRufUUez+2Ll81Sl6PHUPpLY5ApTORANIBnPZb5
GLd3gtXGnqC/phoGxLREuv/dAoGBAKr0Lb/F8vqfHXPkhI/2A/QluD8j/I6vlcfZ
AiLx3YWr7BAvd5ZvusEjAOGKZgCdAjRV5A9Cvt9OrcDqPMngpoHHh9DX5pP6Xis9
+y9fHZkwGmJFf1hgcggBetODn4VU25fAdMb3A7p4fzO5DGtkBCDYe1GKdiAg854y
n0+06BnBAoGAEUHqJR3wk9RELSwX4dDJGwThpWHjG/REpIrCnOk4KLue2sKAW2+w
8M9BPlu2WzuMSyWbb5O+fchZkxjY7CdikqwBFXoSO9kd9ZVwj8r/x9xrm4ymkVYm
uO0Hn0A4m8xg/Z9GW/zX5UW3ZsQmeCorGU8CCpZltTiGdquLjp/KV1g=
-----END RSA PRIVATE KEY----- 
)KEY";
