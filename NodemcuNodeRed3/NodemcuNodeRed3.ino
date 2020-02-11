#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
#define LED 2 // pin no.2
 
//Enter your wifi credentials
const char* ssid = "iambatman";
const char* password =  "12345678";
 
//Enter your mqtt server configurations
const char* mqttServer = "tailor.cloudmqtt.com";    //Enter Your mqttServer address
const int mqttPort = 13534;       //Port number
const char* mqttUser = "whzdnyzv";
const char* mqttPassword = "kAbninqGe4us";
 
WiFiClient espClient3;
PubSubClient client(espClient3);
 
void setup() {
  delay(10);
  pinMode(LED,OUTPUT); // defines the output for the pin
  digitalWrite(LED,HIGH);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(MQTTcallback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.println(client.state());  //If you get state 5: mismatch in configuration
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("esp/test");
 
}
 
void MQTTcallback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
 
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];  //Conver *byte to String
  }
   Serial.print(message);
  if(message == "#on3") {digitalWrite(LED,LOW);}   //LED on  
  if(message == "#off3") {digitalWrite(LED,HIGH);} //LED off
 
  Serial.println();
  Serial.println("-----------------------");  
}
 
void loop() {
  client.loop();
}
