#ifndef OneSignalArduino_h
#define OneSignalArduino_h

#include "Arduino.h"
#include "HTTPClient.h"
#include "WiFiClientSecure.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

class OneSignalArduino {
  private:
    String _oneSignalAuth;
    String _oneSignalAppId;
  public:
    void begin(String _inputOneSignalAuth, String _inputOneSignalAppId);
    void send(String _inputOneSignalHeadings, String _inputOneSignalContents);
};

#endif