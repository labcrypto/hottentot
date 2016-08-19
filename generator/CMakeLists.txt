cmake_minimum_required(VERSION 2.8) 

project(hottentot_generator)

set(DEBUG_MODE ON CACHE  BOOL  "Debug mode is enable or disable -- adds -g and -O0 flags") 
set(BIN_NAME "generator" CACHE STRING "")
set(BIN_INSTALL_DIR "/usr/local/bin/" CACHE PATH "")

if(NOT DEBUG_MODE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O0 -g")
  add_definitions(-D__DEBUG__)
endif()

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR})

include_directories(${PROJECT_INCLUDE_DIR})
include_directories("/usr/include/")
include_directories("/usr/local/include/")
include_directories("/usr/include/hiredis")
include_directories("/usr/local/include/hiredis")

link_directories("/usr/local/lib")

if (APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-writable-strings -Wno-deprecated-register -Wno-unused-function")
elseif (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -Wno-unused-but-set-variable -Wno-sign-compare -Wno-unused-function")
endif()

set(CC_TEMPLATE_FILES
  "${PROJECT_SOURCE_DIR}/cc/templates/templates.h"
  "${PROJECT_SOURCE_DIR}/cc/templates/templates.cc"
)

add_custom_command(OUTPUT ${CC_TEMPLATE_FILES}
  COMMAND ./cc/templates/generate_templates_header.sh ./cc/templates/
  COMMAND ./java/templates/byte_array_maker.sh
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  VERBATIM
)

set(LEX_FILES
  "${PROJECT_SOURCE_DIR}/y.tab.cc"
  "${PROJECT_SOURCE_DIR}/lex.yy.cc"
)

add_custom_command(OUTPUT ${LEX_FILES}
  COMMAND yacc -d ./hot.y
  COMMAND flex hot.l
  COMMAND mv y.tab.c y.tab.cc
  COMMAND mv lex.yy.c lex.yy.cc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  VERBATIM
)

add_custom_target(make_cc_template_files DEPENDS ${CC_TEMPLATE_FILES})
add_custom_target(make_lex_files DEPENDS ${LEX_FILES})

add_library(hottentot-generator-common SHARED 
  ${PROJECT_SOURCE_DIR}/lex.yy.cc
  ${PROJECT_SOURCE_DIR}/runtime.cc
  ${PROJECT_SOURCE_DIR}/fasthash.cc
  ${PROJECT_SOURCE_DIR}/service.cc
  ${PROJECT_SOURCE_DIR}/method.cc
)

add_library(hottentot-generator-cc SHARED
  ${PROJECT_SOURCE_DIR}/cc/runtime.cc
  ${PROJECT_SOURCE_DIR}/cc/cc_generator.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_abstract_service_header.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_enums.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_interface.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_service_interface.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_proxy_header.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_proxy_cc.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_proxy_builder_header.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_proxy_builder_cc.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_request_handler_header.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_request_handler_cc.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_struct_header.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_struct_cc.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_makefile.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_client.cc
  ${PROJECT_SOURCE_DIR}/cc/generate_stub.cc
  ${PROJECT_SOURCE_DIR}/cc/templates/templates.cc
)

add_library(hottentot-generator-java SHARED
  ${PROJECT_SOURCE_DIR}/java/java_generator.cc
  ${PROJECT_SOURCE_DIR}/java/generate_abstract_service_java.cc
  ${PROJECT_SOURCE_DIR}/java/generate_structs_java.cc
  ${PROJECT_SOURCE_DIR}/java/generate_service_interface_java.cc
  ${PROJECT_SOURCE_DIR}/java/generate_request_handler_java.cc
  ${PROJECT_SOURCE_DIR}/java/generate_service_proxy_builder_java.cc
  ${PROJECT_SOURCE_DIR}/java/generate_service_proxy_java.cc
  ${PROJECT_SOURCE_DIR}/java/generate_serializable_struct_list_java.cc
  ${PROJECT_SOURCE_DIR}/java/generate_client_main_java.cc
  ${PROJECT_SOURCE_DIR}/java/generate_server_main_java.cc
  ${PROJECT_SOURCE_DIR}/java/generate_server_impls_java.cc
  ${PROJECT_SOURCE_DIR}/java/generate_enums_java.cc
)

add_executable(hot
  ${PROJECT_SOURCE_DIR}/y.tab.cc
)

target_link_libraries(hot
  hottentot-generator-common
  hottentot-generator-cc
  hottentot-generator-java
  fl
)

# target_link_libraries(rtbe pthread ev httpxx cares systemd)
# install(TARGETS rtbe
#   RUNTIME DESTINATION ${BIN_INSTALL_DIR}
#   LIBRARY DESTINATION /usr/local/lib/
#   ARCHIVE DESTINATION /usr/local/lib/)
