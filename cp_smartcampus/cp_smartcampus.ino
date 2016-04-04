// TODO: 1. hourly data send
//       2. IamAliveMessage
//       3. Deep Sleep Mode
//       4. Encryption 

#include <ESP8266WiFi.h>

#define AP_SSID     "BITS-HYB"
#define AP_PASSWORD "cisco"

#define SERVER_ADDRESS     "172.16.79.14"
#define SERVER_PORT        80

int flag = 1;
int data = 0;
int areYouSure = 0; // value from the sensor will be taken multiple time and sent  
int statusToSend=0;

void sendStatus(int);
void wifiConnect();
void ISR();

void setup() {
  
  Serial.begin(115200);  
  wifiConnect();
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), ISR, CHANGE);
  data = digitalRead(2);
}

void loop() {

  if (flag){
    delay(100); // to avoid debouncing 
    areYouSure=0; 
    for (int i=0;i<5;i++){
      data = digitalRead(2);
      delay(300);
      areYouSure+=data;
    }
    if (areYouSure > 3){
      statusToSend = 0;
      flag= 0;
      sendStatus(statusToSend); // 1-open 0-closed
    }
    else if (areYouSure < 2){
      statusToSend = 1;
      flag= 0;
      sendStatus(statusToSend); // 1-open 0-closed
    }
    else {
      flag= 1;  
    }
  }
  
  delay(1000);
}

void ISR() {
  Serial.println("ISR Here...");
  flag = 1; 
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
  Serial.println("GET /updateStatus.php?shop=karuturi&status="+String(s)+" HTTP/1.1");
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
