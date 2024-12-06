#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h> // Thư viện HTTPS

#define LED 2 // LED kết nối chân D4
#define BUZZER 5 // Buzzer kết nối chân D0

// Wi-Fi thông tin
const char* WIFI_SSID = "NLTH";
const char* WIFI_PASSWORD = "hoatinh11121319";

// Firebase URL (Realtime Database)
const char* FIREBASE_HOST = "https://ltnhung-4e40f-default-rtdb.asia-southeast1.firebasedatabase.app/";

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(LED, LOW); // Tắt LED ban đầu
  digitalWrite(BUZZER, LOW); // Tắt Buzzer ban đầu

  // Kết nối Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  WiFiClientSecure client;
  client.setInsecure();    // Bỏ kiểm tra chứng chỉ SSL
  HTTPClient http;

  // Kiểm tra trạng thái LED
  String urlLedOn = String(FIREBASE_HOST) + "/LedOn.json"; 
  http.begin(client, urlLedOn);
  int httpCodeLedOn = http.GET();
  if (httpCodeLedOn > 0) {
    String payloadLedOn = http.getString();
    Serial.print("LED State: ");
    Serial.println(payloadLedOn);
    if (payloadLedOn == "true") {
      // Lấy độ sáng LED
      String urlLedBright = String(FIREBASE_HOST) + "/LedBrightness.json"; 
      http.begin(client, urlLedBright);
      int httpCodeLedBright = http.GET();
      if (httpCodeLedBright > 0) {
        String payloadLedBright = http.getString();
        int brightness = payloadLedBright.toInt(); // Chuyển chuỗi sang số nguyên
        Serial.print("LED Brightness: ");
        Serial.println(brightness);
        analogWrite(LED, brightness); 
        delay(1000);
        digitalWrite(LED,LOW);// Điều chỉnh độ sáng LED
      } else {
        Serial.print("Failed to get LedBrightness: ");
        Serial.println(http.errorToString(httpCodeLedBright));
      }
    } else {
      digitalWrite(LED, LOW); // Tắt LED
    }
  } else {
    Serial.print("HTTP request failed for LedOn: ");
    Serial.println(http.errorToString(httpCodeLedOn));
  }
  // Kiểm tra trạng thái Buzzer
  String urlBuzOn = String(FIREBASE_HOST) + "/BuzOn.json"; 
  http.begin(client, urlBuzOn);
  int httpCodeBuzOn = http.GET();
  if (httpCodeBuzOn > 0) {
    String payloadBuzOn = http.getString();
    Serial.print("Buzzer State: ");
    Serial.println(payloadBuzOn);
    if (payloadBuzOn == "true") {
      digitalWrite(BUZZER, HIGH); // Bật Buzzer
    } else {
      digitalWrite(BUZZER, LOW); // Tắt Buzzer
    }
  } else {
    Serial.print("HTTP request failed for BuzOn: ");
    Serial.println(http.errorToString(httpCodeBuzOn));
  }
  http.end();

  delay(2000); // 2 giây
}


//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//#include <WiFiClientSecure.h> // Thêm thư viện này
//
//#define LED 2
//// Wi-Fi thông tin
//const char* WIFI_SSID = "NLTH";
//const char* WIFI_PASSWORD = "hoatinh11121319";
//
//// Firebase URL (Realtime Database)
//const char* FIREBASE_HOST = "https://ltnhung-4e40f-default-rtdb.asia-southeast1.firebasedatabase.app/";
//
//void setup() {
//  Serial.begin(115200);
//  pinMode(LED,OUTPUT);
//  // Kết nối Wi-Fi
//  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//  Serial.print("Connecting to Wi-Fi...");
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println(" Connected!");
//
//  HTTPClient http;
//  WiFiClientSecure client; // Sử dụng WiFiClientSecure cho HTTPS
//  client.setInsecure();   // Bỏ kiểm tra chứng chỉ (không an toàn nhưng đơn giản)
//
//  // Lấy trạng thái LED từ Firebase
//  String urlLedOn = String(FIREBASE_HOST) + "/LedOn.json"; // Endpoint Firebase cho LedOn
//  http.begin(client, urlLedOn); // Sử dụng WiFiClientSecure
//  int httpCodeLedOn = http.GET();
//  if (httpCodeLedOn > 0) {
//    Serial.print("HTTP Response code for LedOn: ");
//    Serial.println(httpCodeLedOn);
//    String payloadLedOn = http.getString();
//    Serial.print("Response for LedOn: ");
//    Serial.println(payloadLedOn);
//  } else {
//    Serial.print("HTTP request failed for LedOn, error: ");
//    Serial.println(http.errorToString(httpCodeLedOn));
//  }
//  http.end();
//
//  // Lấy trạng thái Buzzer từ Firebase
//  String urlBuzOn = String(FIREBASE_HOST) + "/BuzOn.json"; // Endpoint Firebase cho BuzOn
//  http.begin(client, urlBuzOn); // Sử dụng WiFiClientSecure
//  int httpCodeBuzOn = http.GET();
//  if (httpCodeBuzOn > 0) {
//    Serial.print("HTTP Response code for BuzOn: ");
//    Serial.println(httpCodeBuzOn);
//    String payloadBuzOn = http.getString();
//    Serial.print("Response for BuzOn: ");
//    Serial.println(payloadBuzOn);
//  } else {
//    Serial.print("HTTP request failed for BuzOn, error: ");
//    Serial.println(http.errorToString(httpCodeBuzOn));
//  }
//  http.end();
//
//  // Lấy độ sáng LED từ Firebase
//  String urlLedBrightness = String(FIREBASE_HOST) + "/LedBrightness.json"; // Endpoint Firebase cho LedBrightness
//  http.begin(client, urlLedBrightness); // Sử dụng WiFiClientSecure
//  int httpCodeLedBrightness = http.GET();
//  if (httpCodeLedBrightness > 0) {
//    Serial.print("HTTP Response code for LedBrightness: ");
//    Serial.println(httpCodeLedBrightness);
//    String payloadLedBrightness = http.getString();
//    Serial.print("Response for LedBrightness: ");
//    Serial.println(payloadLedBrightness);
//  } else {
//    Serial.print("HTTP request failed for LedBrightness, error: ");
//    Serial.println(http.errorToString(httpCodeLedBrightness));
//  }
//  http.end();
//}
//
//void loop() {
//  // Có thể thêm logic gửi dữ liệu hoặc lặp request ở đây
//}
