#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "..\include\config.h"
#include "..\include\helper.h"

class Receiver
{
private:
  std::string data = "";

public:
  const std::string &getData() const;
  void setData(const std::string &data);
  void appendData(const std::string &data);

  std::vector<Frame> viterbi(std::vector<Frame> &input);  // decode convo
  bool checkCRC(Frame &frame);                            // kiểm tra crc
  std::vector<Frame> removeCRC(std::vector<Frame> &frame); //  lọc lấy data
  Frame removeCRCperFrame(Frame &frame);
  std::string combineFrames(std::vector<Frame> &frames);   //  gom data
};