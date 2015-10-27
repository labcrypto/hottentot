all:
	
	mkdir -p target

	g++ -c rt/naeem/hottentot/runtime/proxy/proxy.cc -o target/proxy.o

	g++ -c rt/naeem/hottentot/runtime/service/service_runtime.cc -o target/service_runtime.o
	g++ -c rt/naeem/hottentot/runtime/service/default_client_listener.cc -o target/default_client_listener.o

	g++ -c rt/naeem/hottentot/runtime/protocol_v1.cc -o target/protocol_v1.o
	g++ -c rt/naeem/hottentot/runtime/request_writer.cc -o target/request_writer.o
	g++ -c rt/naeem/hottentot/runtime/response_reader.cc -o target/response_reader.o

	g++ -c -I./rt generated/token.cc -o target/token.o
	g++ -c -I./rt generated/credential.cc -o target/credential.o
	g++ -c -I./rt generated/proxy/authenticate_service_proxy_builder.cc -o target/authenticate_service_proxy_builder.o
	g++ -c -I./rt generated/proxy/authenticate_service_proxy.cc -o target/authenticate_service_proxy.o

	g++ -c -I./rt client/client.cc -o target/client.o

	g++ -c -I./rt server/server.cc -o target/server.o
	g++ -c -I./rt server/authenticate_service_impl.cc -o target/authenticate_service_impl.o

	g++ target/authenticate_service_proxy_builder.o \
	    target/authenticate_service_proxy.o \
	    target/proxy.o \
	    target/client.o \
	    target/request_writer.o \
	    target/response_reader.o \
	    target/protocol_v1.o \
	    target/token.o \
	    target/credential.o \
	    -o client.out
	    
	g++ target/server.o \
	    target/htn_runtime.o \
	    target/authenticate_service_impl.o \
	    target/token.o \
	    target/credential.o \
	    -o server.out
