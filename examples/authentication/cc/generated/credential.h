#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__CREDENTIAL_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__CREDENTIAL_H_

#include <string>

#include <naeem/hottentot/serialization/serializable.h>


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        class Credential : public ::naeem::hottentot::serialization::Serializable {
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
          virtual unsigned char * Serialize(uint32_t *    /* Pointer to length */);
          virtual Credential* Deserialize(unsigned char *   /* Data */,
                                          uint32_t          /* Data length */);
        private:
          std::string username_;
          std::string password_;
        };
      }
    }
  }
}

#endif