#include <ESP8266WiFi.h>

#define AP_SSID     "Internet of Home"
#define AP_PASSWORD "raspberrypi"

#define SERVER_ADDRESS     "192.168.1.106"
#define SERVER_PORT        80

int data=0;

void sendStatus(int);
void wifiConnect();

void setup() {
  
  Serial.begin(115200);  
  wifiConnect();
  pinMode(2, INPUT);

}

void loop() {
  
  data = digitalRead(2);
  sendStatus(data);
  delay(2000);

}

void wifiConnect() {
    Serial.print("Connecting to AP");
    WiFi.begin(AP_SSID, AP_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");  
}

void sendStatus(int s) {  
  WiFiClient client;
   
  while(!client.connect(SERVER_ADDRESS, SERVER_PORT)) {
    Serial.println("connection failed");
    wifiConnect(); 
  }

  Serial.print("GET req for data to URL: ");
  //Serial.println("GET /updateStatus.php?shop=karuturi&status="+String(s)+" HTTP/1.1");
  client.println("GET /updateStatus.php?shop=karuturi&status="+String(s)+" HTTP/1.1");
  client.print("Host: ");
  client.println(SERVER_ADDRESS);
  client.println("Connection: close");
  client.println();
  delay(100);
  while(client.available()){
    String line = client.readStringUntil('\r');
    //Serial.print(line);
  }
  
  Serial.println("Connection closed");
} 
