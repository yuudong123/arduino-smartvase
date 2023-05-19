package com.smartvase.server.mapper;

import org.apache.ibatis.annotations.Mapper;

import com.smartvase.server.domain.THDTO;

@Mapper
public interface ArduinoMapper {
  public void thcheck(THDTO dto);

  public void ledchange(String state);
}
