all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	mkdir -p lib/client
	mkdir -p lib/stub
	g++ -Wall -g -c -I/usr/local/include/hot credential.cc -o lib/credential.o
	g++ -Wall -g -c -I/usr/local/include/hot user.cc -o lib/user.o
	g++ -Wall -g -c -I/usr/local/include/hot token.cc -o lib/token.o
	g++ -Wall -g -c -I/usr/local/include/hot proxy/authenticate_service_proxy.cc -o lib/proxy/authenticate_service_proxy.o
	g++ -Wall -g -c -I/usr/local/include/hot proxy/authenticate_service_proxy_builder.cc -o lib/proxy/authenticate_service_proxy_builder.o
	g++ -Wall -g -c -I/usr/local/include/hot service/authenticate_service_request_handler.cc -o lib/service/authenticate_service_request_handler.o
	g++ -Wall -g -Wall -g -c -I/usr/local/include/hot client/authenticate_service_client.cc -o lib/client/authenticate_service_client.o
	g++ lib/credential.o lib/user.o lib/token.o lib/proxy/authenticate_service_proxy.o lib/proxy/authenticate_service_proxy_builder.o lib/service/authenticate_service_request_handler.o  lib/client/authenticate_service_client.o  -lhotd -lpthread -o bin/authenticate_service_client.out
	g++ -Wall -g -c -I/usr/local/include/hot stub/authenticate_service_impl.cc -o lib/stub/authenticate_service_impl.o
	g++ -Wall -g -c -I/usr/local/include/hot stub/authenticate_service_server.cc -o lib/stub/authenticate_service_server.o
	g++ lib/credential.o lib/user.o lib/token.o lib/proxy/authenticate_service_proxy.o lib/proxy/authenticate_service_proxy_builder.o lib/service/authenticate_service_request_handler.o  lib/stub/authenticate_service_impl.o lib/stub/authenticate_service_server.o  -lhotd -lpthread -o bin/authenticate_service_server.out
