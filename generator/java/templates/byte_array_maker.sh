#!/bin/bash
cat abstractService.template > abstractServiceByteArray
xxd -i abstractServiceByteArray > ./byte_arrays/abstractService.h
echo "std::string abstractServiceTmpStr(reinterpret_cast<char const *>(abstractServiceByteArray),
							         abstractServiceByteArray_len);" >> ./byte_arrays/abstractService.h


cat requestHandler.template > requestHandlerByteArray
xxd -i requestHandlerByteArray > ./byte_arrays/requestHandler.h
echo "std::string requestHandlerTmpStr(reinterpret_cast<char const *>(requestHandlerByteArray),
							         requestHandlerByteArray_len);" >> ./byte_arrays/requestHandler.h


cat serviceProxyBuilder.template > serviceProxyBuilderByteArray
xxd -i serviceProxyBuilderByteArray > ./byte_arrays/serviceProxyBuilder.h
echo "std::string serviceProxyBuilderTmpStr(reinterpret_cast<char const *>(serviceProxyBuilderByteArray),
							         serviceProxyBuilderByteArray_len);" >> ./byte_arrays/serviceProxyBuilder.h


cat serviceProxy.template > serviceProxyByteArray
xxd -i serviceProxyByteArray > ./byte_arrays/serviceProxy.h
echo "std::string serviceProxyTmpStr(reinterpret_cast<char const *>(serviceProxyByteArray),
							         serviceProxyByteArray_len);" >> ./byte_arrays/serviceProxy.h


cat service.template > serviceByteArray
xxd -i serviceByteArray > ./byte_arrays/service.h
echo "std::string serviceTmpStr(reinterpret_cast<char const *>(serviceByteArray),
							         serviceByteArray_len);" >> ./byte_arrays/service.h


cat struct.template > structByteArray
xxd -i structByteArray > ./byte_arrays/struct.h
echo "std::string structTmpStr(reinterpret_cast<char const *>(structByteArray),
							         structByteArray_len);" >> ./byte_arrays/struct.h


