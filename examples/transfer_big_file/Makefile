all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	mkdir -p lib/client
	mkdir -p lib/stub
	g++ -Wall -g -c -I/usr/local/include/hot proxy/big_file_transfer_service_proxy.cc -o lib/proxy/big_file_transfer_service_proxy.o
	g++ -Wall -g -c -I/usr/local/include/hot proxy/big_file_transfer_service_proxy_builder.cc -o lib/proxy/big_file_transfer_service_proxy_builder.o
	g++ -Wall -g -c -I/usr/local/include/hot service/big_file_transfer_service_request_handler.cc -o lib/service/big_file_transfer_service_request_handler.o
	g++ -Wall -g -c -I/usr/local/include/hot client/big_file_transfer_service_client.cc -o lib/client/big_file_transfer_service_client.o
	g++ lib/proxy/big_file_transfer_service_proxy.o lib/proxy/big_file_transfer_service_proxy_builder.o lib/service/big_file_transfer_service_request_handler.o  lib/client/big_file_transfer_service_client.o  -lhotd -lpthread -o bin/big_file_transfer_service_client.out
	g++ -Wall -g -c -I/usr/local/include/hot stub/big_file_transfer_service_impl.cc -o lib/stub/big_file_transfer_service_impl.o
	g++ -Wall -g -c -I/usr/local/include/hot stub/big_file_transfer_service_server.cc -o lib/stub/big_file_transfer_service_server.o
	g++ lib/proxy/big_file_transfer_service_proxy.o lib/proxy/big_file_transfer_service_proxy_builder.o lib/service/big_file_transfer_service_request_handler.o  lib/stub/big_file_transfer_service_impl.o lib/stub/big_file_transfer_service_server.o  -lhotd -lpthread -o bin/big_file_transfer_service_server.out
