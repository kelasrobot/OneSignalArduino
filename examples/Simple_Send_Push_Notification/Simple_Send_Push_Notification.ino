#include <WiFi.h>
#define ssid "insert wifi name"
#define pass "insert wifi password"

#include <OneSignalArduino.h>
OneSignalArduino notif;
String auth = "insert One Signal Rest API Key";
String appId = "insert One Signal App Id One Signal";

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }
  Serial.print("Connected to WIFI!");
  Serial.println(WiFi.localIP());

  notif.begin(auth, appId);
  notif.send("Hello!", "Hello World");
}

void loop() {

}
