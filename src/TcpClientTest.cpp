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

void client_run(
    const std::string& ip,
    const std::string& port,
    const std::string& block,
    const std::string& block_type,
    const std::string& time_) {
  int client_socket_id = clientConnect(ip,port);
  std::this_thread::yield();

  bool sendMessageLoopOn = true;
  while (sendMessageLoopOn) {
    std::string message = "{a};";
    if (block == "yes" && block_type == "input") {
      std::cout << "input:...\n";
      std::cin >> message;
    } else if (block=="yes" && block_type == "auto") {
      sleep(std::atoi(time_.c_str()));
    } else if (block=="no"){
      sendMessageLoopOn = false;
    }
    send(client_socket_id, message.c_str(), message.size(), 0);
    std::cout <<"," <<++event_num<<",";

  };

  close(client_socket_id);
}

int main() {
  std::cout<<"Tcp client test start.\n";
  std::string section_test = "test";;
  std::string client_num = "client_num";
  std::string thread_num = "thread_num";
  getConfig(section_test,client_num,thread_num);

  std::string section_server = "server";
  std::string ip = "ip";
  std::string port = "port";
  getConfig(section_server,ip,port);

  std::string section_client_type = "client_type";
  std::string block = "block";// yes - no
  std::string block_type = "block_type";// auto - input
  getConfig(section_client_type,block,block_type);

  std::string section_sleep = "sleep";
  std::string time_ = "time";
  std::string ddsa;
  getConfig(section_sleep,time_,ddsa);

  int n = (block=="yes")?std::atoi(client_num.c_str()):std::atoi(thread_num.c_str());
  while ( block=="yes" && block_type=="input") n = 1;
  sheThreadPool::ThreadPool pool(n);
  for (int i=0; i<n; ++i)
    pool.submit(client_run, ip, port, block, block_type, time_);


  std::cout<<"Tcp client test end(main thread).\n";
  return 0;
}

