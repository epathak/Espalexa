/*
 * This is a basic example on how to use Espalexa and its device declaration methods.
 */ 
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

// prototypes
boolean connectWifi();

//callback functions
void deviceChanged(String devicename, uint8_t brightness);

// Change this!!
const char* ssid = "...";
const char* password = "wifipassword";

boolean wifiConnected = false;

Espalexa espalexa;

EspalexaDevice* device1, device2; //Declare device variables

void setup()
{
  Serial.begin(115200);
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    
    device1 = new EspalexaDevice("Light 1", deviceChanged);//Intantiate variables
    espalexa.addDevice(device1);
    
    device2 = new EspalexaDevice("Light 2", deviceChanged);
    espalexa.addDevice(device2);

    espalexa.begin();
    
  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
 
void loop()
{
   espalexa.loop();
   delay(1);
}

//our callback function

void thirdLightChanged(String devicename, uint8_t brightness) {
  if(devicename == "Light 1"){
    //do something like analogWrite(pin1, brightness);
  }
  if(devicename == "Light 2"){
    //do something like analogWrite(pin2, brightness);
  }
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
