all:
	
	mkdir -p target

	g++ -c -I./cc generated/authenticate_service_proxy_builder.cc -o target/authenticate_service_proxy_builder.o
	g++ -c -I./cc generated/authenticate_service_proxy.cc -o target/authenticate_service_proxy.o
	g++ -c -I./cc client/client.cc -o target/client.o
	g++ -c -I./cc server/server.cc -o target/server.o
	g++ -c -I./cc server/authenticate_service_impl.cc -o target/authenticate_service_impl.o
	g++ -c cc/naeem/hottentot/runtime/proxy/proxy.cc -o target/proxy.o
	g++ -c cc/naeem/hottentot/runtime/service/htn_runtime.cc -o target/htn_runtime.o

	g++ target/authenticate_service_proxy_builder.o \
	    target/authenticate_service_proxy.o \
	    target/proxy.o \
	    target/client.o \
	    -o client.out
	    
	g++ target/server.o \
	    target/htn_runtime.o \
	    target/authenticate_service_impl.o \
	    -o server.out
