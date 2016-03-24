all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	mkdir -p lib/client
	mkdir -p lib/stub
	g++ --std=c++11 -Wall -g -c -I/usr/local/include/hot hotgen/proxy/hello_service_proxy.cc -o lib/proxy/hello_service_proxy.o
	g++ --std=c++11 -Wall -g -c -I/usr/local/include/hot hotgen/proxy/hello_service_proxy_builder.cc -o lib/proxy/hello_service_proxy_builder.o
	g++ --std=c++11 -Wall -g -c -I/usr/local/include/hot hotgen/service/hello_service_request_handler.cc -o lib/service/hello_service_request_handler.o
	g++ --std=c++11 -Wall -g -Wall -g -c -I/usr/local/include/hot client/hello_service_client.cc -o lib/client/hello_service_client.o
	g++ lib/proxy/hello_service_proxy.o lib/proxy/hello_service_proxy_builder.o lib/service/hello_service_request_handler.o  lib/client/hello_service_client.o  -lhotd -lpthread -o bin/hello_service_client.out
	g++ --std=c++11 -Wall -g -c -I/usr/local/include/hot server/hello_service_impl.cc -o lib/stub/hello_service_impl.o
	g++ --std=c++11 -Wall -g -c -I/usr/local/include/hot server/hello_service_server.cc -o lib/stub/hello_service_server.o
	g++ lib/proxy/hello_service_proxy.o lib/proxy/hello_service_proxy_builder.o lib/service/hello_service_request_handler.o  lib/stub/hello_service_impl.o lib/stub/hello_service_server.o  -lhotd -lpthread -o bin/hello_service_server.out
