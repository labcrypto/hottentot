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

set(CC_TEMPLATE_FILES
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/abstract_service_header.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/client.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/enums.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/interface.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_builder_cc.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_builder_header.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_cc.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_cc__method.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_cc__method_argument_serialization.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_cc__method_response_deserailization.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/proxy_header.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/request_handler_cc.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/request_handler_cc__method_if_clause.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/request_handler_header.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/server.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/service_impl_cc.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/service_impl_cc__method.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/service_impl_header.templpate"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/service_interface.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/struct_cc.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/struct_header.template"
#  "${PROJECT_SOURCE_DIR}/generator/cc/templates/struct_header__getter_and_setter.template"
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
  COMMAND yacc -d hot.y
  COMMAND flex hot.l
  COMMAND mv y.tab.c y.tab.cc
  COMMAND mv lex.yy.c lex.yy.cc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/generator
  VERBATIM
)

add_custom_target(make_cc_template_files DEPENDS ${CC_TEMPLATE_FILES})
add_custom_target(make_lex_files DEPENDS ${LEX_FILES})

add_library(hottentot-generator-common-lib SHARED 
  ${PROJECT_SOURCE_DIR}/generator/runtime.cc
  ${PROJECT_SOURCE_DIR}/generator/fasthash.cc
  ${PROJECT_SOURCE_DIR}/generator/service.cc
  ${PROJECT_SOURCE_DIR}/generator/method.cc
  ${PROJECT_SOURCE_DIR}/generator/os.cc
)

add_library(hottentot-generator-cc-lib SHARED
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

add_library(hottentot-generator-java-lib SHARED
  ${PROJECT_SOURCE_DIR}/generator/runtime.cc
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

add_executable(hot-executable
  ${PROJECT_SOURCE_DIR}/generator/lex.yy.cc
  ${PROJECT_SOURCE_DIR}/generator/y.tab.cc
)

target_compile_options(hottentot-generator-common-lib PUBLIC -std=c++11 -O3)
target_compile_options(hottentot-generator-cc-lib PUBLIC -std=c++11 -O3)
target_compile_options(hottentot-generator-java-lib PUBLIC -std=c++11 -O3)
target_compile_options(hot-executable PUBLIC -std=c++11 -O3)

set_target_properties(hottentot-generator-common-lib PROPERTIES OUTPUT_NAME hot-generator-common)
set_target_properties(hottentot-generator-cc-lib PROPERTIES OUTPUT_NAME hot-generator-cc)
set_target_properties(hottentot-generator-java-lib PROPERTIES OUTPUT_NAME hot-generator-java)
set_target_properties(hot-executable PROPERTIES RUNTIME_OUTPUT_NAME hot)

target_link_libraries(hot-executable
  hottentot-generator-common-lib
  hottentot-generator-cc-lib
  hottentot-generator-java-lib
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
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/plain_blocking_tcp_client_acceptor.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/default_client_acceptor_factory.cc
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
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/plain_blocking_tcp_client_acceptor.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/default_client_acceptor_factory.cc
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/service/default_request_callback.cc
)

target_compile_options(hotd PUBLIC -std=c++11 -O0 -g)

set(HEADERS 
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/boolean.h
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/configuration.h
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/configuration.h
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/configuration.h
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/configuration.h
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org/labcrypto/hottentot/runtime/configuration.h
)

install(DIRECTORY 
  ${PROJECT_SOURCE_DIR}/runtimes/cc/runtime/org 
  DESTINATION 
  ${HEADERS_INSTALL_DIR} 
  FILES_MATCHING 
  PATTERN "*.h"
)

install(TARGETS
  hottentot-generator-common-lib
  hottentot-generator-cc-lib
  hottentot-generator-java-lib
  hot
  hotd
  DESTINATION
  ${LIB_INSTALL_DIR}
)

install(TARGETS
  hot-executable
  DESTINATION
  ${BIN_INSTALL_DIR}
)

add_custom_target(uninstall
  COMMAND rm -rfv ${BIN_INSTALL_DIR}/hot
  COMMAND rm -rfv ${LIB_INSTALL_DIR}/libhot*
  COMMAND rm -rfv ${HEADERS_INSTALL_DIR}/org/labcrypto/hottentot
)
