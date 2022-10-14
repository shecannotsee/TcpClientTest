//
// Created by shecannotsee on 2022/10/13.
//

#ifndef TCP_CLIENT_TEST_TCPCLIENTTEST_SRC_GETCONFIG_H_
#define TCP_CLIENT_TEST_TCPCLIENTTEST_SRC_GETCONFIG_H_

#include <iostream>
#include <vector>
#include "DataStructure/Section.h"
#include "Parse/Parse.h"

void getConfig(std::string& section, std::string& ip, std::string& port) {
  std::vector<sheIni::Section> config;
  /* get config */ {
    sheIni::IniFile config_file("/etc/TcpClientTest/TcpClientTest.config");
    config_file.parse(config);
  }
  for (auto& e:config) {
    // get section
    if (e.getSection() == section) {
      for (auto& ee: e.getAllKV() ) {
        if      (std::get<0>(ee) == ip)   ip   = std::get<1>(ee);
        else if (std::get<0>(ee) == port) port = std::get<1>(ee);
      }
    }
  }
}

#endif //TCP_CLIENT_TEST_TCPCLIENTTEST_SRC_GETCONFIG_H_
