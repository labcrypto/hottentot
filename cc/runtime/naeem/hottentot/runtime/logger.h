#ifndef _NAEEM_HOTTENTOT_RUNTIME__LOGGER_H_
#define _NAEEM_HOTTENTOT_RUNTIME__LOGGER_H_

#include <iostream>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class Logger {
      public:
        static void Init();
        static std::ostream& GetOut();
        static std::ostream& GetError();
      private:
        static std::ostream *o_;
        static std::ostream *e_;
      };
    }
  }
}

#endif