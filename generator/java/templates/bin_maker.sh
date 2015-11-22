#!/bin/bash
cat abstractService.tmp > temp
xxd -i temp > ./byte_arrays/abstractService.b

cat requestHandler.tmp > temp
xxd -i temp > ./byte_arrays/requestHandler.b

cat serviceProxyBuilder.tmp > temp
xxd -i temp > ./byte_arrays/serviceProxyBuilder.b

cat serviceProxy.tmp > temp
xxd -i temp > ./byte_arrays/serviceProxy.b

cat service.tmp > temp
xxd -i temp > ./byte_arrays/service.b

cat struct.tmp > temp
xxd -i temp > ./byte_arrays/struct.b

rm temp