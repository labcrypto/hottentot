all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	mkdir -p lib/client
	mkdir -p lib/stub
	g++ -c -I/usr/local/include/hot proxy/file_service_proxy.cc -o lib/proxy/file_service_proxy.o
	g++ -c -I/usr/local/include/hot proxy/file_service_proxy_builder.cc -o lib/proxy/file_service_proxy_builder.o
	g++ -c -I/usr/local/include/hot service/file_service_request_handler.cc -o lib/service/file_service_request_handler.o
	g++ -c -I/usr/local/include/hot client/file_service_client.cc -o lib/client/file_service_client.o
	g++ lib/proxy/file_service_proxy.o lib/proxy/file_service_proxy_builder.o lib/service/file_service_request_handler.o  lib/client/file_service_client.o  -lhotd -lpthread -o bin/file_service_client.out
	g++ -c -I/usr/local/include/hot stub/file_service_impl.cc -o lib/stub/file_service_impl.o
	g++ -c -I/usr/local/include/hot stub/file_service_server.cc -o lib/stub/file_service_server.o
	g++ lib/proxy/file_service_proxy.o lib/proxy/file_service_proxy_builder.o lib/service/file_service_request_handler.o  lib/stub/file_service_impl.o lib/stub/file_service_server.o  -lhotd -lpthread -o bin/file_service_server.out
