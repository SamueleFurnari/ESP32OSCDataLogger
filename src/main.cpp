#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

WiFiUDP Udp;
const unsigned int localPort = 8000;


void printOSCMessage(OSCMessage &msg);


void setup() {
  Serial.begin(115200);


  WiFiManager wifiManager;

  if (!wifiManager.autoConnect("OSCDataLogger", "password"))
  {
    Serial.println("Failed to connect and hit  timeout");
    ESP.restart();
  }

  Serial.println("Connected to WiFi!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Udp.begin(localPort);
  Serial.print("Listening on port ");
  Serial.println(localPort);

}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    OSCMessage msg;
    while (packetSize--)
    {
      msg.fill(Udp.read());
    }

    if (!msg.hasError())
    {
      Serial.print("Received OSC message: ");
      printOSCMessage(msg);
    }
    else
    {
      Serial.print("Error in OSC message. Error code: ");
      OSCErrorCode error = msg.getError();
      Serial.println(error);
    }
    
  }
  
}

void printOSCMessage(OSCMessage &msg) {
  Serial.print("Address: ");
  Serial.println(msg.getAddress());

  for (int i = 0; i < msg.size(); i++)
  {
    if (msg.isInt(i))
    {
      Serial.print("Int: ");
      Serial.println(msg.getInt(i));
    } else if (msg.isFloat(i))
    {
      Serial.print("Float: ");
      Serial.println(msg.getFloat(i));
    } else if (msg.isString(i))
    {
      char buffer[100];
      msg.getString(i, buffer, 100);
      Serial.print("String: ");
      Serial.println(buffer);
    }
    
  }
  
}