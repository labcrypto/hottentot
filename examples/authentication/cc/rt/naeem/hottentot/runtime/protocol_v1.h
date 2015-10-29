#ifndef _NAEEM_HOTTENTOT_RUNTIME__PROTOCOL_V1_H_
#define _NAEEM_HOTTENTOT_RUNTIME__PROTOCOL_V1_H_

#include "protocol.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class ProtocolV1 : public Protocol {
      public:
        virtual unsigned char* SerializeRequest(Request *      /* Request object*/, 
                                                uint32_t *     /* Length */);
        virtual unsigned char* SerializeResponse(Response *    /* Response object*/, 
                                                 uint32_t *    /* Length */);
        virtual Response* DeserializeRequest(unsigned char *   /* Request data */, 
                                             uint32_t          /* Request data length */);
        virtual Response* DeserializeResponse(unsigned char *  /* Response data */, 
                                              uint32_t         /* Response data length */);
      public:
        virtual void ProcessDataForRequest(unsigned char *     /* Data chuck */,
                                           uint32_t            /* Data chunk length */);
        virtual void ProcessDataForResponse(unsigned char *    /* Data chuck */,
                                            uint32_t           /* Data chunk length */);
      };
    }
  }
}

#endif