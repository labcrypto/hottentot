/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 03-12-2015 02:39:42
 * Name: echo_service_impl.cc
 * Description:
 *   This file contains empty implementation of sample stub.
 ******************************************************************/
 
#include <naeem/hottentot/runtime/utils.h>
 #include <naeem/hottentot/runtime/logger.h>

#include "echo_service_impl.h"

#include "../request_message.h"
#include "../response_message.h"


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace echoer {
  ResponseMessage*
  EchoServiceImpl::EchoMessage(RequestMessage *req) {
    ::naeem::hottentot::runtime::Logger::GetOut() << "EchoServiceImpl::EchoMessage() is called." << std::endl;
        return NULL;
  }
} // END OF NAMESPACE echoer
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir