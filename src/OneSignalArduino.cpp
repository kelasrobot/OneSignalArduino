#include "OneSignalArduino.h"
#include "Arduino.h"

void OneSignalArduino::begin(String _inputOneSignalAuth,
                             String _inputOneSignalAppId) {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  if (WiFi.status() == WL_CONNECTED) {
    while (nowSecs < 1 * 3600 * 2) {
      delay(500);
      Serial.print(F("."));
      yield();
      nowSecs = time(nullptr);
    }
  }
  Serial.println();
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
  Serial.print(F("Current time: "));
  Serial.print(asctime(&timeinfo));
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  _oneSignalAuth = _inputOneSignalAuth;
  _oneSignalAppId = _inputOneSignalAppId;
}

void OneSignalArduino::send(String _inputOneSignalHeadings,
                            String _inputOneSignalContents) {
  WiFiClientSecure *client = new WiFiClientSecure;
  client->setInsecure(); // skip verification
  //  if(client) {
  //    client -> se(fingerprint);
  //
  //    {
  // Add a scoping block for HTTPClient https to make sure it is destroyed
  // before WiFiClientSecure *client is
  HTTPClient https;
  Serial.print("Sending Notification...\n");
  if (https.begin(*client,
                  "https://onesignal.com/api/v1/notifications")) { // HTTPS
    https.addHeader("Content-Type", "application/json; charset=utf-8", true,
                    false);
    https.addHeader("Authorization",
                    "Basic " +
                        _oneSignalAuth); // remove '<>' wheb typing api key

    Serial.print("Sending Notification... POST...\n");

    String json = "{"
                  "\"app_id\": \"" +
                  _oneSignalAppId +
                  "\","
                  "\"included_segments\": [\"Subscribed Users\"],"
                  "\"data\": {\"foo\": \"bar\"},"
                  "\"headings\": {\"en\": \"" +
                  _inputOneSignalHeadings +
                  "\"},"
                  "\"contents\": {\"en\": \"" +
                  _inputOneSignalContents +
                  "\"}"
                  "}";

    int httpCode = https.POST(json);

    if (httpCode > 0) {
      Serial.printf("Send Notification... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("Send Notification... failed, error: %s\n",
                    https.errorToString(httpCode).c_str());
    }
    https.end();
  } else {
    Serial.printf("Send Notification... Unable to connect\n");
  }
  Serial.println();
}