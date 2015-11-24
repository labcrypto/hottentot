#!/bin/bash
cat abstractService.template > temp
xxd -i temp > ./byte_arrays/abstractService.c

cat requestHandler.template > temp
xxd -i temp > ./byte_arrays/requestHandler.c

cat serviceProxyBuilder.template > temp
xxd -i temp > ./byte_arrays/serviceProxyBuilder.c

cat serviceProxy.template > temp
xxd -i temp > ./byte_arrays/serviceProxy.c

cat service.template > temp
xxd -i temp > ./byte_arrays/service.c

cat struct.template > temp
xxd -i temp > ./byte_arrays/struct.c

rm temp