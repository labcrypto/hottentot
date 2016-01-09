all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	mkdir -p lib/client
	mkdir -p lib/stub
	g++ -c -I/usr/include/hot proxy/calculator_service_proxy.cc -o lib/proxy/calculator_service_proxy.o
	g++ -c -I/usr/include/hot proxy/calculator_service_proxy_builder.cc -o lib/proxy/calculator_service_proxy_builder.o
	g++ -c -I/usr/include/hot service/calculator_service_request_handler.cc -o lib/service/calculator_service_request_handler.o
	g++ -c -I/usr/include/hot client/calculator_service_client.cc -o lib/client/calculator_service_client.o
	g++ lib/proxy/calculator_service_proxy.o lib/proxy/calculator_service_proxy_builder.o lib/service/calculator_service_request_handler.o  lib/client/calculator_service_client.o  -lhotd -lpthread -o bin/calculator_service_client.out
	g++ -c -I/usr/include/hot stub/calculator_service_impl.cc -o lib/stub/calculator_service_impl.o
	g++ -c -I/usr/include/hot stub/calculator_service_server.cc -o lib/stub/calculator_service_server.o
	g++ lib/proxy/calculator_service_proxy.o lib/proxy/calculator_service_proxy_builder.o lib/service/calculator_service_request_handler.o  lib/stub/calculator_service_impl.o lib/stub/calculator_service_server.o  -lhotd -lpthread -o bin/calculator_service_server.out
