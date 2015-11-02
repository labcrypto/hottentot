#include "logger.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      std::ostream *Logger::o_ = 0;
      std::ostream *Logger::e_ = 0;
      void 
      Logger::Init() {
        o_ = new std::ostream(std::cout.rdbuf());
        e_ = new std::ostream(std::cerr.rdbuf());
      }
      std::ostream& 
      Logger::GetOut() {
        return *o_;
      }
      std::ostream& 
      Logger::GetError() {
        return *e_;
      }
    }
  }
}