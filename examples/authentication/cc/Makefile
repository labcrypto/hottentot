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
