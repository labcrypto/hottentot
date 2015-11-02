#ifndef _NAEEM_HOTTENTOT_RUNTIME__REQUEST_H_
#define _NAEEM_HOTTENTOT_RUNTIME__REQUEST_H_

#include <stdint.h>
#include <vector>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class _Argument {
      public:
        unsigned char *data_;
        uint32_t dataLength_;
      };
      class Request {
      public:
        enum RequestType {
          Unknown,
          ServiceListQuery,
          InvokeStateless,
          InvokeStateful
        };
      public:
        Request() {}
        ~Request() {}
        inline RequestType GetType() const {
          return type_;
        }
        inline void SetType(RequestType type) {
          type_ = type;
        }
        inline uint32_t GetServiceId() const {
          return serviceId_;
        }
        inline void SetServiceId(uint32_t serviceId) {
          serviceId_ = serviceId;
        }
        inline uint32_t GetMethodId() const {
          return methodId_;
        }
        inline void SetMethodId(uint32_t methodId) {
          methodId_ = methodId;
        }
        inline uint32_t GetArgumentCount() const {
          return argumentCount_;
        }
        inline void SetArgumentCount(uint32_t argumentCount) {
          argumentCount_ = argumentCount;
        }
        inline void AddArgument(unsigned char *data, uint32_t dataLength) {
          _Argument argument;
          argument.data_ = data;
          argument.dataLength_ = dataLength;
          args_.push_back(argument);
        }
        inline unsigned char* GetArgumentData(uint8_t index) {
          return args_[index].data_;
        }
        inline uint32_t GetArgumentDataLength(uint8_t index) {
          return args_[index].dataLength_;
        }
      private:
        RequestType type_;
        uint32_t serviceId_;
        uint32_t methodId_;
        uint32_t argumentCount_;
        std::vector<_Argument> args_;
      };
    }
  }
}

#endif