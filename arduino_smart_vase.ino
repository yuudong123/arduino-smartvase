#include <DHT.h>  //// DHT11 센서를 쉽게 제어하기 위한 라이브러리를 추가해줍니다.

#define DHTTYPE DHT11

#define LightSensor A0
#define Led D5
#define Btn1 D1
#define Btn2 D2
#define Btn3 D3

DHT tempSensor(D6, DHTTYPE);

int btn1flag = 0;
int btn2flag = 0;
int btn3flag = 0;
boolean toggle_state = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LightSensor, INPUT);
  pinMode(Led, OUTPUT);
  pinMode(Btn1, INPUT_PULLUP);
  pinMode(Btn2, INPUT_PULLUP);
  pinMode(Btn3, INPUT_PULLUP);

  tempSensor.begin();
}

void loop() {

  if (digitalRead(Btn1) == 0) {
    if (btn1flag == 0) {
      btn1flag = 1;
      toggle_state = !toggle_state;
    }
  } else {
    if (btn1flag == 1) {
      btn1flag = 0;
      tempCheck();
    }
  }

  if (digitalRead(Btn2) == 0) {
    if (btn2flag == 0) {
      btn2flag = 1;
      toggle_state = !toggle_state;
    }
  } else {
    if (btn2flag == 1) {
      btn2flag = 0;
      tempCheck();
    }
  }

  if (digitalRead(Btn3) == 0) {
    if (btn3flag == 0) {
      btn3flag = 1;
      toggle_state = !toggle_state;
    }
  } else {
    if (btn3flag == 1) {
      btn3flag = 0;
      tempCheck();
    }
  }
}

void tempCheck() {
  int humidity = tempSensor.readHumidity();
  int temperature = tempSensor.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("센서와 연결되지 않았습니다"));
    return;
  }

  Serial.print(temperature);
  Serial.print(" *C, ");
  Serial.print(humidity);
  Serial.println(" %");
}