#include "UartDriver.h"

using namespace MyUartDriver;

void UartDriver::AddLayer(size_t type, uint8_t val) {
  if(type==frame_data) {
    for(int i=0;i<val;i++)
      layer.emplace_back(type,0);
  }
  else
    layer.emplace_back(type,val);
}

bool UartDriver::GetOneByte(uint8_t val) {
  static int i;
  if(i==0) buf.clear();
  switch (layer[i].first) {
    case frame_header :
      if (val == layer[i++].second) {
        buf.push_back(val);
        if(i>=layer.size()) {i=0;return 1;}
        /*return  "get_frame_header";*/
        return 0;
      } else {
        buf.clear();
        i=0;
        /*return "frame_header_is_error";*/
        return 0;
      }

    case frame_end : {
      if (val == layer[i++].second) {
        buf.push_back(val);
        i=0;
        /*return  "get_frame_end_and_complete";*/
        return 1;
      } else {
        buf.clear();
        i=0;
        /*return "frame_end_is_error";*/
        return 0;
      }
    }

    case frame_check:
      buf.push_back(val);
      i++;
      if(i>=layer.size()) {i=0;/*return "get_frame_check_and_complete";*/return 1;}
      /*return "get_check";*/
      return 0;

    case frame_data:
      buf.push_back(val);
      i++;
      if(i>=layer.size()) {i=0;/*return "get_frame_data_and_complete";*/return 1;}
      /*return "get_one_data";*/
      return 0;

    case frame_cnt:
      buf.push_back(val);
      static int cnt_i=0;
      static bool even_visit=false;
      if(even_visit==0) {
        even_visit=true;
        cnt_i=val;
        if(cnt_i==0) {
          even_visit=false;
          i++;
          if(i>=layer.size()) {i=0;/*return "get_frame_cnt_and_cnt=0_and_complete";*/return 1;}
          /*return "get_frame_cnt_and_cnt=0";*/
          return 0;
        } else {
          /*return "get_frame_cnt";*/
          return 0;
        }
      } else {
        if(--cnt_i==0) {
          even_visit=false;
          i++;
          if(i>=layer.size()) {i=0;/*return "frame_cnt_get_one_data_and_complete";*/return 1;}
        }
      }
      /*return "frame_cnt_get_one_data";*/
      return 0;
    default:
      buf.clear();
      i=0;
      /*return "no_expect_error";*/
      return 0;
  }
}
//
//std::string UartDriver::GetOneByte(uint8_t val) {
//  static int i;
//  if(i==0) buf.clear();
//  switch (layer[i].first) {
//    case frame_header :
//      if (val == layer[i++].second) {
//        buf.push_back(val);
//        if(i>=layer.size()) {i=0;return "get_frame_header_and_complete";}
//        return  "get_frame_header";
//      } else {
//        buf.clear();
//        i=0;
//        return "frame_header_is_error";
//      }
//
//    case frame_end : {
//      if (val == layer[i++].second) {
//        buf.push_back(val);
//        i=0;
//        return  "get_frame_end_and_complete";
//      } else {
//        buf.clear();
//        i=0;
//        return "frame_end_is_error";
//      }
//    }
//
//    case frame_check:
//      buf.push_back(val);
//      i++;
//      if(i>=layer.size()) {i=0;return "get_frame_check_and_complete";}
//      return "get_check";
//
//    case frame_data:
//      buf.push_back(val);
//      i++;
//      if(i>=layer.size()) {i=0;return "get_frame_data_and_complete";}
//      return "get_one_data";
//
//    case frame_cnt:
//      buf.push_back(val);
//      static int cnt_i=0;
//      static bool even_visit=false;
//      if(even_visit==0) {
//        even_visit=true;
//        cnt_i=val;
//        if(cnt_i==0) {
//          even_visit=false;
//          i++;
//          if(i>=layer.size()) {i=0;return "get_frame_cnt_and_cnt=0_and_complete";}
//          return "get_frame_cnt_and_cnt=0";
//        } else {
//          return "get_frame_cnt";
//        }
//      } else {
//        if(--cnt_i==0) {
//          even_visit=false;
//          i++;
//          if(i>=layer.size()) {i=0;return "frame_cnt_get_one_data_and_complete";}
//        }
//      }
//      return "frame_cnt_get_one_data";
//    default:
//      buf.clear();
//      i=0;
//      return "no_expect_error";
//  }
//}