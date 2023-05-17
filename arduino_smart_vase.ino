#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#define DHTTYPE DHT11

#define LightSensor A0
#define LED LED_BUILTIN
#define Light D5
#define Btn1 D1
#define Btn2 D2
#define Btn3 D3
DHT tempSensor(D6, DHTTYPE);

int btn1flag = 0;
int btn2flag = 0;
int btn3flag = 0;
boolean toggle_state = 0;

const char *ssid = "hanul301";
const char *password = "hanul301";

void setup()
{
  Serial.begin(9600);
  pinMode(LightSensor, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(Btn1, INPUT_PULLUP);
  pinMode(Btn2, INPUT_PULLUP);
  pinMode(Btn3, INPUT_PULLUP);
  tempSensor.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  if (digitalRead(Btn1) == 0)
  {
    if (btn1flag == 0)
    {
      btn1flag = 1;
      toggle_state = !toggle_state;
    }
  }
  else
  {
    if (btn1flag == 1)
    {
      btn1flag = 0;
      thCheck();
    }
  }

  if (analogRead(LightSensor) < 150)
  {
    digitalWrite(Light, 1);
  }
  else
  {
    digitalWrite(Light, 0);
  }
}

void thCheck()
{

  int t = tempSensor.readTemperature();
  int h = tempSensor.readHumidity();

  if (isnan(t) || isnan(h))
  {
    Serial.println(F("센서와 연결되지 않았습니다"));
    return;
  }
  String temperature = String(t);
  String humidity = String(h);
  String url = "http://192.168.0.219:9090/thcheck.ard?";
  url += "temperature=" + temperature + "&humidity=" + humidity;

  Serial.println(url);
  WiFiClient client;
  HTTPClient http;
  http.begin(client, url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0)
  {
    String response = http.getString();
    Serial.println(httpResponseCode);
    if (httpResponseCode == 200)
    {
      blink(2);
    }
    else if (httpResponseCode == 400)
    {
      blink(4);
    }
    else if (httpResponseCode == 500)
    {
      blink(5);
    }
    Serial.println(response);
  }
  else
  {
    Serial.print("Error on HTTP request: ");
    Serial.println(httpResponseCode);
    blink(1);
  }

  http.end();
}

void blink(int cnt)
{
  for (int i = 0; i < cnt; i++)
  {
    digitalWrite(LED, 1);
    delay(100);
    digitalWrite(LED, 0);
    delay(200);
  }
}