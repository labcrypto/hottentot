/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 05-02-2016 10:31:51
 * Name: calculator_service_impl.cc
 * Description:
 *   This file contains empty implementation of sample stub.
 ******************************************************************/
 
#include <naeem/hottentot/runtime/configuration.h>
#include <naeem/hottentot/runtime/logger.h>
#include <naeem/hottentot/runtime/utils.h>

#include "calculator_service_impl.h"




namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace calc {
  void
  CalculatorServiceImpl::OnInit() {
    // TODO: Called when service is initializing.
  }
  void
  CalculatorServiceImpl::OnShutdown() {
    // TODO: Called when service is shutting down.
  }
  void
  CalculatorServiceImpl::Add(::naeem::hottentot::runtime::types::UInt16 &a, ::naeem::hottentot::runtime::types::UInt16 &b, ::naeem::hottentot::runtime::types::UInt16 &out) {
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "CalculatorServiceImpl::Add() is called." << std::endl;
    }
    // TODO
  }
  void
  CalculatorServiceImpl::Mul(::naeem::hottentot::runtime::types::Int16 &a, ::naeem::hottentot::runtime::types::Int16 &b, ::naeem::hottentot::runtime::types::Int16 &out) {
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "CalculatorServiceImpl::Mul() is called." << std::endl;
    }
    // TODO
  }
} // END OF NAMESPACE calc
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir