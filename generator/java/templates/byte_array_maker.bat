
type .\java\templates\abstractService.template > abstractServiceByteArray
java\templates\tools\xxd -i abstractServiceByteArray > .\java\templates\byte_arrays\abstractService.h
del abstractServiceByteArray
echo std::string abstractServiceTmpStr(reinterpret_cast^<char const *^>(abstractServiceByteArray), abstractServiceByteArray_len); >> .\java\templates\byte_arrays\abstractService.h

type .\java\templates\requestHandler.template > requestHandlerByteArray
java\templates\tools\xxd -i requestHandlerByteArray > .\java\templates\byte_arrays\requestHandler.h
del requestHandlerByteArray
echo std::string requestHandlerTmpStr(reinterpret_cast^<char const *^>(requestHandlerByteArray), requestHandlerByteArray_len); >> .\java\templates\byte_arrays\requestHandler.h

type .\java\templates\serviceProxyBuilder.template > serviceProxyBuilderByteArray
java\templates\tools\xxd -i serviceProxyBuilderByteArray > .\java\templates\byte_arrays\serviceProxyBuilder.h
del serviceProxyBuilderByteArray
echo std::string serviceProxyBuilderTmpStr(reinterpret_cast^<char const *^>(serviceProxyBuilderByteArray), serviceProxyBuilderByteArray_len); >> .\java\templates\byte_arrays\serviceProxyBuilder.h

type .\java\templates\serviceProxy.template > serviceProxyByteArray
java\templates\tools\xxd -i serviceProxyByteArray > .\java\templates\byte_arrays\serviceProxy.h
del serviceProxyByteArray
echo std::string serviceProxyTmpStr(reinterpret_cast^<char const *^>(serviceProxyByteArray), serviceProxyByteArray_len); >>.\java\templates\byte_arrays\serviceProxy.h

type .\java\templates\service.template > serviceByteArray
java\templates\tools\xxd -i serviceByteArray > .\java\templates\byte_arrays\service.h
del serviceByteArray
echo std::string serviceTmpStr(reinterpret_cast^<char const *^>(serviceByteArray), serviceByteArray_len); >> .\java\templates\byte_arrays\service.h

type .\java\templates\struct.template > structByteArray
java\templates\tools\xxd -i structByteArray > .\java\templates\byte_arrays\struct.h
del structByteArray
echo std::string structTmpStr(reinterpret_cast^<char const *^>(structByteArray), structByteArray_len); >> .\java\templates\byte_arrays\struct.h

type .\java\templates\serializableStructList.template > serializableStructListByteArray
java\templates\tools\xxd -i serializableStructListByteArray > .\java\templates\byte_arrays\serializableStructList.h
del serializableStructListByteArray
echo std::string serializableStructListTmpStr(reinterpret_cast^<char const *^>(serializableStructListByteArray), serializableStructListByteArray_len); >> .\java\templates\byte_arrays\serializableStructList.h

type .\java\templates\client_main.template > clientMainByteArray
java\templates\tools\xxd -i clientMainByteArray > .\java\templates\byte_arrays\clientMain.h
del clientMainByteArray
echo std::string clientMainTmpStr(reinterpret_cast^<char const *^>(clientMainByteArray), clientMainByteArray_len); >> .\java\templates\byte_arrays\clientMain.h

type .\java\templates\server_main.template > serverMainByteArray
java\templates\tools\xxd -i serverMainByteArray > .\java\templates\byte_arrays\serverMain.h
del serverMainByteArray
echo std::string serverMainTmpStr(reinterpret_cast^<char const *^>(serverMainByteArray), serverMainByteArray_len); >> .\java\templates\byte_arrays\serverMain.h

type .\java\templates\server_impl.template > serverImplByteArray
java\templates\tools\xxd -i serverImplByteArray > .\java\templates\byte_arrays\serverImpl.h
del serverImplByteArray
echo std::string serverImplTmpStr(reinterpret_cast^<char const *^>(serverImplByteArray), serverImplByteArray_len); >> .\java\templates\byte_arrays\serverImpl.h

type .\java\templates\enum.template > enumByteArray
java\templates\tools\xxd -i enumByteArray > .\java\templates\byte_arrays\enum.h
del enumByteArray
echo std::string enumTmpStr(reinterpret_cast^<char const *^>(enumByteArray), enumByteArray_len); >> .\java\templates\byte_arrays\enum.h

type .\java\templates\pom.template > pomByteArray
java\templates\tools\xxd -i pomByteArray > .\java\templates\byte_arrays\pom.h
del pomByteArray
echo std::string pomTmpStr(reinterpret_cast^<char const *^>(pomByteArray), pomByteArray_len); >> .\java\templates\byte_arrays\pom.h