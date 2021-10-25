#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "SK_WiFi6D47"    //  와이파이 이름
#define STAPSK  "1509007217"    //  와이파이 비밀번호
#endif

/*와이파이*/
const char* ssid     = STASSID;
const char* password = STAPSK;

byte mac[6];                     // the MAC address of your Wifi shield

void setup() {
  /*시리얼 모니터 보드레이트*/
  Serial.begin(115200);

  /*WiFi setup*/
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  /*와이파이 연결될 때까지 반복*/
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
}

void loop() {
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(10000);
}
