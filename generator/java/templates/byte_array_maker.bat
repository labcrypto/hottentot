
type .\java\templates\abstractService.template > abstractServiceByteArray
java\templates\tools\xxd -i abstractServiceByteArray > .\java\templates\byte_arrays\abstractService.h
del abstractServiceByteArray
echo std::string abstractServiceTmpStr(reinterpret_cast<char const *>(abstractServiceByteArray), abstractServiceByteArray_len); >> .\java\templates\byte_arrays\abstractService.h

type .\java\templates\requestHandler.template > requestHandlerByteArray
java\templates\tools\xxd -i requestHandlerByteArray > .\java\templates\byte_arrays\requestHandler.h
del requestHandlerByteArray
echo std::string requestHandlerTmpStr(reinterpret_cast<char const *>(requestHandlerByteArray), requestHandlerByteArray_len); >> .\java\templates\byte_arrays\requestHandler.h


rem cat ./java/templates/serviceProxyBuilder.template > serviceProxyBuilderByteArray
rem xxd -i serviceProxyBuilderByteArray > ./java/templates/byte_arrays/serviceProxyBuilder.h
rem rm -rf serviceProxyBuilderByteArray
rem echo "std::string serviceProxyBuilderTmpStr(reinterpret_cast<char const *>(serviceProxyBuilderByteArray),
rem 							         serviceProxyBuilderByteArray_len);" >> ./java/templates/byte_arrays/serviceProxyBuilder.h
rem 
rem 
rem cat ./java/templates/serviceProxy.template > serviceProxyByteArray
rem xxd -i serviceProxyByteArray > ./java/templates/byte_arrays/serviceProxy.h
rem rm -rf serviceProxyByteArray
rem echo "std::string serviceProxyTmpStr(reinterpret_cast<char const *>(serviceProxyByteArray),
rem 							         serviceProxyByteArray_len);" >>./java/templates/byte_arrays/serviceProxy.h
rem 
rem 
rem cat ./java/templates/service.template > serviceByteArray
rem xxd -i serviceByteArray > ./java/templates/byte_arrays/service.h
rem rm -rf serviceByteArray
rem echo "std::string serviceTmpStr(reinterpret_cast<char const *>(serviceByteArray),
rem 							         serviceByteArray_len);" >> ./java/templates/byte_arrays/service.h
rem 
rem 
rem cat ./java/templates/struct.template > structByteArray
rem xxd -i structByteArray > ./java/templates/byte_arrays/struct.h
rem rm -rf structByteArray
rem echo "std::string structTmpStr(reinterpret_cast<char const *>(structByteArray),
rem 							         structByteArray_len);" >> ./java/templates/byte_arrays/struct.h
rem 
rem cat ./java/templates/serializableStructList.template > serializableStructListByteArray
rem xxd -i serializableStructListByteArray > ./java/templates/byte_arrays/serializableStructList.h
rem rm -rf serializableStructListByteArray
rem echo "std::string serializableStructListTmpStr(reinterpret_cast<char const *>(serializableStructListByteArray),
rem 							         serializableStructListByteArray_len);" >> ./java/templates/byte_arrays/serializableStructList.h
rem 
rem 
rem cat ./java/templates/client_main.template > clientMainByteArray
rem xxd -i clientMainByteArray > ./java/templates/byte_arrays/clientMain.h
rem rm -rf clientMainByteArray
rem echo "std::string clientMainTmpStr(reinterpret_cast<char const *>(clientMainByteArray),
rem 							         clientMainByteArray_len);" >> ./java/templates/byte_arrays/clientMain.h
rem 
rem 
rem cat ./java/templates/server_main.template > serverMainByteArray
rem xxd -i serverMainByteArray > ./java/templates/byte_arrays/serverMain.h
rem rm -rf serverMainByteArray
rem echo "std::string serverMainTmpStr(reinterpret_cast<char const *>(serverMainByteArray),
rem 							         serverMainByteArray_len);" >> ./java/templates/byte_arrays/serverMain.h
rem 
rem 
rem cat ./java/templates/server_impl.template > serverImplByteArray
rem xxd -i serverImplByteArray > ./java/templates/byte_arrays/serverImpl.h
rem rm -rf serverImplByteArray
rem echo "std::string serverImplTmpStr(reinterpret_cast<char const *>(serverImplByteArray),
rem 							         serverImplByteArray_len);" >> ./java/templates/byte_arrays/serverImpl.h
rem 
rem cat ./java/templates/enum.template > enumByteArray
rem xxd -i enumByteArray > ./java/templates/byte_arrays/enum.h
rem rm -rf enumByteArray
rem echo "std::string enumTmpStr(reinterpret_cast<char const *>(enumByteArray),
rem 							         enumByteArray_len);" >> ./java/templates/byte_arrays/enum.h
rem 
rem cat ./java/templates/pom.template > pomByteArray
rem xxd -i pomByteArray > ./java/templates/byte_arrays/pom.h
rem rm -rf pomByteArray
rem echo "std::string pomTmpStr(reinterpret_cast<char const *>(pomByteArray),
rem 							         pomByteArray_len);" >> ./java/templates/byte_arrays/pom.h
