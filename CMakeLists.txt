cmake_minimum_required(VERSION 2.8) 

project(hottentot_generator)

set(BIN_INSTALL_DIR "/usr/local/bin/" CACHE PATH "")

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
  "${PROJECT_SOURCE_DIR}/generator/cc/templates/templates.h"
  "${PROJECT_SOURCE_DIR}/generator/cc/templates/templates.cc"
)

add_custom_command(OUTPUT ${CC_TEMPLATE_FILES}
  COMMAND ./cc/templates/generate_templates_header.sh ./cc/templates/
  COMMAND ./java/templates/byte_array_maker.sh
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/generator
  VERBATIM
)

set(LEX_FILES
  "${PROJECT_SOURCE_DIR}/generator/y.tab.cc"
  "${PROJECT_SOURCE_DIR}/generator/lex.yy.cc"
)

add_custom_command(OUTPUT ${LEX_FILES}
  COMMAND yacc -d .hot.y
  COMMAND flex hot.l
  COMMAND mv y.tab.c y.tab.cc
  COMMAND mv lex.yy.c lex.yy.cc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/generator
  VERBATIM
)

add_custom_target(make_cc_template_files DEPENDS ${CC_TEMPLATE_FILES})
add_custom_target(make_lex_files DEPENDS ${LEX_FILES})

add_library(hottentot-generator-common SHARED 
  ${PROJECT_SOURCE_DIR}/generator/lex.yy.cc
  ${PROJECT_SOURCE_DIR}/generator/runtime.cc
  ${PROJECT_SOURCE_DIR}/generator/fasthash.cc
  ${PROJECT_SOURCE_DIR}/generator/service.cc
  ${PROJECT_SOURCE_DIR}/generator/method.cc
)

add_library(hottentot-generator-cc SHARED
  ${PROJECT_SOURCE_DIR}/generator/cc/runtime.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/cc_generator.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_abstract_service_header.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_enums.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_interface.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_service_interface.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_proxy_header.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_proxy_cc.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_proxy_builder_header.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_proxy_builder_cc.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_request_handler_header.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_request_handler_cc.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_struct_header.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_struct_cc.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_makefile.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_client.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/generate_stub.cc
  ${PROJECT_SOURCE_DIR}/generator/cc/templates/templates.cc
)

add_library(hottentot-generator-java SHARED
  ${PROJECT_SOURCE_DIR}/generator/java/java_generator.cc
  ${PROJECT_SOURCE_DIR}/generator/java/generate_abstract_service_java.cc
  ${PROJECT_SOURCE_DIR}/generator/java/generate_structs_java.cc
  ${PROJECT_SOURCE_DIR}/generator/java/generate_service_interface_java.cc
  ${PROJECT_SOURCE_DIR}/generator/java/generate_request_handler_java.cc
  ${PROJECT_SOURCE_DIR}/generator/java/generate_service_proxy_builder_java.cc
  ${PROJECT_SOURCE_DIR}/generator/java/generate_service_proxy_java.cc
  ${PROJECT_SOURCE_DIR}/generator/java/generate_serializable_struct_list_java.cc
  ${PROJECT_SOURCE_DIR}/generator/java/generate_client_main_java.cc
  ${PROJECT_SOURCE_DIR}/generator/java/generate_server_main_java.cc
  ${PROJECT_SOURCE_DIR}/generator/java/generate_server_impls_java.cc
  ${PROJECT_SOURCE_DIR}/generator/java/generate_enums_java.cc
)

add_executable(hot-exe
  ${PROJECT_SOURCE_DIR}/generator/y.tab.cc
)

target_compile_options(hottentot-generator-common PUBLIC -std=c++11 -O3)
target_compile_options(hottentot-generator-cc PUBLIC -std=c++11 -O3)
target_compile_options(hottentot-generator-java PUBLIC -std=c++11 -O3)
target_compile_options(hot-exe PUBLIC -std=c++11 -O3)

set_target_properties(hot-exe PROPERTIES RUNTIME_OUTPUT_NAME hot)

target_link_libraries(hot-exe
  hottentot-generator-common
  hottentot-generator-cc
  hottentot-generator-java
  fl
)

add_library(hot SHARED
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/configuration.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/logger.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/protocol_v1.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/proxy/proxy.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/proxy/proxy_runtime.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/proxy/default_tcp_client.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/proxy/default_tcp_client_factory.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/service_runtime.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/default_tcp_server.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/default_tcp_server_factory.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/default_request_callback.cc
)

target_compile_options(hot PUBLIC -std=c++11 -O3)

add_library(hotd SHARED
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/configuration.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/logger.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/protocol_v1.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/proxy/proxy.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/proxy/proxy_runtime.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/proxy/default_tcp_client.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/proxy/default_tcp_client_factory.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/service_runtime.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/default_tcp_server.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/default_tcp_server_factory.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/default_request_callback.cc
)

target_compile_options(hotd PUBLIC -std=c++11 -O0 -g)

# target_link_libraries(rtbe pthread ev httpxx cares systemd)
# install(TARGETS rtbe
#   RUNTIME DESTINATION ${BIN_INSTALL_DIR}
#   LIBRARY DESTINATION /usr/local/lib/
#   ARCHIVE DESTINATION /usr/local/lib/)
