all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	mkdir -p lib/client
	mkdir -p lib/stub
	g++ -Wall -g -c -I/usr/local/include/hot proxy/calculator_service_proxy.cc -o lib/proxy/calculator_service_proxy.o
	g++ -Wall -g -c -I/usr/local/include/hot proxy/calculator_service_proxy_builder.cc -o lib/proxy/calculator_service_proxy_builder.o
	g++ -Wall -g -c -I/usr/local/include/hot service/calculator_service_request_handler.cc -o lib/service/calculator_service_request_handler.o
	g++ -Wall -g -Wall -g -c -I/usr/local/include/hot client/calculator_service_client.cc -o lib/client/calculator_service_client.o
	g++ lib/proxy/calculator_service_proxy.o lib/proxy/calculator_service_proxy_builder.o lib/service/calculator_service_request_handler.o  lib/client/calculator_service_client.o  -lhotd -lpthread -o bin/calculator_service_client.out
	g++ -Wall -g -c -I/usr/local/include/hot stub/calculator_service_impl.cc -o lib/stub/calculator_service_impl.o
	g++ -Wall -g -c -I/usr/local/include/hot stub/calculator_service_server.cc -o lib/stub/calculator_service_server.o
	g++ lib/proxy/calculator_service_proxy.o lib/proxy/calculator_service_proxy_builder.o lib/service/calculator_service_request_handler.o  lib/stub/calculator_service_impl.o lib/stub/calculator_service_server.o  -lhotd -lpthread -o bin/calculator_service_server.out
