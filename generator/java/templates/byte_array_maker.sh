#!/bin/bash
cat ./java/templates/abstractService.template > abstractServiceByteArray
xxd -i abstractServiceByteArray > ./java/templates/byte_arrays/abstractService.h
rm -rf abstractServiceByteArray

echo "std::string abstractServiceTmpStr(reinterpret_cast<char const *>(abstractServiceByteArray),
							         abstractServiceByteArray_len);" >> ./java/templates/byte_arrays/abstractService.h


cat ./java/templates/requestHandler.template > requestHandlerByteArray
xxd -i requestHandlerByteArray > ./java/templates/byte_arrays/requestHandler.h
rm -rf requestHandlerByteArray
echo "std::string requestHandlerTmpStr(reinterpret_cast<char const *>(requestHandlerByteArray),
							         requestHandlerByteArray_len);" >> ./java/templates/byte_arrays/requestHandler.h


cat ./java/templates/serviceProxyBuilder.template > serviceProxyBuilderByteArray
xxd -i serviceProxyBuilderByteArray > ./java/templates/byte_arrays/serviceProxyBuilder.h
rm -rf serviceProxyBuilderByteArray
echo "std::string serviceProxyBuilderTmpStr(reinterpret_cast<char const *>(serviceProxyBuilderByteArray),
							         serviceProxyBuilderByteArray_len);" >> ./java/templates/byte_arrays/serviceProxyBuilder.h


cat ./java/templates/serviceProxy.template > serviceProxyByteArray
xxd -i serviceProxyByteArray > ./java/templates/byte_arrays/serviceProxy.h
rm -rf serviceProxyByteArray
echo "std::string serviceProxyTmpStr(reinterpret_cast<char const *>(serviceProxyByteArray),
							         serviceProxyByteArray_len);" >>./java/templates/byte_arrays/serviceProxy.h


cat ./java/templates/service.template > serviceByteArray
xxd -i serviceByteArray > ./java/templates/byte_arrays/service.h
rm -rf serviceByteArray
echo "std::string serviceTmpStr(reinterpret_cast<char const *>(serviceByteArray),
							         serviceByteArray_len);" >> ./java/templates/byte_arrays/service.h


cat ./java/templates/struct.template > structByteArray
xxd -i structByteArray > ./java/templates/byte_arrays/struct.h
rm -rf structByteArray
echo "std::string structTmpStr(reinterpret_cast<char const *>(structByteArray),
							         structByteArray_len);" >> ./java/templates/byte_arrays/struct.h

cat ./java/templates/serializableStructList.template > serializableStructListByteArray
xxd -i serializableStructListByteArray > ./java/templates/byte_arrays/serializableStructList.h
rm -rf serializableStructListByteArray
echo "std::string serializableStructListTmpStr(reinterpret_cast<char const *>(serializableStructListByteArray),
							         structByteArray_len);" >> ./java/templates/byte_arrays/serializableStructList.h


