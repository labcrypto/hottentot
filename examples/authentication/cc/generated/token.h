#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__TOKEN_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__TOKEN_H_

namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        class Token {
        public:
          Token() {}
          ~Token() {}
          inline std::string GetValue() const {
            return value_;
          }
          inline void SetValue(std::string value) {
            value_ = value;
          }
        private:
          std::string value_;
        };
      }
    }
  }
}

#endif