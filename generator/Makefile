#  The MIT License (MIT)
#
#  Copyright (c) 2015 LabCrypto Org.
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#  
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#  
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.
#

compile: init c_cc c_java build_output


init:
	mkdir -p .lib
	./java/templates/byte_array_maker.sh
	./cc/templates/generate_templates_header.sh ./cc/templates/
	
	yacc -d hot.y
	g++ -c -g -Wno-write-strings y.tab.c -o .lib/y.tab.o
	flex hot.l
	
	g++ -c -g lex.yy.c -o .lib/lex.yy.o
	g++ -c -g runtime.cc -o .lib/runtime_common.o
	g++ -c -g fasthash.cc -o .lib/fasthash.o
	g++ -c -g service.cc -o .lib/service.o
	g++ -c -g method.cc -o .lib/method.o

c_cc:
	g++ -c -g cc/runtime.cc -o .lib/runtime.o
	g++ -c -g cc/cc_generator.cc -o .lib/cc_generator.o
	g++ -c -g cc/generate_abstract_service_header.cc -o .lib/generate_abstract_service_header.o
	g++ -c -g cc/generate_enums.cc -o .lib/generate_enums.o
	g++ -c -g cc/generate_interface.cc -o .lib/generate_interface.o
	g++ -c -g cc/generate_service_interface.cc -o .lib/generate_service_interface.o
	g++ -c -g cc/generate_proxy_header.cc -o .lib/generate_proxy_header.o
	g++ -c -g cc/generate_proxy_cc.cc -o .lib/generate_proxy_cc.o
	g++ -c -g cc/generate_proxy_builder_header.cc -o .lib/generate_proxy_builder_header.o
	g++ -c -g cc/generate_proxy_builder_cc.cc -o .lib/generate_proxy_builder_cc.o
	g++ -c -g cc/generate_request_handler_header.cc -o .lib/generate_request_handler_header.o
	g++ -c -g cc/generate_request_handler_cc.cc -o .lib/generate_request_handler_cc.o
	g++ -c -g cc/generate_struct_header.cc -o .lib/generate_struct_header.o
	g++ -c -g cc/generate_struct_cc.cc -o .lib/generate_struct_cc.o
	g++ -c -g cc/generate_makefile.cc -o .lib/generate_makefile.o
	g++ -c -g cc/generate_client.cc -o .lib/generate_client.o
	g++ -c -g cc/generate_stub.cc -o .lib/generate_stub.o
	g++ -c -g cc/templates/templates.cc -o .lib/templates.o
	
c_java:
	g++ -c -g java/java_generator.cc -o .lib/java_generator.o
	g++ -c -g java/generate_abstract_service_java.cc -o .lib/generate_abstract_service_java.o
	g++ -c -g java/generate_structs_java.cc -o .lib/generate_structs_java.o
	g++ -c -g java/generate_service_interface_java.cc -o .lib/generate_service_interface_java.o
	g++ -c -g java/generate_request_handler_java.cc -o .lib/generate_request_handler_java.o
	g++ -c -g java/generate_service_proxy_builder_java.cc -o .lib/generate_service_proxy_builder_java.o
	g++ -c -g java/generate_service_proxy_java.cc -o .lib/generate_service_proxy_java.o
	g++ -c -g java/generate_serializable_struct_list_java.cc -o .lib/generate_serializable_struct_list_java.o
	g++ -c -g java/generate_client_main_java.cc -o .lib/generate_client_main_java.o
	g++ -c -g java/generate_server_main_java.cc -o .lib/generate_server_main_java.o
	g++ -c -g java/generate_server_impls_java.cc -o .lib/generate_server_impls_java.o
	g++ -c -g java/generate_enums_java.cc -o .lib/generate_enums_java.o
	
build_output:
	g++ -g .lib/y.tab.o \
	    .lib/lex.yy.o \
	    .lib/templates.o \
	    .lib/fasthash.o \
	    .lib/service.o \
	    .lib/method.o \
	    .lib/runtime_common.o \
	    .lib/runtime.o \
	    .lib/cc_generator.o \
	    .lib/generate_abstract_service_header.o \
	    .lib/generate_enums.o \
	    .lib/generate_service_interface.o \
	    .lib/generate_interface.o \
	    .lib/generate_proxy_header.o \
	    .lib/generate_proxy_cc.o \
	    .lib/generate_proxy_builder_header.o \
	    .lib/generate_proxy_builder_cc.o \
	    .lib/generate_request_handler_header.o \
	    .lib/generate_request_handler_cc.o \
	    .lib/generate_struct_header.o \
	    .lib/generate_struct_cc.o \
	    .lib/generate_makefile.o \
	    .lib/generate_client.o \
	    .lib/generate_stub.o \
	    .lib/java_generator.o \
	    .lib/generate_structs_java.o \
	    .lib/generate_enums_java.o \
	    .lib/generate_abstract_service_java.o \
	    .lib/generate_service_interface_java.o \
	    .lib/generate_request_handler_java.o \
	    .lib/generate_service_proxy_builder_java.o \
	    .lib/generate_service_proxy_java.o \
	    .lib/generate_serializable_struct_list_java.o \
	    .lib/generate_client_main_java.o \
	    .lib/generate_server_main_java.o \
	    .lib/generate_server_impls_java.o \
	    -lfl -ll -o hot