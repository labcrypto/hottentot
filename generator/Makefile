#  The MIT License (MIT)
#
#  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
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

compile:
	./java/templates/byte_array_maker.sh
	yacc -d hot.y
	g++ -c y.tab.c
	flex hot.l
	g++ -c lex.yy.c
	g++ -c cc/cc_generator.cc -o cc_generator.o
	g++ -c cc/generate_abstract_service_header.cc -o generate_abstract_service_header.o
	g++ -c cc/generate_service_interface.cc -o generate_service_interface.o
	g++ -c cc/generate_proxy_header.cc -o generate_proxy_header.o
	g++ -c cc/generate_proxy_cc.cc -o generate_proxy_cc.o
	g++ -c cc/generate_proxy_builder_header.cc -o generate_proxy_builder_header.o
	g++ -c cc/generate_proxy_builder_cc.cc -o generate_proxy_builder_cc.o
	g++ -c cc/generate_request_handler_header.cc -o generate_request_handler_header.o
	g++ -c cc/generate_request_handler_cc.cc -o generate_request_handler_cc.o
	g++ -c cc/generate_struct_header.cc -o generate_struct_header.o
	g++ -c cc/generate_struct_cc.cc -o generate_struct_cc.o
	g++ -c cc/generate_makefile.cc -o generate_makefile.o
	g++ -c cc/generate_client.cc -o generate_client.o
	g++ -c cc/generate_stub.cc -o generate_stub.o
	g++ -c java/java_generator.cc -o java_generator.o
	g++ -c dep/fasthash.cc -o fasthash.o
	g++ -c ds/service.cc -o service.o
	g++ -c ds/method.cc -o method.o
	g++ y.tab.o \
	    lex.yy.o \
	    cc_generator.o \
	    generate_abstract_service_header.o \
	    generate_service_interface.o \
	    generate_proxy_header.o \
	    generate_proxy_cc.o \
	    generate_proxy_builder_header.o \
	    generate_proxy_builder_cc.o \
	    generate_request_handler_header.o \
	    generate_request_handler_cc.o \
	    generate_struct_header.o \
	    generate_struct_cc.o \
	    generate_makefile.o \
	    generate_client.o \
	    generate_stub.o \
	    java_generator.o \
	    fasthash.o \
	    service.o \
	    method.o \
	    -lfl -ll -o hot

java: compile
	./hot --java --out ../examples/authentication/java/src/main/java/example/generated test3.hot
        #./hot --java --out /home/developer/Desktop/gen test3.hot
cc: compile
	./hot --cc --indent-with-spaces --number-of-spaces-used-for-indentation 2 --out gen --makefile --client --stub test2.hot
