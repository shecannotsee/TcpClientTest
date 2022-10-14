//
// Created by shecannotsee on 2022/10/13.
//

#ifndef TCP_CLIENT_TEST_TCPCLIENTTEST_SRC_CLIENTCONNECT_H_
#define TCP_CLIENT_TEST_TCPCLIENTTEST_SRC_CLIENTCONNECT_H_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>//sleep

typedef int client_socket_id;

client_socket_id clientConnect(std::string ip,std::string port) {
  //用户连接的服务器 IP + port
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = PF_INET;
  serverAddr.sin_port = htons(std::atoi(port.c_str()));
  serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

  // 创建socket
  int client_socket_id = socket(PF_INET, SOCK_STREAM, 0);
  if (client_socket_id>=0)
    std::cout<<"create socket success.\n";
  else
    std::cout<<"create socket failed.\n";

part_connect:
  // 连接服务器
  int connect_result = connect(client_socket_id, (struct  sockaddr*)&serverAddr, sizeof(serverAddr));
  if (connect_result>=0)
    std::cout<<"connect server success.\n";
  else {
    std::cout << "connect server failed.\n";
    sleep(5);
    goto part_connect;
  }
  return client_socket_id;
}

#endif //TCP_CLIENT_TEST_TCPCLIENTTEST_SRC_CLIENTCONNECT_H_
