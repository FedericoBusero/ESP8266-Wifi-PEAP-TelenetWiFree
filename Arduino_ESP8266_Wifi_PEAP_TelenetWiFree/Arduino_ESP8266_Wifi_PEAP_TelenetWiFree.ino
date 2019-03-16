// This is an example to show how to connect to the WPA2 PEAP MSCHAPv2 network TelenetWiFree on ESP8266
// Based on information on  https://github.com/esp8266/Arduino/issues/3442

#include <ESP8266WiFi.h>
#include "user_interface.h"
#include "wpa2_enterprise.h"

// SSID to connect to
static const char* myssid = "TelenetWiFree";
// Username for authentification
static const char* myusername = "xxx@telenet.be";
// Password for authentication
static const char* mypassword = "paswoord";

void wifi_begin_peap(const char *ssid, const char *username, const char *password)
{
  wifi_set_opmode(STATION_MODE);
  struct station_config wifi_config;
  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, ssid);
  wifi_station_set_config(&wifi_config);
  wifi_station_clear_cert_key();
  wifi_station_clear_enterprise_ca_cert();
  wifi_station_set_wpa2_enterprise_auth(1);
  wifi_station_set_enterprise_identity((uint8*)"", 0);
  wifi_station_set_enterprise_username((uint8*)username, strlen(username));
  wifi_station_set_enterprise_password((uint8*)password, strlen(password));
  wifi_station_connect();
}

void setup() {

  // put your setup code here, to run once:
  Serial.begin(115200);

  delay(500);

  // Normal Connection starts here
  /*
    WiFi.mode(WIFI_STA);
    Serial.write("\r\nConnect to WLAN");
    WiFi.begin(ssid, password);
    // Normal Connection ends here
  */
  wifi_begin_peap(myssid,myusername, mypassword);

  // Wait for connection AND IP address from DHCP
  Serial.println();
  Serial.println("Waiting for connection and IP Address from DHCP");
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  IPAddress myAddr = WiFi.localIP();
}

void loop() {

}
