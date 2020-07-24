// Created by tz301 on 2020/07/03

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <zmq.hpp>

#include "../asr/asr.h"

/**
 * @brief Print current time.
 */
void PrintTime() {
  auto cur_time = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(cur_time);
  std::cout << std::ctime(&time);
}

/**
 * @brief Main function.
 */
int main() {
  std::string model_dir = "../tests/model";
  asr::OnlineAsr online_asr(model_dir);

  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_REP);
  socket.bind("tcp://*:6557");

  PrintTime();
  std::cout << "Server start in port 6557." << std::endl;

  while (true) {
    zmq::message_t message;
    socket.recv(&message);

    auto data_ptr = static_cast<char *>(message.data());
    auto msg_len = message.size();
    bool is_end = false;
    if (msg_len % 2 != 0) {
      is_end = true;
      --msg_len;
      PrintTime();
      std::cout << "Finish." << std::endl;
    }

    std::vector<char> data(data_ptr, data_ptr + msg_len);
    auto transcript = online_asr.Recognize(16000, data, is_end);

    auto len = transcript.size();
    zmq::message_t reply(len);
    memcpy(reply.data(), transcript.c_str(), len);
    socket.send(reply);
  }
}
