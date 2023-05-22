## 웹서버
- java 11
- Spring boot 2.7.11
- mybatis, lombok, jdbc, oracle driver, thymeleaf(미사용)

## 아두이노
- NodeMCU 1.0 (esp8266)
- 블루투스 모듈 (hc-06)
- 온습도 센서 (dht11)
- 조도 센서

## DB 세팅

```sql
create table tbl_thcheck (
    no number,
    temperature varchar2(4),
    humidity varchar2(3),
    checkdate date default sysdate,
    constraint pk_thcheck primary key (no)
);

commit;
```

- temp.html은 현재 사용하지 않음.

## 기능 설명

### 초기 선언 값
- LightSensor : 조도 센서 핀 (A0)
- LED : 기기상태 표시 LED 핀 (LED_BUILTIN)
- Light : 조명용 LED 핀 (D5)
- Btn1, Btn2, Btn3 : 버튼1, 2, 3 (D1, D2, D3)
- tempSensor : 온습도 센서
- bluetooth : 블루투스 소프트웨어 시리얼 설정 (Rx - D6, Tx - D4)
- isInProgress : 진행중인 절차 유무 여부 (요청 중복 방지)

### 아두이노
- 모든 버튼은 메소드 실행 전에 isInProgress를 true로 변경
  
- btn1 : 누를 시 reqTOspring(1) 실행
- btn2 : 누를 시 reqTOspring(2) 실행
- btn3 : 누를 시 setWiFi() 실행
- 
### 메소드
- void blink(int cnt)
  1. 설정된 LED를 (cnt)번 점멸
   
- void setWiFi()
  1. 블루투스 통신 시작
  2. 와이파이 이름과 비밀번호가 입력될 때까지 blink(1) 반복하고, 입력되면 연결 시도
  3. 최대 15초까지 대기, 연결 성공 시 blink(3), 실패 시 종료

- void reqTOspring(int btn)
  1. 버튼마다 번호를 지정하고 btn으로 받아옴.
  2. btn == 1 , 온습도 측정 후 값을 String으로 변환
  3. btn == 2 , 주변 밝기에 따라 조명을 켜거나 끄고, on/off 여부를 String으로 저장
  4. 각 버튼마다 서버에 설정된 url에 파라미터를 적어 GET 요청
  5. 응답 코드에 따라 blink() 실행

- 메소드 공통으로, 종료 시에 isInProgress를 false로 변경


### 추후 수정해야하는 요소
- LED는 버튼이 아닌 일정 주기마다 밝기를 측정하고 그에 따라 LED 점등하도록 하고, 값이 변경될 때만 서버에 전송하도록 수정.
- 와이파이 세팅을 현재는 Serial Bluetooth Terminal 앱으로 했으나, 직접만든 앱에 기능으로 추가.
- setWiFi() 실행 중, 입력값이 없는 상태에서 btn3을 한번 더 누르거나, 앱에서 와이파이 설정 취소를 선택할 시 메소드를 종료하도록 수정.