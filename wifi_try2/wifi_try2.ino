#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "iambatman";
const char* password =  "12345678";
const char* mqttServer = "tailor.cloudmqtt.com";
const int mqttPort = 13534;
const char* mqttUser = "whzdnyzv";
const char* mqttPassword = "kAbninqGe4us";
#define LED 2
char* topic;
WiFiClient espclient1;
PubSubClient client(espclient1);
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("esp/test");

 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  String msgg;
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    msgg=msgg+(char)payload[i]; 
  }
  if(topic == "esp/test"){
  Serial.print("Loop entered");
  Serial.print(topic);
  
  if(msgg == "#on")
  {
  digitalWrite(LED,HIGH); 
  Serial.print("\n up \n ");
  }
  else if(msgg == "#off")
  {
  digitalWrite(LED,LOW);
  Serial.print("\n down");
  
  }
  }
  Serial.print(msgg);
  Serial.println();
  Serial.println("-----------------------");

  

}
 
void loop() {
  client.loop();
}
