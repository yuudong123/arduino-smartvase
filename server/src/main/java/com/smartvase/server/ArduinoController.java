package com.smartvase.server;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import com.smartvase.server.domain.THDTO;
import com.smartvase.server.mapper.ArduinoMapper;

@Controller
public class ArduinoController {

  @Autowired
  ArduinoMapper mapper;

  @GetMapping("/thcheck.ard")
  @ResponseBody
  public String thcheck(THDTO dto) {
    mapper.thcheck(dto);
    return "";
  }
}
