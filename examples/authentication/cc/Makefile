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

all:
	
	mkdir -p target

	g++ -c ../../../cc/runtime//naeem/hottentot/runtime/logger.cc -o target/logger.o
	g++ -c ../../../cc/runtime//naeem/hottentot/runtime/protocol_v1.cc -o target/protocol_v1.o

	g++ -c ../../../cc/runtime//naeem/hottentot/runtime/proxy/proxy.cc -o target/proxy.o
	g++ -c ../../../cc/runtime//naeem/hottentot/runtime/proxy/proxy_runtime.cc -o target/proxy_runtime.o
	g++ -c ../../../cc/runtime//naeem/hottentot/runtime/proxy/default_tcp_client.cc -o target/default_tcp_client.o
	g++ -c ../../../cc/runtime//naeem/hottentot/runtime/proxy/default_tcp_client_factory.cc -o target/default_tcp_client_factory.o

	g++ -c ../../../cc/runtime//naeem/hottentot/runtime/service/service_runtime.cc -o target/service_runtime.o
	g++ -c ../../../cc/runtime//naeem/hottentot/runtime/service/default_tcp_server.cc -o target/default_tcp_server.o
	g++ -c ../../../cc/runtime//naeem/hottentot/runtime/service/default_tcp_server_factory.cc -o target/default_tcp_server_factory.o
	g++ -c ../../../cc/runtime//naeem/hottentot/runtime/service/default_request_callback.cc -o target/default_request_callback.o

	g++ -c -I../../../cc/runtime/ generated/token.cc -o target/token.o
	g++ -c -I../../../cc/runtime/ generated/credential.cc -o target/credential.o
	g++ -c -I../../../cc/runtime/ generated/proxy/authenticate_service_proxy_builder.cc -o target/authenticate_service_proxy_builder.o
	g++ -c -I../../../cc/runtime/ generated/proxy/authenticate_service_proxy.cc -o target/authenticate_service_proxy.o
	g++ -c -I../../../cc/runtime/ generated/service/authenticate_service_request_handler.cc -o target/authenticate_service_request_handler.o

	g++ -c -I../../../cc/runtime/ client/client.cc -o target/client.o

	g++ -c -I../../../cc/runtime/ server/server.cc -o target/server.o
	g++ -c -I../../../cc/runtime/ server/authenticate_service_impl.cc -o target/authenticate_service_impl.o

	g++ target/authenticate_service_proxy_builder.o \
	    target/authenticate_service_proxy.o \
	    target/proxy.o \
	    target/client.o \
	    target/protocol_v1.o \
	    target/token.o \
	    target/credential.o \
	    target/default_tcp_client.o \
	    target/default_tcp_client_factory.o \
	    target/proxy_runtime.o \
	    target/logger.o \
	    -o client.out
	    
	g++ target/server.o \
	    target/service_runtime.o \
	    target/default_tcp_server.o \
	    target/default_tcp_server_factory.o \
	    target/default_request_callback.o \
	    target/protocol_v1.o \
	    target/token.o \
	    target/credential.o \
	    target/authenticate_service_request_handler.o \
	    target/authenticate_service_impl.o \
	    target/logger.o \
	    -lpthread \
	    -o server.out
