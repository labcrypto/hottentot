RTDIR=./runtime
MAJOR_VERSION = 1
MINOR_VERSION = 0

all:
	mkdir -p lib
	mkdir -p libd
	rm -rf lib/*
	rm -rf libd/*

	g++ -c -Wall -Wno-comment -fPIC -g $(RTDIR)/org/labcrypto/hottentot/runtime/configuration.cc -o libd/configuration.o	
	g++ -c -Wall -Wno-comment -fPIC -g $(RTDIR)/org/labcrypto/hottentot/runtime/logger.cc -o libd/logger.o
	g++ -c -Wall -Wno-comment -fPIC -g $(RTDIR)/org/labcrypto/hottentot/runtime/protocol_v1.cc -o libd/protocol_v1.o
	g++ -c -Wall -Wno-comment -fPIC -g $(RTDIR)/org/labcrypto/hottentot/runtime/proxy/proxy.cc -o libd/proxy.o
	g++ -c -Wall -Wno-comment -fPIC -g $(RTDIR)/org/labcrypto/hottentot/runtime/proxy/proxy_runtime.cc -o libd/proxy_runtime.o
	g++ -c -Wall -Wno-comment -fPIC -g $(RTDIR)/org/labcrypto/hottentot/runtime/proxy/default_tcp_client.cc -o libd/default_tcp_client.o
	g++ -c -Wall -Wno-comment -fPIC -g $(RTDIR)/org/labcrypto/hottentot/runtime/proxy/default_tcp_client_factory.cc -o libd/default_tcp_client_factory.o
	g++ -c -Wall -Wno-comment -fPIC -g $(RTDIR)/org/labcrypto/hottentot/runtime/service/service_runtime.cc -o libd/service_runtime.o
	g++ -c -Wall -Wno-comment -fPIC -g $(RTDIR)/org/labcrypto/hottentot/runtime/service/default_tcp_server.cc -o libd/default_tcp_server.o
	g++ -c -Wall -Wno-comment -fPIC -g $(RTDIR)/org/labcrypto/hottentot/runtime/service/default_tcp_server_factory.cc -o libd/default_tcp_server_factory.o
	g++ -c -Wall -Wno-comment -fPIC -g $(RTDIR)/org/labcrypto/hottentot/runtime/service/default_request_callback.cc -o libd/default_request_callback.o
	ar -cq libd/libhotd.a.$(MAJOR_VERSION).$(MINOR_VERSION) \
	   libd/configuration.o \
	   libd/logger.o \
	   libd/protocol_v1.o \
	   libd/proxy.o \
	   libd/proxy_runtime.o \
	   libd/default_tcp_client.o \
	   libd/default_tcp_client_factory.o \
	   libd/service_runtime.o \
	   libd/default_tcp_server.o \
	   libd/default_tcp_server_factory.o \
	   libd/default_request_callback.o
	g++ -shared -Wl,-soname,libhotd.so.$(MAJOR_VERSION) -o libd/libhotd.so.$(MAJOR_VERSION).$(MINOR_VERSION) \
	   libd/configuration.o \
	   libd/logger.o \
	   libd/protocol_v1.o \
	   libd/proxy.o \
	   libd/proxy_runtime.o \
	   libd/default_tcp_client.o \
	   libd/default_tcp_client_factory.o \
	   libd/service_runtime.o \
	   libd/default_tcp_server.o \
	   libd/default_tcp_server_factory.o \
	   libd/default_request_callback.o
	 	
	g++ -Wall -Wno-comment -fPIC -c $(RTDIR)/org/labcrypto/hottentot/runtime/configuration.cc -o lib/configuration.o
	g++ -Wall -Wno-comment -fPIC -c $(RTDIR)/org/labcrypto/hottentot/runtime/logger.cc -o lib/logger.o
	g++ -Wall -Wno-comment -fPIC -c $(RTDIR)/org/labcrypto/hottentot/runtime/protocol_v1.cc -o lib/protocol_v1.o
	g++ -Wall -Wno-comment -fPIC -c $(RTDIR)/org/labcrypto/hottentot/runtime/proxy/proxy.cc -o lib/proxy.o
	g++ -Wall -Wno-comment -fPIC -c $(RTDIR)/org/labcrypto/hottentot/runtime/proxy/proxy_runtime.cc -o lib/proxy_runtime.o
	g++ -Wall -Wno-comment -fPIC -c $(RTDIR)/org/labcrypto/hottentot/runtime/proxy/default_tcp_client.cc -o lib/default_tcp_client.o
	g++ -Wall -Wno-comment -fPIC -c $(RTDIR)/org/labcrypto/hottentot/runtime/proxy/default_tcp_client_factory.cc -o lib/default_tcp_client_factory.o
	g++ -Wall -Wno-comment -fPIC -c $(RTDIR)/org/labcrypto/hottentot/runtime/service/service_runtime.cc -o lib/service_runtime.o
	g++ -Wall -Wno-comment -fPIC -c $(RTDIR)/org/labcrypto/hottentot/runtime/service/default_tcp_server.cc -o lib/default_tcp_server.o
	g++ -Wall -Wno-comment -fPIC -c $(RTDIR)/org/labcrypto/hottentot/runtime/service/default_tcp_server_factory.cc -o lib/default_tcp_server_factory.o
	g++ -Wall -Wno-comment -fPIC -c $(RTDIR)/org/labcrypto/hottentot/runtime/service/default_request_callback.cc -o lib/default_request_callback.o
	ar -cq lib/libhot.a.$(MAJOR_VERSION).$(MINOR_VERSION) \
	   lib/configuration.o \
	   lib/logger.o \
	   lib/protocol_v1.o \
	   lib/proxy.o \
	   lib/proxy_runtime.o \
	   lib/default_tcp_client.o \
	   lib/default_tcp_client_factory.o \
	   lib/service_runtime.o \
	   lib/default_tcp_server.o \
	   lib/default_tcp_server_factory.o \
	   lib/default_request_callback.o
	g++ -shared -Wl,-soname,libhot.so.$(MAJOR_VERSION) -o lib/libhot.so.$(MAJOR_VERSION).$(MINOR_VERSION) \
	   lib/configuration.o \
	   lib/logger.o \
	   lib/protocol_v1.o \
	   lib/proxy.o \
	   lib/proxy_runtime.o \
	   lib/default_tcp_client.o \
	   lib/default_tcp_client_factory.o \
	   lib/service_runtime.o \
	   lib/default_tcp_server.o \
	   lib/default_tcp_server_factory.o \
	   lib/default_request_callback.o



