#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__CREDENTIAL_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__CREDENTIAL_H_

#include <string>


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        class Credential {
        public:
          Credential() {}
          ~Credential() {}
          inline std::string GetUsername() const {
            return username_;
          }
          inline void SetUsername(std::string username) {
            username_ = username;
          }
          inline std::string GetPassword() const {
            return password_;
          }
          inline void SetPassword(std::string password) {
            password_ = password;
          }
        private:
          std::string username_;
          std::string password_;
        };
      }
    }
  }
}

#endif