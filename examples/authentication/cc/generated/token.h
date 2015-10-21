#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__TOKEN_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__TOKEN_H_

#include <string>

#include <naeem/hottentot/serialization/serializable.h>


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        class Token : public ::naeem::hottentot::serialization::Serializable {
        public:
          Token() {}
          ~Token() {}
          inline std::string GetValue() const {
            return value_;
          }
          inline void SetValue(std::string value) {
            value_ = value;
          }
          virtual unsigned char * Serialize(uint32_t *  /* Pointer to length */);
        private:
          std::string value_;
        };
      }
    }
  }
}

#endif