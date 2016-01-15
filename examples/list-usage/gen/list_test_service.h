/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 16-01-2016 12:46:41
 * Name: list_test_service.h
 * Description:
 *   This file contains definition of service interface.
 ***************************************************************/

#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_LISTTEST__PROXY__LIST_TEST_SERVICE_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_LISTTEST__PROXY__LIST_TEST_SERVICE_H_

#include <stdint.h>
#include <string>

#include <naeem/hottentot/runtime/types/primitives.h>

#include "message.h"


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace listtest {
  class ListTestService {
  public:
    virtual void AddNames(::naeem::hottentot::runtime::types::List< ::naeem::hottentot::runtime::types::Utf8String> &names) = 0;
    virtual void GetNames(::naeem::hottentot::runtime::types::List< ::naeem::hottentot::runtime::types::Utf8String> &out) = 0;
    virtual void GetMessages(::naeem::hottentot::runtime::types::List< ::ir::ntnaeem::hottentot::examples::listtest::Message> &out) = 0;
    virtual void AddMessage(::ir::ntnaeem::hottentot::examples::listtest::Message &message) = 0;
  };
} // END OF NAMESPACE listtest
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif