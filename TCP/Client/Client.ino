#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "SK_WiFi6D47"    //  와이파이 이름
#define STAPSK  "1509007217"    //  와이파이 비밀번호
#endif

/*와이파이*/
const char* ssid     = STASSID;
const char* password = STAPSK;

byte mac[6];    //  Mac주소 저장 변수

/*TCP 서버  Info*/
const char* serverIP = "192.168.25.44";    //  접속할 서버 IP
const int tcpPort = 22485;    //  서버에 접속할 포트(지금 예시에서는 22485를 사용)

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
  String st = Serial.readString();
  
  if(st.equals("open\n")) {
    st = "";
    WiFiClient client;

    bool connected = client.connect(serverIP, tcpPort);

    if(!connected) {
      Serial.println("Disconnected");
    }
    else {
      Serial.println("Connected");
      String msg;
      char chMsg[100];
      while(connected) {
        msg = Serial.readString();
        if(msg.length() > 0) {
          msg.toCharArray(chMsg, msg.length() + 1);
          client.write(chMsg);
          Serial.print("msg: ");
          Serial.println(msg);
        }
        delay(10);
        
        connected = !(msg.equals("close\n"));
      }
      Serial.println("Client disconnected");
      client.stop();
    }
    delay(1000);
  }
}
