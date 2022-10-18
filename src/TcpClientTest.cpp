//
// Created by shecannotsee on 2022/10/13.
//
#include <iostream>
#include <map>
#include <atomic>
#include <random>
#include <thread>
#include <sys/socket.h>
#include <unistd.h>//sleep
#include "getConfig.h"
#include "clientConnect.h"
#include "ThreadPool/ThreadPool.h"

static std::atomic<unsigned int> event_num;

void client_register(const std::string& ip, const std::string& port) {
  int client_socket_id = clientConnect(ip,port);
  std::this_thread::yield();

  bool sendMessage = true;
  while (sendMessage) {
    std::string message = "{a};";
    std::cout<<"input:...\n";
    std::cin>>message;
    if (message != "stop") {
      sleep(0);
      send(client_socket_id, message.c_str(), message.size(), 0);
      std::cout <<"," <<++event_num<<",";
    }
    else
      sendMessage = false;
  };
  close(client_socket_id);
}

int main() {
  std::cout<<"start.\n";
  std::string section_test = "test";;
  std::string client_num = "client_num";
  std::string thread_num = "thread_num";// because client_register block,so this key has no practical use
  getConfig(section_test,client_num,thread_num);
  std::string section_server = "server";
  std::string ip = "ip";
  std::string port = "port";
  getConfig(section_server,ip,port);

  sheThreadPool::ThreadPool pool(std::atoi(client_num.c_str()));
  for (int i=0; i<std::atoi(client_num.c_str()) ;++i) {
    pool.submit(client_register, ip, port);
  }

  std::cout<<"end.\n";
  return 0;
}

