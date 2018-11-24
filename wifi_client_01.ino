/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Sends and receives message from the server in every 2 seconds
 *  Communicates: wifi_server_01.ino
 */ 

#include <ESP8266WiFi.h>

byte led = 2;
char ssid[] = "tecknologg";           // SSID of your home WiFi
char pass[] = "101$Poop";            // password of your home WiFi

unsigned long askTimer = 0;

IPAddress server(192,168,0,80);       // IP of server
WiFiClient client;

void setup() {
  Serial.begin(115200);               // only for debug
  WiFi.begin(ssid, pass);             // connect to WiFi
  while (WiFi.status() != WL_CONNECTED) {  // do this when its not connected yet
    Serial.print(".");
    delay(500);
  }

  pinMode(led, OUTPUT);
}

void loop () {
  client.connect(server, 80);   // Connect to the server
  digitalWrite(led, LOW);    // to show the communication only (inverted logic)
  Serial.println(".");
  client.println("Hello server! Are you sleeping?\r");  // talk to server
  String answer = client.readStringUntil('\r');   // receive the message from the sever
  Serial.println("from server: " + answer);   // print the server's message
  client.flush();
  digitalWrite(led, HIGH);
  delay(2000);                  // after 2 seconds client will talk to the server
}
