all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	mkdir -p lib/client
	mkdir -p lib/stub
	g++ -std=c++11 -Wall -g -c -I/usr/local/include/hot request_message.cc -o lib/request_message.o
	g++ -std=c++11 -Wall -g -c -I/usr/local/include/hot response_message.cc -o lib/response_message.o
	g++ -std=c++11 -Wall -g -c -I/usr/local/include/hot proxy/echo_service_proxy.cc -o lib/proxy/echo_service_proxy.o
	g++ -std=c++11 -Wall -g -c -I/usr/local/include/hot proxy/echo_service_proxy_builder.cc -o lib/proxy/echo_service_proxy_builder.o
	g++ -std=c++11 -Wall -g -c -I/usr/local/include/hot service/echo_service_request_handler.cc -o lib/service/echo_service_request_handler.o
	g++ -std=c++11 -Wall -g -c -I/usr/local/include/hot client/echo_service_client.cc -o lib/client/echo_service_client.o
	g++ lib/request_message.o lib/response_message.o lib/proxy/echo_service_proxy.o lib/proxy/echo_service_proxy_builder.o lib/service/echo_service_request_handler.o  lib/client/echo_service_client.o  -lhottentot-runtime-proxy-debug-lib -lhottentot-runtime-common-debug-lib -lpthread -o bin/echo_service_client.out
	g++ -std=c++11 -Wall -g -c -I/usr/local/include/hot stub/echo_service_impl.cc -o lib/stub/echo_service_impl.o
	g++ -std=c++11 -Wall -g -c -I/usr/local/include/hot stub/echo_service_server.cc -o lib/stub/echo_service_server.o
	g++ lib/request_message.o lib/response_message.o lib/proxy/echo_service_proxy.o lib/proxy/echo_service_proxy_builder.o lib/service/echo_service_request_handler.o  lib/stub/echo_service_impl.o lib/stub/echo_service_server.o -lhottentot-runtime-proxy-debug-lib -lhottentot-runtime-common-debug-lib -lhottentot-runtime-service-debug-lib -lpthread -o bin/echo_service_server.out
