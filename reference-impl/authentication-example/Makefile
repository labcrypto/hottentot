all:
	mkdir -p target
	g++ -c -I./cc generated/authenticate_service_proxy_builder.cc -o target/authenticate_service_proxy_builder.o
	g++ -c -I./cc generated/authenticate_service_proxy.cc -o target/authenticate_service_proxy.o
	g++ -c -I./cc client.cc -o target/client.o
	g++ -c cc/naeem/hottentot/runtime/proxy/proxy.cc -o target/proxy.o
	g++ target/authenticate_service_proxy_builder.o \
	    target/authenticate_service_proxy.o \
	    target/proxy.o \
	    target/client.o -o client
