all:
	mkdir -p bin
	mkdir -p lib
	mkdir -p lib/proxy
	mkdir -p lib/service
	g++ -Wall -g -c -I/usr/local/include/hot person.cc -o lib/person.o
	g++ -Wall -g -c -I/usr/local/include/hot phone.cc -o lib/phone.o
	g++ -Wall -g -c -I/usr/local/include/hot proxy/person_authenticator_service_proxy.cc -o lib/proxy/person_authenticator_service_proxy.o
	g++ -Wall -g -c -I/usr/local/include/hot proxy/person_authenticator_service_proxy_builder.cc -o lib/proxy/person_authenticator_service_proxy_builder.o
	g++ -Wall -g -c -I/usr/local/include/hot service/person_authenticator_service_request_handler.cc -o lib/service/person_authenticator_service_request_handler.o
	g++ -Wall -g -c -I/usr/local/include/hot proxy/phone_manager_service_proxy.cc -o lib/proxy/phone_manager_service_proxy.o
	g++ -Wall -g -c -I/usr/local/include/hot proxy/phone_manager_service_proxy_builder.cc -o lib/proxy/phone_manager_service_proxy_builder.o
	g++ -Wall -g -c -I/usr/local/include/hot service/phone_manager_service_request_handler.cc -o lib/service/phone_manager_service_request_handler.o
	g++ -Wall -g -c -I/usr/local/include/hot license.cc -o lib/license.o
	g++ -Wall -g -c -I/usr/local/include/hot proxy/apache_license_manager_service_proxy.cc -o lib/proxy/apache_license_manager_service_proxy.o
	g++ -Wall -g -c -I/usr/local/include/hot proxy/apache_license_manager_service_proxy_builder.cc -o lib/proxy/apache_license_manager_service_proxy_builder.o
	g++ -Wall -g -c -I/usr/local/include/hot service/apache_license_manager_service_request_handler.cc -o lib/service/apache_license_manager_service_request_handler.o
