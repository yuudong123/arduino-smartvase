# 스펙

## 웹서버
- java 11
- Spring boot 2.7.11
- mybatis, lombok, jdbc, oracle driver, thymeleaf(아직 미사용)

## 아두이노
- esp8266
- dht11 (온습도 센서)

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

### temp.html은 현재 사용하지 않음.