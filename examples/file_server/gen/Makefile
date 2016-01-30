all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	mkdir -p lib/client
	mkdir -p lib/stub
	g++ -c -I/usr/local/include/hot proxy/service_proxy.cc -o lib/proxy/service_proxy.o
	g++ -c -I/usr/local/include/hot proxy/service_proxy_builder.cc -o lib/proxy/service_proxy_builder.o
	g++ -c -I/usr/local/include/hot service/service_request_handler.cc -o lib/service/service_request_handler.o
	g++ -c -I/usr/local/include/hot client/service_client.cc -o lib/client/service_client.o
	g++ lib/proxy/service_proxy.o lib/proxy/service_proxy_builder.o lib/service/service_request_handler.o  lib/client/service_client.o  -lhotd -lpthread -o bin/service_client.out
	g++ -c -I/usr/local/include/hot stub/service_impl.cc -o lib/stub/service_impl.o
	g++ -c -I/usr/local/include/hot stub/service_server.cc -o lib/stub/service_server.o
	g++ lib/proxy/service_proxy.o lib/proxy/service_proxy_builder.o lib/service/service_request_handler.o  lib/stub/service_impl.o lib/stub/service_server.o  -lhotd -lpthread -o bin/service_server.out
