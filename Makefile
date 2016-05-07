PWD=$(shell pwd)
BinDir=/usr/local/bin
LibDir=/usr/local/lib
IncludeDir=/usr/local/include

MajorVersion=1
MinorVersion=0

all:
	make -C generator
	make -C runtimes/cc
install:
	rm -f $(BinDir)/hot
	ln -s $(PWD)/generator/hot /usr/local/bin/hot
	rm -f $(LibDir)/libhot.a
	rm -f $(LibDir)/libhot.so
	rm -f $(LibDir)/libhot.so.*
	rm -f $(LibDir)/libhotd.a
	rm -f $(LibDir)/libhotd.so
	rm -f $(LibDir)/libhotd.so.*
	ln -s $(PWD)/runtimes/cc/lib/libhot.a.1.0 $(LibDir)/libhot.a
	ln -s $(PWD)/runtimes/cc/lib/libhot.so.1.0 $(LibDir)/libhot.so
	ln -s $(PWD)/runtimes/cc/lib/libhot.so.1.0 $(LibDir)/libhot.so.1
	ln -s $(PWD)/runtimes/cc/lib/libhot.so.1.0 $(LibDir)/libhot.so.1.0
	ln -s $(PWD)/runtimes/cc/libd/libhotd.a.1.0 $(LibDir)/libhotd.a
	ln -s $(PWD)/runtimes/cc/libd/libhotd.so.1.0 $(LibDir)/libhotd.so
	ln -s $(PWD)/runtimes/cc/libd/libhotd.so.1.0 $(LibDir)/libhotd.so.1
	ln -s $(PWD)/runtimes/cc/libd/libhotd.so.1.0 $(LibDir)/libhotd.so.1.0
	rm -f $(IncludeDir)/hot
	ln -s $(PWD)/runtimes/cc/runtime $(IncludeDir)/hot
