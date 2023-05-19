package com.smartvase.server;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import com.smartvase.server.domain.THDTO;
import com.smartvase.server.mapper.ArduinoMapper;

@RestController
public class ArduinoController {

  @Autowired
  ArduinoMapper mapper;

  @GetMapping("/thcheck.ard")
  public String thcheck(THDTO dto) {
    mapper.thcheck(dto);
    return "";
  }

  @GetMapping("/ledchange.ard")
  public String ledchange(String state) {
    mapper.ledchange(state);
    return "";
  }
}
