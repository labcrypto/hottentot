all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	mkdir -p lib/client
	mkdir -p lib/stub
	g++ -g -c -I/usr/local/include/hot gen/request_message.cc -o lib/request_message.o
	g++ -g -c -I/usr/local/include/hot gen/response_message.cc -o lib/response_message.o
	g++ -g -c -I/usr/local/include/hot gen/proxy/echo_service_proxy.cc -o lib/proxy/echo_service_proxy.o
	g++ -g -c -I/usr/local/include/hot gen/proxy/echo_service_proxy_builder.cc -o lib/proxy/echo_service_proxy_builder.o
	g++ -g -c -I/usr/local/include/hot gen/service/echo_service_request_handler.cc -o lib/service/echo_service_request_handler.o
	g++ -g -c -I/usr/local/include/hot client/echo_service_client.cc -o lib/client/echo_service_client.o
	g++ lib/request_message.o lib/response_message.o lib/proxy/echo_service_proxy.o lib/proxy/echo_service_proxy_builder.o lib/service/echo_service_request_handler.o  lib/client/echo_service_client.o  -lhotd -lpthread -o bin/echo_service_client.out
	g++ -g -c -I/usr/local/include/hot stub/echo_service_impl.cc -o lib/stub/echo_service_impl.o
	g++ -g -c -I/usr/local/include/hot stub/echo_service_server.cc -o lib/stub/echo_service_server.o
	g++ lib/request_message.o lib/response_message.o lib/proxy/echo_service_proxy.o lib/proxy/echo_service_proxy_builder.o lib/service/echo_service_request_handler.o  lib/stub/echo_service_impl.o lib/stub/echo_service_server.o  -lhotd -lpthread -o bin/echo_service_server.out
