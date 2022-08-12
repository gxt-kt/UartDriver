# UartDriver use

It's a uart driver to fast development.

Your can use this code to fast fit common uart protocal.

## EXAMPLE

There are five kind type in UartDriver.h `enum type { frame_header, frame_end, frame_data, frame_cnt, frame_check };`

- frame_header : common use of the header of  frame  , you can also use it to fixed data. So you can have multiple frame_header.
- frame_end  : common use of the end of frame. Note that once you receive the frame_end, however if the data is right ,the frame will be end.
- frame_data : common use of the data. When you need add multiple data. Use the AddLayer Function like AddLayer(MyUartDriver::frame_data,cnt). The cnt represent the data number you want to add.
- frame_cnt : Represent the not fix number of data. Your will receive frame_cnt data.
- frame_check : like frame_data. Your need to check the data after your receive a whole frame.

### example0.
> 0x11 , data1 , data2 , 0x10
```c++
#include <iostream>
#include "UartDriver.h"
#include <cmath>

std::vector<uint8_t> test_data={0x10,0x11,0x2,0x13,0x10,0x2,0x13,0x11};

int main() {

  MyUartDriver::UartDriver example0;
  example0.AddLayer(MyUartDriver::frame_header,0x11);
  example0.AddLayer(MyUartDriver::frame_data,2);
  example0.AddLayer(MyUartDriver::frame_end,0x10);

  for(auto i:test_data) {
    if(example0.GetOneByte(i)) {
      std::cout << "receive complete" << std::endl;
      std:: cout << "receive buf: ";
      for (auto data:example0.buf) {
        std:: cout << +data << " ";
      }
    }
  }

  return 0;
}
```
print out :

```
receive complete
receive buf: 16 17 2 19 
```

### example1.

> 0x11 , 0x12 , data1 , data2 , data3 , data4 , sum_check

```c++
INIT:
MyUartDriver::UartDriver example1;
example1.AddLayer(MyUartDriver::frame_header,0x11);
example1.AddLayer(MyUartDriver::frame_header,0x11);
example1.AddLayer(MyUartDriver::frame_data,4);
example1.AddLayer(MyUartDriver::frame_check);

USE:
if(example1.GetOneByte(INPUT_DATA))
{
    DEAL_CODE:
}
```

### example2.

> 0xFF , data_cnt , ***(data_cnt) , sum_check1 , sum_check2

```c++
INIT:
MyUartDriver::UartDriver example2;
example2.AddLayer(MyUartDriver::frame_header,0xFF);
example2.AddLayer(MyUartDriver::frame_cnt);
example2.AddLayer(MyUartDriver::frame_check);
example2.AddLayer(MyUartDriver::frame_check);

USE:
if(example2.GetOneByte(INPUT_DATA))
{
    DEAL_CODE:
}
```

