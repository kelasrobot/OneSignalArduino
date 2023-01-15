#include <WiFiManager.h>
WiFiManager wifiManager;

#include <OneSignalArduino.h>
OneSignalArduino notif;
String auth = "insert One Signal Rest API Key";
String appId = "insert One Signal App Id One Signal";

void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  //  wifiManager.resetSettings();
  wifiManager.setConfigPortalBlocking(false);
  wifiManager.setConfigPortalTimeout(180);
  if (wifiManager.autoConnect("Pakan Ikan Otomatis"))
    Serial.println("connected...yeey :)");
  else
    Serial.println("Configportal running");

  notif.begin(auth, appId);
  notif.send("Hello!", "Hello World");
}

void loop() {
  wifiManager.process();
}
