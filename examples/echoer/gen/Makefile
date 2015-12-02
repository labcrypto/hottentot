RTDIR = ../../cc/runtime
all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	mkdir -p lib/client
	mkdir -p lib/stub
	mkdir -p lib/runtime
	g++ -c $(RTDIR)/naeem/hottentot/runtime/logger.cc -o lib/runtime/logger.o
	g++ -c $(RTDIR)/naeem/hottentot/runtime/protocol_v1.cc -o lib/runtime/protocol_v1.o
	g++ -c $(RTDIR)/naeem/hottentot/runtime/proxy/proxy.cc -o lib/runtime/proxy.o
	g++ -c $(RTDIR)/naeem/hottentot/runtime/proxy/proxy_runtime.cc -o lib/runtime/proxy_runtime.o
	g++ -c $(RTDIR)/naeem/hottentot/runtime/proxy/default_tcp_client.cc -o lib/runtime/default_tcp_client.o
	g++ -c $(RTDIR)/naeem/hottentot/runtime/proxy/default_tcp_client_factory.cc -o lib/runtime/default_tcp_client_factory.o
	g++ -c $(RTDIR)/naeem/hottentot/runtime/service/service_runtime.cc -o lib/runtime/service_runtime.o
	g++ -c $(RTDIR)/naeem/hottentot/runtime/service/default_tcp_server.cc -o lib/runtime/default_tcp_server.o
	g++ -c $(RTDIR)/naeem/hottentot/runtime/service/default_tcp_server_factory.cc -o lib/runtime/default_tcp_server_factory.o
	g++ -c $(RTDIR)/naeem/hottentot/runtime/service/default_request_callback.cc -o lib/runtime/default_request_callback.o
	g++ -c -I$(RTDIR) request_message.cc -o lib/request_message.o
	g++ -c -I$(RTDIR) response_message.cc -o lib/response_message.o
	g++ -c -I$(RTDIR) proxy/echo_service_proxy.cc -o lib/proxy/echo_service_proxy.o
	g++ -c -I$(RTDIR) proxy/echo_service_proxy_builder.cc -o lib/proxy/echo_service_proxy_builder.o
	g++ -c -I$(RTDIR) service/echo_service_request_handler.cc -o lib/service/echo_service_request_handler.o
	g++ -c -I$(RTDIR) client/echo_service_client.cc -o lib/client/echo_service_client.o
	g++ lib/runtime/logger.o lib/runtime/protocol_v1.o lib/runtime/proxy.o lib/runtime/proxy_runtime.o lib/runtime/default_tcp_client.o lib/runtime/default_tcp_client_factory.o lib/runtime/service_runtime.o lib/runtime/default_tcp_server.o lib/runtime/default_tcp_server_factory.o lib/runtime/default_request_callback.o lib/request_message.o lib/response_message.o lib/proxy/echo_service_proxy.o lib/proxy/echo_service_proxy_builder.o lib/service/echo_service_request_handler.o  lib/client/echo_service_client.o  -lpthread -o bin/echo_service_client.out
	g++ -c -I$(RTDIR) stub/echo_service_impl.cc -o lib/stub/echo_service_impl.o
	g++ -c -I$(RTDIR) stub/echo_service_server.cc -o lib/stub/echo_service_server.o
	g++ lib/runtime/logger.o lib/runtime/protocol_v1.o lib/runtime/proxy.o lib/runtime/proxy_runtime.o lib/runtime/default_tcp_client.o lib/runtime/default_tcp_client_factory.o lib/runtime/service_runtime.o lib/runtime/default_tcp_server.o lib/runtime/default_tcp_server_factory.o lib/runtime/default_request_callback.o lib/request_message.o lib/response_message.o lib/proxy/echo_service_proxy.o lib/proxy/echo_service_proxy_builder.o lib/service/echo_service_request_handler.o  lib/stub/echo_service_impl.o lib/stub/echo_service_server.o  -lpthread -o bin/echo_service_server.out
