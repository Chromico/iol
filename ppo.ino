
#include "ESP8266WiFi.h"

int led = 2;


void setup(){

  Serial.begin(115200);

  //reset the wifi connection, solves bugs
  WiFi.disconnect(true);
  delay(1000);

  pinMode(led, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  const char* ssid = "server101";
  const char* pass = "server101";
  const uint16_t serverPort = 80;
  const char* serverIP = "192.168.4.1";

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
 
  }

  Serial.println("WiFi Connected");
  delay(10);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.gatewayIP());
  Serial.println("Connected to WiFi");
}

void loop(){


  const uint16_t serverPort = 80;
  const char* serverIP = "192.168.4.1";

  WiFiClient client;

  //connect to other WEMOS
  if (!client.connect(serverIP, serverPort)){
    delay(1);
  }
  //Write data to other wemos
  delay(2000);
  
  String micro = client.readStringUntil('\r');
  
Serial.println(micro);


  //End connection
  client.stop();

  delay(100);
}
