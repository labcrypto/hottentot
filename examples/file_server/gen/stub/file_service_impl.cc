/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 11-01-2016 11:34:13
 * Name: file_service_impl.cc
 * Description:
 *   This file contains empty implementation of sample stub.
 ******************************************************************/
 
#include <naeem/hottentot/runtime/utils.h>
 #include <naeem/hottentot/runtime/logger.h>

#include "file_service_impl.h"




namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace file {
namespace server {
  void
  FileServiceImpl::UploadFile(::naeem::hottentot::runtime::types::Utf8String &fileName, ::naeem::hottentot::runtime::types::ByteArray &content) {
    ::naeem::hottentot::runtime::Logger::GetOut() << "FileServiceImpl::UploadFile() is called." << std::endl;
    // TODO
  }
  void
  FileServiceImpl::FileExists(::naeem::hottentot::runtime::types::Utf8String &fileName, ::naeem::hottentot::runtime::types::Boolean &out) {
    ::naeem::hottentot::runtime::Logger::GetOut() << "FileServiceImpl::FileExists() is called." << std::endl;
    // TODO
  }
  void
  FileServiceImpl::DownloadFile(::naeem::hottentot::runtime::types::Utf8String &fileName, ::naeem::hottentot::runtime::types::ByteArray &out) {
    ::naeem::hottentot::runtime::Logger::GetOut() << "FileServiceImpl::DownloadFile() is called." << std::endl;
    // TODO
  }
} // END OF NAMESPACE server
} // END OF NAMESPACE file
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir