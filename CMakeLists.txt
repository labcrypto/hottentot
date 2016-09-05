cmake_minimum_required(VERSION 2.8) 

project(LabCryptoOrg-hottentot)

if (APPLE)
  set(CMAKE_MACOSX_RPATH 1)
endif()

set(BIN_INSTALL_DIR "/usr/bin/" CACHE PATH "")
set(HEADERS_INSTALL_DIR "/usr/include")
set(LIB_INSTALL_DIR "/usr/lib")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})

link_directories("/usr/local/lib")
if (APPLE)
  link_directories("/opt/local/lib/")
endif()

if (APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-writable-strings -Wno-deprecated-register -Wno-unused-function")
elseif (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -Wno-unused-but-set-variable -Wno-sign-compare -Wno-unused-function")
endif()

set(CC_TEMPLATES_SOURCES
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/templates.h
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/templates.cc
)

set(CC_TEMPLATES
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/abstract_service_header.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/client.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/enums.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/interface.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_builder_cc.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_builder_header.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_cc.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_cc__method.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_cc__method_argument_serialization.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_cc__method_response_deserialization.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_header.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/request_handler_cc.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/request_handler_cc__method_if_clause.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/request_handler_header.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/server.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/service_impl_cc.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/service_impl_cc__method.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/service_impl_header.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/service_interface.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/struct_cc.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/struct_header.template
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/struct_header__getter_and_setter.template
)

add_custom_command(OUTPUT ${CC_TEMPLATES_SOURCES}
  COMMAND echo "Generating C++ templates ..."
  COMMAND ./cc/templates/generate_templates_header.sh ./cc/templates/
  COMMAND echo "C++ templates are generated."
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/generator
  VERBATIM
  DEPENDS ${CC_TEMPLATES}
)

add_custom_target(cc-templates DEPENDS ${CC_TEMPLATES_SOURCES})

add_library(hottentot-generator-cc-lib SHARED
  ${PROJECT_SOURCE_DIR}/generator/cc/runtime.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/cc_generator.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_abstract_service_header.cc
)

add_dependencies(hottentot-generator-cc-lib cc-templates)
