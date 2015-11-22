#!/bin/bash
cat abstractService.tmp > temp
xxd -i temp > abstractService.b

cat requestHandler.tmp > temp
xxd -i temp > requestHandler.b

cat serviceProxyBuilder.tmp > temp
xxd -i temp > serviceProxyBuilder.b

cat serviceProxy.tmp > temp
xxd -i temp > serviceProxy.b

cat service.tmp > temp
xxd -i temp > service.b

cat struct.tmp > temp
xxd -i temp > struct.b

rm temp