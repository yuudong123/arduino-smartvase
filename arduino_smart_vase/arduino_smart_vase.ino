#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

#define DHTTYPE DHT11

#define LightSensor A0
#define LED LED_BUILTIN
#define Light D5
#define Btn1 D1
#define Btn2 D2
#define Btn3 D3
DHT tempSensor(D7, DHTTYPE);
SoftwareSerial bluetooth(D6, D4);

bool anyBtnPressed = false;

// const char *ssid = "hanul301";
// const char *password = "hanul301";

void setup() {
  Serial.begin(9600);
  pinMode(LightSensor, INPUT);
  pinMode(Light, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(Btn1, INPUT_PULLUP);
  pinMode(Btn2, INPUT_PULLUP);
  pinMode(Btn3, INPUT_PULLUP);
  tempSensor.begin();
  WiFi.mode(WIFI_STA);
}

void loop() {
  if (digitalRead(Btn1) == 0 && !anyBtnPressed) {
    anyBtnPressed = true;
    reqTOspring(1);
  }

  if (digitalRead(Btn2) == 0 && !anyBtnPressed) {
    anyBtnPressed = true;
    reqTOspring(2);
  }

  if (digitalRead(Btn3) == 0 && !anyBtnPressed) {
    anyBtnPressed = true;
    setWiFi();
  }
}

void reqTOspring(int btn) {
  WiFiClient client;
  HTTPClient http;
  String url = "none";

  if (btn == 1) {
    int t = tempSensor.readTemperature();
    int h = tempSensor.readHumidity();
    if (isnan(t) || isnan(h)) {
      Serial.println("센서와 연결되지 않았습니다");
      return;
    }
    String temperature = String(t);
    String humidity = String(h);
    url = "http://192.168.0.219:9090/thcheck.ard?";
    url += "temperature=" + temperature + "&humidity=" + humidity;
  } else if (btn == 2) {
    String state = analogRead(LightSensor) > 300 ? "ON" : "OFF";
    digitalWrite(Light, analogRead(LightSensor) > 300 ? 1 : 0);
    Serial.println(analogRead(LightSensor));
    url = "http://192.168.0.219:9090/ledchange.ard?";
    url += "state=" + state;
  }
  if (url == "none") {
    Serial.println("주소가 none입니다.");
    return;
  }

  Serial.println(url);
  http.begin(client, url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    if (httpResponseCode == 200) {
      blink(2);
    } else if (httpResponseCode == 400) {
      blink(4);
    } else if (httpResponseCode == 500) {
      blink(5);
    }
    Serial.println(response);
  } else {
    Serial.print("Error on HTTP request: ");
    Serial.println(httpResponseCode);
    blink(1);
  }

  http.end();
  anyBtnPressed = false;
}

void setWiFi() {
  bluetooth.begin(9600);

  if (WiFi.status() == WL_CONNECTED) { WiFi.disconnect(); }

  while (!bluetooth.available()) {
    blink(1);
  }

  String ssid = bluetooth.readStringUntil('\n');
  ssid.trim();
  Serial.print(ssid);

  while (!bluetooth.available()) {
    blink(1);
  }

  String password = bluetooth.readStringUntil('\n');
  password.trim();
  Serial.print(password);

  WiFi.begin(ssid.c_str(), password.c_str());
  int wait = 0;
  while (WiFi.status() != WL_CONNECTED && wait < 30) {
    delay(500);
    Serial.print(".");
    wait++;
  }
  if (wait >= 30) {
    Serial.println("WiFi connection Failed.");
    anyBtnPressed = false;
    return;
  } else {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  anyBtnPressed = false;
}

void blink(int cnt) {
  for (int i = 0; i < cnt; i++) {
    digitalWrite(LED, 1);
    delay(100);
    digitalWrite(LED, 0);
    delay(200);
  }
}