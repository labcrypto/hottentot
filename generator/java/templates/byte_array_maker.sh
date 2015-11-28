#!/bin/bash
cat ./java/templates/abstractService.template > abstractServiceByteArray
xxd -i abstractServiceByteArray > ./java/templates/byte_arrays/abstractService.h

echo "std::string abstractServiceTmpStr(reinterpret_cast<char const *>(abstractServiceByteArray),
							         abstractServiceByteArray_len);" >> ./java/templates/byte_arrays/abstractService.h


cat ./java/templates/requestHandler.template > requestHandlerByteArray
xxd -i requestHandlerByteArray > ./java/templates/byte_arrays/requestHandler.h
echo "std::string requestHandlerTmpStr(reinterpret_cast<char const *>(requestHandlerByteArray),
							         requestHandlerByteArray_len);" >> ./java/templates/byte_arrays/requestHandler.h


cat ./java/templates/serviceProxyBuilder.template > serviceProxyBuilderByteArray
xxd -i serviceProxyBuilderByteArray > ./java/templates/byte_arrays/serviceProxyBuilder.h
echo "std::string serviceProxyBuilderTmpStr(reinterpret_cast<char const *>(serviceProxyBuilderByteArray),
							         serviceProxyBuilderByteArray_len);" >> ./java/templates/byte_arrays/serviceProxyBuilder.h


cat ./java/templates/serviceProxy.template > serviceProxyByteArray
xxd -i serviceProxyByteArray > ./java/templates/byte_arrays/serviceProxy.h
echo "std::string serviceProxyTmpStr(reinterpret_cast<char const *>(serviceProxyByteArray),
							         serviceProxyByteArray_len);" >>./java/templates/byte_arrays/serviceProxy.h


cat ./java/templates/service.template > serviceByteArray
xxd -i serviceByteArray > ./java/templates/byte_arrays/service.h
echo "std::string serviceTmpStr(reinterpret_cast<char const *>(serviceByteArray),
							         serviceByteArray_len);" >> ./java/templates/byte_arrays/service.h


cat ./java/templates/struct.template > structByteArray
xxd -i structByteArray > ./java/templates/byte_arrays/struct.h
echo "std::string structTmpStr(reinterpret_cast<char const *>(structByteArray),
							         structByteArray_len);" >> ./java/templates/byte_arrays/struct.h


