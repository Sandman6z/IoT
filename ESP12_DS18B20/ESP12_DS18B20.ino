#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;  // arrays to hold device address

const char* ssid     = "SFA-Senior";
const char* password = "woaisfair";

ESP8266WebServer server(80);

float tempC;  // Values read from sensor
String webString = "";     // String to display

 
void handle_root() 
{
  server.send(200, "text/plain", "Hello from the weather esp8266, read from /temp or /humidity");
  delay(100);
}

void setup(void)
{
  Serial.begin(115200);  
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
  
  Serial.println("");
  
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

 // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) 
    Serial.println("ON");
  else 
    Serial.println("OFF");
  
  if (!sensors.getAddress(insideThermometer, 0))
    Serial.println("Unable to find address for Device 0"); 


// show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(insideThermometer, 9);
 
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC); 
  Serial.println();

  
    
   //初始化WebServer
  server.on("/", handle_root);
  
  server.on("/temp", [](){
    webString="Temperature: "+String(tempC)+ "C";   // Arduino has a hard time with float to string
    server.send(200, "text/plain", webString);            // send to someones browser when asked
  });
  
  server.begin();
  Serial.println("HTTP server started");
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  tempC = sensors.getTempC(deviceAddress);
  if(tempC == DEVICE_DISCONNECTED_C) 
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
  Serial.print("Temp C: ");
  Serial.println(tempC);
}




void loop(void)
{
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  
  // It responds almost immediately. Let's print out the data
  printTemperature(insideThermometer); // Use a simple function to print out the data
  
  server.handleClient();
} 


// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
