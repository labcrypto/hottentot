#ifndef _NAEEM_HOTTENTOT_RUNTIME__RESPONSE_H_
#define _NAEEM_HOTTENTOT_RUNTIME__RESPONSE_H_

#include <stdint.h>
#include <vector>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class Response {
      public:
        inline uint8_t GetStatusCode() const {
          return statusCode_;
        }
        inline void SetStatusCode(uint8_t statusCode) {
          statusCode_ = statusCode;
        }
        inline unsigned char* GetData() const {
          return data_;
        }
        inline void SetData(unsigned char *data) {
          data_ = data;
        }
        inline uint32_t GetDataLength() const {
          return dataLength_;
        }
        inline void SetDataLength(uint32_t dataLength) {
          dataLength_ = dataLength;
        }
      private:
        /*
         * Success = 0
         * Fault > 0
         */
        uint8_t statusCode_;
        unsigned char *data_;
        uint32_t dataLength_;
      };
    }
  }
}

#endif