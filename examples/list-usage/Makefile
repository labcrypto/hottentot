all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	mkdir -p lib/client
	mkdir -p lib/stub
	g++ -g -c -I/usr/local/include/hot gen/message.cc -o lib/message.o
	g++ -g -c -I/usr/local/include/hot gen/proxy/list_test_service_proxy.cc -o lib/proxy/list_test_service_proxy.o
	g++ -g -c -I/usr/local/include/hot gen/proxy/list_test_service_proxy_builder.cc -o lib/proxy/list_test_service_proxy_builder.o
	g++ -g -c -I/usr/local/include/hot gen/service/list_test_service_request_handler.cc -o lib/service/list_test_service_request_handler.o
	g++ -g -c -I/usr/local/include/hot client/list_test_service_client.cc -o lib/client/list_test_service_client.o
	g++ lib/message.o lib/proxy/list_test_service_proxy.o lib/proxy/list_test_service_proxy_builder.o lib/service/list_test_service_request_handler.o  lib/client/list_test_service_client.o  -lhotd -lpthread -o bin/list_test_service_client.out
	g++ -g -c -I/usr/local/include/hot stub/list_test_service_impl.cc -o lib/stub/list_test_service_impl.o
	g++ -g -c -I/usr/local/include/hot stub/list_test_service_server.cc -o lib/stub/list_test_service_server.o
	g++ lib/message.o lib/proxy/list_test_service_proxy.o lib/proxy/list_test_service_proxy_builder.o lib/service/list_test_service_request_handler.o  lib/stub/list_test_service_impl.o lib/stub/list_test_service_server.o  -lhotd -lpthread -o bin/list_test_service_server.out
