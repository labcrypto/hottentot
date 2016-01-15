/****************************************************************************
 * Generated by Hottentot CC Generator
 * Date: 15-01-2016 04:23:09
 * Name: list_test_service_request_handler.cc
 * Description:
 *   This file contains implementation of service's request handler class.
 ****************************************************************************/
 
#include <string.h>

#include <naeem/hottentot/runtime/request.h>
#include <naeem/hottentot/runtime/response.h>

#include "list_test_service_request_handler.h"
#include "abstract_list_test_service.h"
#include "../list_test_service.h"
#include "../message.h"


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace listtest {
namespace service {
  void 
  ListTestServiceRequestHandler::HandleRequest(::naeem::hottentot::runtime::Request &request, ::naeem::hottentot::runtime::Response &response) {
    if (request.GetMethodId() == 4202985802) {
      ::ir::ntnaeem::hottentot::examples::listtest::service::AbstractListTestService *serviceObject = 
        dynamic_cast< ::ir::ntnaeem::hottentot::examples::listtest::service::AbstractListTestService*>(service_);
      /*
       * Deserialization and making input variables
       */
      ::naeem::hottentot::runtime::types::List< ::naeem::hottentot::runtime::types::Utf8String> names;
      names.Deserialize(request.GetArgumentData(0), request.GetArgumentLength(0));
      /*
       * Calling service method
       */
            serviceObject->AddNames(names);
      /*
       * Serializiation of returned object
       */
      uint32_t serializedDataLength = 0;
      unsigned char *serializedData = 0;
      response.SetStatusCode(0);
      response.SetData(serializedData);
      response.SetDataLength(serializedDataLength);
      return;
    }
    if (request.GetMethodId() == 2800820226) {
      ::ir::ntnaeem::hottentot::examples::listtest::service::AbstractListTestService *serviceObject = 
        dynamic_cast< ::ir::ntnaeem::hottentot::examples::listtest::service::AbstractListTestService*>(service_);
      /*
       * Deserialization and making input variables
       */
      /*
       * Calling service method
       */
      ::naeem::hottentot::runtime::types::List< ::naeem::hottentot::runtime::types::Utf8String> result;
      serviceObject->GetNames(result);
      /*
       * Serializiation of returned object
       */
      uint32_t serializedDataLength = 0;
      unsigned char *serializedData = result.Serialize(&serializedDataLength);

      response.SetStatusCode(0);
      response.SetData(serializedData);
      response.SetDataLength(serializedDataLength);
      return;
    }
    if (request.GetMethodId() == 1872129924) {
      ::ir::ntnaeem::hottentot::examples::listtest::service::AbstractListTestService *serviceObject = 
        dynamic_cast< ::ir::ntnaeem::hottentot::examples::listtest::service::AbstractListTestService*>(service_);
      /*
       * Deserialization and making input variables
       */
      /*
       * Calling service method
       */
      ::naeem::hottentot::runtime::types::List< ::ir::ntnaeem::hottentot::examples::listtest::Message> result;
      serviceObject->GetMessages(result);
      /*
       * Serializiation of returned object
       */
      uint32_t serializedDataLength = 0;
      unsigned char *serializedData = result.Serialize(&serializedDataLength);

      response.SetStatusCode(0);
      response.SetData(serializedData);
      response.SetDataLength(serializedDataLength);
      return;
    }
    if (request.GetMethodId() == 3626181027) {
      ::ir::ntnaeem::hottentot::examples::listtest::service::AbstractListTestService *serviceObject = 
        dynamic_cast< ::ir::ntnaeem::hottentot::examples::listtest::service::AbstractListTestService*>(service_);
      /*
       * Deserialization and making input variables
       */
      ::ir::ntnaeem::hottentot::examples::listtest::Message message;
      message.Deserialize(request.GetArgumentData(0), request.GetArgumentLength(0));
      /*
       * Calling service method
       */
            serviceObject->AddMessage(message);
      /*
       * Serializiation of returned object
       */
      uint32_t serializedDataLength = 0;
      unsigned char *serializedData = 0;
      response.SetStatusCode(0);
      response.SetData(serializedData);
      response.SetDataLength(serializedDataLength);
      return;
    }
    char errorMessage[] = "Method not found.";
    response.SetStatusCode(1);
    response.SetData((unsigned char*)errorMessage);
    response.SetDataLength(strlen(errorMessage));
  }
} // END OF NAMESPACE service
} // END OF NAMESPACE listtest
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir