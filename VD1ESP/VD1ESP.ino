#include <SocketIoClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <stdio.h>
unsigned long int previousMillis;
unsigned long int interval = 1000;
// tên wifi và password nơi mà ESP cài đặt (ví dụ: nhà bạn)
const char* ssid = "Phong Dep SG 01..05";
const char* password = "88888888";

// host và post của SocketIO Server
char host[] = "192.168.0.102";
int port = 80;
int i,val;
char dis[5];
//char domain[] = "fast-anchorage-66763.herokuapp.com";
// char host[] = "hieuwebsite.herokuapp.com";

// Khởi tạo socket
SocketIoClient socket;

ESP8266WiFiMulti WiFiMulti;
// trên module ESP8266, chân của LED là 16
const int LED = 16;
void setupNetwork() {
    //Kết nối vào mạng Wifi
    WiFiMulti.addAP(ssid, password);
    //WiFi.disconnect();
    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(500);
        Serial.print('.');
    }
    
    Serial.println("Wifi connected!");
    Serial.println(F("Di chi IP cua ESP8266 (Socket Client ESP8266): "));
    Serial.println(WiFi.localIP());
    
    // Kết nối đến SocketIO server
//    socket.begin(domain);
    socket.begin(host, port);
}
void choptatLed(const char load[8],size_t length){
  digitalWrite(16,!digitalRead(16));
}

void setup() {
  pinMode(16, OUTPUT); // Cài đặt chân LED là chân đầu ra tín hiệu
    // Bắt đầu kết nối serial với tốc độ baud là 115200.
    // Khi mở serial monitor thì phải set đúng tốc độ baud.
    Serial.begin(115200);
    setupNetwork();
    socket.emit("customEvent","50");
    socket.on("message",choptatLed );
}

void loop() {
    socket.loop();
   if (millis() - previousMillis > 2000) {
       previousMillis = millis();
    };
}
