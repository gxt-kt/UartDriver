#ifndef PROJECT1__UARTDRIVER_H_
#define PROJECT1__UARTDRIVER_H_

#include "gDebug/gDebug.h"
#include <string>
#include <vector>

namespace MyUartDriver {

enum type { frame_header, frame_end, frame_data, frame_cnt, frame_check };

class UartDriver {
 public:

  UartDriver() = default;
  ~UartDriver() = default;

  void AddLayer(size_t type, uint8_t val = 1);
  bool GetOneByte(uint8_t val);

 private:
  std::vector<std::pair<size_t, uint8_t>> layer;
 public:
  std::vector<uint8_t> buf;
}; // class UartDriver

} // namespace UartDriver

#endif //PROJECT1__UARTDRIVER_H_
