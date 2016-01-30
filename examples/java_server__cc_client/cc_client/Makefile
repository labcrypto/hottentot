all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	mkdir -p lib/client
	mkdir -p lib/stub
	g++ -c -I/usr/local/include/hot token.cc -o lib/token.o
	g++ -c -I/usr/local/include/hot credential.cc -o lib/credential.o
	g++ -c -I/usr/local/include/hot data_wrapper.cc -o lib/data_wrapper.o
	g++ -c -I/usr/local/include/hot string_wrapper.cc -o lib/string_wrapper.o
	g++ -c -I/usr/local/include/hot sample_struct.cc -o lib/sample_struct.o
	g++ -c -I/usr/local/include/hot result.cc -o lib/result.o
	g++ -c -I/usr/local/include/hot proxy/test_service_proxy.cc -o lib/proxy/test_service_proxy.o
	g++ -c -I/usr/local/include/hot proxy/test_service_proxy_builder.cc -o lib/proxy/test_service_proxy_builder.o
	g++ -c -I/usr/local/include/hot service/test_service_request_handler.cc -o lib/service/test_service_request_handler.o
	g++ -c -I/usr/local/include/hot client/test_service_client.cc -o lib/client/test_service_client.o
	g++ lib/token.o lib/credential.o lib/data_wrapper.o lib/string_wrapper.o lib/sample_struct.o lib/result.o lib/proxy/test_service_proxy.o lib/proxy/test_service_proxy_builder.o lib/service/test_service_request_handler.o  lib/client/test_service_client.o  -lhotd -lpthread -o bin/test_service_client.out
	g++ -c -I/usr/local/include/hot stub/test_service_impl.cc -o lib/stub/test_service_impl.o
	g++ -c -I/usr/local/include/hot stub/test_service_server.cc -o lib/stub/test_service_server.o
	g++ lib/token.o lib/credential.o lib/data_wrapper.o lib/string_wrapper.o lib/sample_struct.o lib/result.o lib/proxy/test_service_proxy.o lib/proxy/test_service_proxy_builder.o lib/service/test_service_request_handler.o  lib/stub/test_service_impl.o lib/stub/test_service_server.o  -lhotd -lpthread -o bin/test_service_server.out
	./bin/test_service_client.out -v
