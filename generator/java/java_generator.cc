/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTAB_STRILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include "java_generator.h"
#include "../ds/hot.h"
#include <stdint.h>
#include <sys/stat.h>

namespace naeem {
    namespace hottentot {
        namespace generator {
            namespace java {

                JavaGenerator::~JavaGenerator() {
                    for (int i = 0; i < modules_.size(); i++) {
                        ::naeem::hottentot::generator::ds::Module *pModule = modules_.at(i);
                        for (int j = 0; j < pModule->structs_.size(); j++) {
                            ::naeem::hottentot::generator::ds::Struct *pStruct = pModule->structs_.at(j);
                            for (int k = 0; k < pStruct->declarations_.size(); k++) {
                                delete pStruct->declarations_.at(k);
                            }
                            delete pStruct;
                        }
                        delete pModule;
                    }
                }

                JavaGenerator::JavaGenerator() {
                    for (int i = 0; i < TAB_SPACE_NUMBER; i++) {
                        TAB_STR += " ";
                    }
                    //MakeStringsFromByteArrays();
                    ReadTemplateFiles();
                }

                void
                JavaGenerator::Generate(::naeem::hottentot::generator::ds::Hot *hot,
                                        ::naeem::hottentot::generator::GenerationConfig &generationConfig) {

                    outDir_ = generationConfig.outDir_;
                    struct stat st = {0};
                    if (stat(outDir_.c_str(), &st) != 0) {
                        mkdir(outDir_.c_str(), 0777);
                    }

                    modules_ = hot->modules_;
                    for (int i = 0; i < modules_.size(); i++) {
                        ::naeem::hottentot::generator::ds::Module *pModule = modules_.at(i);
                        GenerateStructs(pModule);
                        GenerateAbstractService(pModule);
                        GenerateServiceInterface(pModule);
                        GenerateRequestHandler(pModule);
                        GenerateServiceProxyBuilder(pModule);
                        GenerateServiceProxy(pModule);

                    }
                    //std::cout << hot->GetModules().at(0)->GetMethod()-> << std::endl;
                    std::cout << "Java Generation done." << std::endl;
                }

                std::string
                JavaGenerator::ConvertType(std::string hotType){
                	std::string javaType;
                	if (hotType.compare("string") == 0) {
						javaType = "String";
					} else if (hotType.compare("int8") == 0 ||
					           hotType.compare("uint8") == 0) {
					    javaType = "short";
					} else if (hotType.compare("int16") == 0 ||
					           hotType.compare("uint16") == 0) {
					    javaType = "short";
					} else if (hotType.compare("int32") == 0 ||
					           hotType.compare("uint32") == 0) {
					    javaType = "int";
					} else if (hotType.compare("int64") == 0 ||
					           hotType.compare("uint64") == 0) {
					    javaType = "long";
					}
					return javaType;
                }


                std::string
                JavaGenerator::Capitalize(std::string str){
                	if(str[0] == 'S'){
                		return str;
                	}
                	std::string outputStr = str;
					outputStr[0] -= 32;
					return outputStr;
                }


                void
                JavaGenerator::MakeStringsFromByteArrays() {
                    //service proxy
                    unsigned char serviceProxyByteArray[] = {
                            0x70, 0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0x20, 0x5b, 0x25, 0x42, 0x41,
                            0x53, 0x45, 0x5f, 0x50, 0x41, 0x43, 0x4b, 0x41, 0x47, 0x45, 0x5f, 0x4e,
                            0x41, 0x4d, 0x45, 0x25, 0x5d, 0x3b, 0x0a, 0x0a, 0x69, 0x6d, 0x70, 0x6f,
                            0x72, 0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65,
                            0x6d, 0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e,
                            0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x41, 0x72, 0x67, 0x75,
                            0x6d, 0x65, 0x6e, 0x74, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74,
                            0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d, 0x2e,
                            0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72, 0x75,
                            0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x50, 0x72, 0x6f, 0x78, 0x79, 0x3b,
                            0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e,
                            0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d, 0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65,
                            0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65,
                            0x2e, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x3b, 0x0a, 0x69, 0x6d,
                            0x70, 0x6f, 0x72, 0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61,
                            0x65, 0x65, 0x6d, 0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f,
                            0x74, 0x2e, 0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x52, 0x65,
                            0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f,
                            0x72, 0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65,
                            0x6d, 0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e,
                            0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x54, 0x63, 0x70, 0x43,
                            0x6c, 0x69, 0x65, 0x6e, 0x74, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72,
                            0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d,
                            0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72,
                            0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x65, 0x78, 0x63, 0x65, 0x70,
                            0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x48, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74,
                            0x6f, 0x74, 0x52, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x45, 0x78, 0x63,
                            0x65, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f,
                            0x72, 0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65,
                            0x6d, 0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e,
                            0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x65, 0x78, 0x63, 0x65,
                            0x70, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x54, 0x63, 0x70, 0x43, 0x6c, 0x69,
                            0x65, 0x6e, 0x74, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x45, 0x78,
                            0x63, 0x65, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x69, 0x6d, 0x70,
                            0x6f, 0x72, 0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65,
                            0x65, 0x6d, 0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74,
                            0x2e, 0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x65, 0x78, 0x63,
                            0x65, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x54, 0x63, 0x70, 0x43, 0x6c,
                            0x69, 0x65, 0x6e, 0x74, 0x52, 0x65, 0x61, 0x64, 0x45, 0x78, 0x63, 0x65,
                            0x70, 0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72,
                            0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d,
                            0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72,
                            0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x65, 0x78, 0x63, 0x65, 0x70,
                            0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x54, 0x63, 0x70, 0x43, 0x6c, 0x69, 0x65,
                            0x6e, 0x74, 0x57, 0x72, 0x69, 0x74, 0x65, 0x45, 0x78, 0x63, 0x65, 0x70,
                            0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74,
                            0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d, 0x2e,
                            0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72, 0x75,
                            0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x66, 0x61, 0x63, 0x74, 0x6f, 0x72,
                            0x79, 0x2e, 0x50, 0x72, 0x6f, 0x74, 0x6f, 0x63, 0x6f, 0x6c, 0x46, 0x61,
                            0x63, 0x74, 0x6f, 0x72, 0x79, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72,
                            0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d,
                            0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72,
                            0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x66, 0x61, 0x63, 0x74, 0x6f,
                            0x72, 0x79, 0x2e, 0x54, 0x63, 0x70, 0x43, 0x6c, 0x69, 0x65, 0x6e, 0x74,
                            0x46, 0x61, 0x63, 0x74, 0x6f, 0x72, 0x79, 0x3b, 0x0a, 0x69, 0x6d, 0x70,
                            0x6f, 0x72, 0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65,
                            0x65, 0x6d, 0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74,
                            0x2e, 0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x70, 0x72, 0x6f,
                            0x74, 0x6f, 0x63, 0x6f, 0x6c, 0x2e, 0x50, 0x72, 0x6f, 0x74, 0x6f, 0x63,
                            0x6f, 0x6c, 0x3b, 0x0a, 0x0a, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x20,
                            0x63, 0x6c, 0x61, 0x73, 0x73, 0x20, 0x5b, 0x25, 0x53, 0x45, 0x52, 0x56,
                            0x49, 0x43, 0x45, 0x5f, 0x4e, 0x41, 0x4d, 0x45, 0x25, 0x5d, 0x53, 0x65,
                            0x72, 0x76, 0x69, 0x63, 0x65, 0x50, 0x72, 0x6f, 0x78, 0x79, 0x20, 0x65,
                            0x78, 0x74, 0x65, 0x6e, 0x64, 0x73, 0x20, 0x41, 0x62, 0x73, 0x74, 0x72,
                            0x61, 0x63, 0x74, 0x5b, 0x25, 0x53, 0x45, 0x52, 0x56, 0x49, 0x43, 0x45,
                            0x5f, 0x4e, 0x41, 0x4d, 0x45, 0x25, 0x5d, 0x53, 0x65, 0x72, 0x76, 0x69,
                            0x63, 0x65, 0x20, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74,
                            0x73, 0x20, 0x50, 0x72, 0x6f, 0x78, 0x79, 0x20, 0x7b, 0x0a, 0x09, 0x0a,
                            0x09, 0x70, 0x72, 0x69, 0x76, 0x61, 0x74, 0x65, 0x20, 0x53, 0x74, 0x72,
                            0x69, 0x6e, 0x67, 0x20, 0x68, 0x6f, 0x73, 0x74, 0x3b, 0x0a, 0x09, 0x70,
                            0x72, 0x69, 0x76, 0x61, 0x74, 0x65, 0x20, 0x69, 0x6e, 0x74, 0x20, 0x70,
                            0x6f, 0x72, 0x74, 0x3b, 0x0a, 0x0a, 0x09, 0x70, 0x75, 0x62, 0x6c, 0x69,
                            0x63, 0x20, 0x5b, 0x25, 0x53, 0x45, 0x52, 0x56, 0x49, 0x43, 0x45, 0x5f,
                            0x4e, 0x41, 0x4d, 0x45, 0x25, 0x5d, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63,
                            0x65, 0x50, 0x72, 0x6f, 0x78, 0x79, 0x28, 0x53, 0x74, 0x72, 0x69, 0x6e,
                            0x67, 0x20, 0x68, 0x6f, 0x73, 0x74, 0x2c, 0x20, 0x69, 0x6e, 0x74, 0x20,
                            0x70, 0x6f, 0x72, 0x74, 0x29, 0x20, 0x7b, 0x0a, 0x09, 0x09, 0x74, 0x68,
                            0x69, 0x73, 0x2e, 0x68, 0x6f, 0x73, 0x74, 0x20, 0x3d, 0x20, 0x68, 0x6f,
                            0x73, 0x74, 0x3b, 0x0a, 0x09, 0x09, 0x74, 0x68, 0x69, 0x73, 0x2e, 0x70,
                            0x6f, 0x72, 0x74, 0x20, 0x3d, 0x20, 0x70, 0x6f, 0x72, 0x74, 0x3b, 0x0a,
                            0x09, 0x7d, 0x0a, 0x09, 0x5b, 0x25, 0x4d, 0x45, 0x54, 0x48, 0x4f, 0x44,
                            0x53, 0x25, 0x5d, 0x0a, 0x09, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x20,
                            0x76, 0x6f, 0x69, 0x64, 0x20, 0x64, 0x65, 0x73, 0x74, 0x72, 0x6f, 0x79,
                            0x28, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                            0x20, 0x09, 0x2f, 0x2f, 0x54, 0x4f, 0x44, 0x4f, 0x0a, 0x09, 0x7d, 0x0a,
                            0x7d, 0x0a
                    };
                    uint32_t serviceProxyByteArrayLength = 1034;

                    unsigned char absractServiceByteArray[] = {
                            0x70, 0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0x20, 0x5b, 0x25, 0x42, 0x41,
                            0x53, 0x45, 0x5f, 0x50, 0x41, 0x43, 0x4b, 0x41, 0x47, 0x45, 0x5f, 0x4e,
                            0x41, 0x4d, 0x45, 0x25, 0x5d, 0x3b, 0x0a, 0x0a, 0x69, 0x6d, 0x70, 0x6f,
                            0x72, 0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65,
                            0x6d, 0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e,
                            0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x52, 0x65, 0x71, 0x75,
                            0x65, 0x73, 0x74, 0x48, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x72, 0x3b, 0x0a,
                            0x0a, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x20, 0x61, 0x62, 0x73, 0x74,
                            0x72, 0x61, 0x63, 0x74, 0x20, 0x63, 0x6c, 0x61, 0x73, 0x73, 0x20, 0x41,
                            0x62, 0x73, 0x74, 0x72, 0x61, 0x63, 0x74, 0x5b, 0x25, 0x53, 0x45, 0x52,
                            0x56, 0x49, 0x43, 0x45, 0x5f, 0x4e, 0x41, 0x4d, 0x45, 0x25, 0x5d, 0x53,
                            0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20, 0x69, 0x6d, 0x70, 0x6c, 0x65,
                            0x6d, 0x65, 0x6e, 0x74, 0x73, 0x20, 0x5b, 0x25, 0x53, 0x45, 0x52, 0x56,
                            0x49, 0x43, 0x45, 0x5f, 0x4e, 0x41, 0x4d, 0x45, 0x25, 0x5d, 0x53, 0x65,
                            0x72, 0x76, 0x69, 0x63, 0x65, 0x20, 0x7b, 0x09, 0x0a, 0x09, 0x70, 0x75,
                            0x62, 0x6c, 0x69, 0x63, 0x20, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74,
                            0x48, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x72, 0x20, 0x6d, 0x61, 0x6b, 0x65,
                            0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x48, 0x61, 0x6e, 0x64, 0x6c,
                            0x65, 0x72, 0x28, 0x29, 0x20, 0x7b, 0x0a, 0x09, 0x09, 0x72, 0x65, 0x74,
                            0x75, 0x72, 0x6e, 0x20, 0x6e, 0x65, 0x77, 0x20, 0x5b, 0x25, 0x53, 0x45,
                            0x52, 0x56, 0x49, 0x43, 0x45, 0x5f, 0x4e, 0x41, 0x4d, 0x45, 0x25, 0x5d,
                            0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x48, 0x61, 0x6e, 0x64, 0x6c,
                            0x65, 0x72, 0x28, 0x74, 0x68, 0x69, 0x73, 0x29, 0x3b, 0x0a, 0x09, 0x7d,
                            0x0a, 0x09, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x20, 0x69, 0x6e, 0x74,
                            0x20, 0x67, 0x65, 0x74, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x49,
                            0x64, 0x28, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                            0x20, 0x20, 0x09, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x5b, 0x25,
                            0x53, 0x45, 0x52, 0x56, 0x49, 0x43, 0x45, 0x5f, 0x49, 0x44, 0x25, 0x5d,
                            0x3b, 0x0a, 0x09, 0x7d, 0x0a, 0x7d, 0x0a
                    };
                    uint32_t absractServiceByteArrayLength = 343;

                    unsigned char requestHandlerByteArray[] = {
                            0x70, 0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0x20, 0x5b, 0x25, 0x42, 0x41,
                            0x53, 0x45, 0x5f, 0x50, 0x41, 0x43, 0x4b, 0x41, 0x47, 0x45, 0x5f, 0x4e,
                            0x41, 0x4d, 0x45, 0x25, 0x5d, 0x3b, 0x0a, 0x0a, 0x69, 0x6d, 0x70, 0x6f,
                            0x72, 0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65,
                            0x6d, 0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e,
                            0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x41, 0x72, 0x67, 0x75,
                            0x6d, 0x65, 0x6e, 0x74, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74,
                            0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d, 0x2e,
                            0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72, 0x75,
                            0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73,
                            0x74, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74, 0x20, 0x69, 0x72,
                            0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d, 0x2e, 0x68, 0x6f, 0x74,
                            0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72, 0x75, 0x6e, 0x74, 0x69,
                            0x6d, 0x65, 0x2e, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x48, 0x61,
                            0x6e, 0x64, 0x6c, 0x65, 0x72, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72,
                            0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d,
                            0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72,
                            0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x52, 0x65, 0x73, 0x70, 0x6f,
                            0x6e, 0x73, 0x65, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74, 0x20,
                            0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d, 0x2e, 0x68,
                            0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72, 0x75, 0x6e,
                            0x74, 0x69, 0x6d, 0x65, 0x2e, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65,
                            0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74, 0x20, 0x69, 0x72, 0x2e,
                            0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d, 0x2e, 0x68, 0x6f, 0x74, 0x74,
                            0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d,
                            0x65, 0x2e, 0x65, 0x78, 0x63, 0x65, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x2e,
                            0x4d, 0x65, 0x74, 0x68, 0x6f, 0x64, 0x4e, 0x6f, 0x74, 0x53, 0x75, 0x70,
                            0x70, 0x6f, 0x72, 0x74, 0x45, 0x78, 0x63, 0x65, 0x70, 0x74, 0x69, 0x6f,
                            0x6e, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74, 0x20, 0x69, 0x72,
                            0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d, 0x2e, 0x68, 0x6f, 0x74,
                            0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72, 0x75, 0x6e, 0x74, 0x69,
                            0x6d, 0x65, 0x2e, 0x65, 0x78, 0x63, 0x65, 0x70, 0x74, 0x69, 0x6f, 0x6e,
                            0x2e, 0x54, 0x63, 0x70, 0x43, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x43, 0x6f,
                            0x6e, 0x6e, 0x65, 0x63, 0x74, 0x45, 0x78, 0x63, 0x65, 0x70, 0x74, 0x69,
                            0x6f, 0x6e, 0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74, 0x20, 0x69,
                            0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d, 0x2e, 0x68, 0x6f,
                            0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72, 0x75, 0x6e, 0x74,
                            0x69, 0x6d, 0x65, 0x2e, 0x65, 0x78, 0x63, 0x65, 0x70, 0x74, 0x69, 0x6f,
                            0x6e, 0x2e, 0x54, 0x63, 0x70, 0x43, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x52,
                            0x65, 0x61, 0x64, 0x45, 0x78, 0x63, 0x65, 0x70, 0x74, 0x69, 0x6f, 0x6e,
                            0x3b, 0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74, 0x20, 0x69, 0x72, 0x2e,
                            0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65, 0x6d, 0x2e, 0x68, 0x6f, 0x74, 0x74,
                            0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e, 0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d,
                            0x65, 0x2e, 0x65, 0x78, 0x63, 0x65, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x2e,
                            0x54, 0x63, 0x70, 0x43, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x57, 0x72, 0x69,
                            0x74, 0x65, 0x45, 0x78, 0x63, 0x65, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x3b,
                            0x0a, 0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74, 0x20, 0x6a, 0x61, 0x76, 0x61,
                            0x2e, 0x75, 0x74, 0x69, 0x6c, 0x2e, 0x4c, 0x69, 0x73, 0x74, 0x3b, 0x0a,
                            0x0a, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x20, 0x63, 0x6c, 0x61, 0x73,
                            0x73, 0x20, 0x5b, 0x25, 0x53, 0x45, 0x52, 0x56, 0x49, 0x43, 0x45, 0x5f,
                            0x4e, 0x41, 0x4d, 0x45, 0x25, 0x5d, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73,
                            0x74, 0x48, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x72, 0x20, 0x65, 0x78, 0x74,
                            0x65, 0x6e, 0x64, 0x73, 0x20, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74,
                            0x48, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x72, 0x20, 0x7b, 0x0a, 0x20, 0x20,
                            0x20, 0x20, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x20, 0x5b, 0x25, 0x53,
                            0x45, 0x52, 0x56, 0x49, 0x43, 0x45, 0x5f, 0x4e, 0x41, 0x4d, 0x45, 0x25,
                            0x5d, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x48, 0x61, 0x6e, 0x64,
                            0x6c, 0x65, 0x72, 0x28, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20,
                            0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x29, 0x20, 0x7b, 0x0a, 0x20,
                            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x73, 0x75, 0x70, 0x65, 0x72,
                            0x28, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x29, 0x3b, 0x0a, 0x20,
                            0x20, 0x20, 0x20, 0x7d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x40, 0x4f, 0x76,
                            0x65, 0x72, 0x72, 0x69, 0x64, 0x65, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x70,
                            0x75, 0x62, 0x6c, 0x69, 0x63, 0x20, 0x52, 0x65, 0x73, 0x70, 0x6f, 0x6e,
                            0x73, 0x65, 0x20, 0x68, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x52, 0x65, 0x71,
                            0x75, 0x65, 0x73, 0x74, 0x28, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74,
                            0x20, 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x29, 0x20, 0x74, 0x68,
                            0x72, 0x6f, 0x77, 0x73, 0x20, 0x54, 0x63, 0x70, 0x43, 0x6c, 0x69, 0x65,
                            0x6e, 0x74, 0x57, 0x72, 0x69, 0x74, 0x65, 0x45, 0x78, 0x63, 0x65, 0x70,
                            0x74, 0x69, 0x6f, 0x6e, 0x2c, 0x20, 0x54, 0x63, 0x70, 0x43, 0x6c, 0x69,
                            0x65, 0x6e, 0x74, 0x52, 0x65, 0x61, 0x64, 0x45, 0x78, 0x63, 0x65, 0x70,
                            0x74, 0x69, 0x6f, 0x6e, 0x2c, 0x20, 0x54, 0x63, 0x70, 0x43, 0x6c, 0x69,
                            0x65, 0x6e, 0x74, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x45, 0x78,
                            0x63, 0x65, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x2c, 0x20, 0x4d, 0x65, 0x74,
                            0x68, 0x6f, 0x64, 0x4e, 0x6f, 0x74, 0x53, 0x75, 0x70, 0x70, 0x6f, 0x72,
                            0x74, 0x45, 0x78, 0x63, 0x65, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x7b,
                            0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x62, 0x79, 0x74,
                            0x65, 0x20, 0x6d, 0x65, 0x74, 0x68, 0x6f, 0x64, 0x49, 0x64, 0x20, 0x3d,
                            0x20, 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x2e, 0x67, 0x65, 0x74,
                            0x4d, 0x65, 0x74, 0x68, 0x6f, 0x64, 0x49, 0x64, 0x28, 0x29, 0x3b, 0x0a,
                            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5b, 0x25, 0x53, 0x45,
                            0x52, 0x56, 0x49, 0x43, 0x45, 0x5f, 0x4e, 0x41, 0x4d, 0x45, 0x25, 0x5d,
                            0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20, 0x5b, 0x25, 0x53, 0x45,
                            0x52, 0x56, 0x49, 0x43, 0x45, 0x5f, 0x4e, 0x41, 0x4d, 0x45, 0x5f, 0x4c,
                            0x4f, 0x57, 0x45, 0x52, 0x43, 0x41, 0x53, 0x45, 0x25, 0x5d, 0x49, 0x6d,
                            0x70, 0x6c, 0x20, 0x3d, 0x20, 0x28, 0x41, 0x62, 0x73, 0x74, 0x72, 0x61,
                            0x63, 0x74, 0x5b, 0x25, 0x53, 0x45, 0x52, 0x56, 0x49, 0x43, 0x45, 0x5f,
                            0x4e, 0x41, 0x4d, 0x45, 0x25, 0x5d, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63,
                            0x65, 0x29, 0x20, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x3b, 0x0a,
                            0x0a, 0x09, 0x5b, 0x25, 0x4d, 0x45, 0x54, 0x48, 0x4f, 0x44, 0x5f, 0x43,
                            0x4f, 0x4e, 0x44, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x53, 0x25, 0x5d, 0x0a,
                            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x68, 0x72, 0x6f,
                            0x77, 0x20, 0x6e, 0x65, 0x77, 0x20, 0x4d, 0x65, 0x74, 0x68, 0x6f, 0x64,
                            0x4e, 0x6f, 0x74, 0x53, 0x75, 0x70, 0x70, 0x6f, 0x72, 0x74, 0x45, 0x78,
                            0x63, 0x65, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x28, 0x22, 0x6d, 0x65, 0x74,
                            0x68, 0x6f, 0x64, 0x20, 0x69, 0x64, 0x20, 0x69, 0x73, 0x20, 0x69, 0x6e,
                            0x63, 0x6f, 0x72, 0x72, 0x65, 0x63, 0x74, 0x22, 0x29, 0x3b, 0x0a, 0x20,
                            0x20, 0x20, 0x20, 0x7d, 0x0a, 0x7d, 0x0a
                    };
                    uint32_t requestHandlerByteArrayLength = 1171;

                    unsigned char serviceByteArray[] = {
                            0x70, 0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0x20, 0x5b, 0x25, 0x42, 0x41,
                            0x53, 0x45, 0x5f, 0x50, 0x41, 0x43, 0x4b, 0x41, 0x47, 0x45, 0x5f, 0x4e,
                            0x41, 0x4d, 0x45, 0x25, 0x5d, 0x3b, 0x0a, 0x0a, 0x69, 0x6d, 0x70, 0x6f,
                            0x72, 0x74, 0x20, 0x69, 0x72, 0x2e, 0x6e, 0x74, 0x6e, 0x61, 0x65, 0x65,
                            0x6d, 0x2e, 0x68, 0x6f, 0x74, 0x74, 0x65, 0x6e, 0x74, 0x6f, 0x74, 0x2e,
                            0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x53, 0x65, 0x72, 0x76,
                            0x69, 0x63, 0x65, 0x3b, 0x0a, 0x0a, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63,
                            0x20, 0x69, 0x6e, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x20, 0x5b,
                            0x25, 0x53, 0x45, 0x52, 0x56, 0x49, 0x43, 0x45, 0x5f, 0x4e, 0x41, 0x4d,
                            0x45, 0x25, 0x5d, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20, 0x65,
                            0x78, 0x74, 0x65, 0x6e, 0x64, 0x73, 0x20, 0x53, 0x65, 0x72, 0x76, 0x69,
                            0x63, 0x65, 0x20, 0x7b, 0x0a, 0x5b, 0x25, 0x53, 0x45, 0x52, 0x56, 0x49,
                            0x43, 0x45, 0x5f, 0x4d, 0x45, 0x54, 0x48, 0x4f, 0x44, 0x53, 0x25, 0x5d,
                            0x0a, 0x7d, 0x0a
                    };
                    uint32_t serviceByteArrayLength = 159;

                    unsigned char serviceProxyBuilderByteArray[] = {
                            0x70, 0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0x20, 0x5b, 0x25, 0x42, 0x41,
                            0x53, 0x45, 0x5f, 0x50, 0x41, 0x43, 0x4b, 0x41, 0x47, 0x45, 0x5f, 0x4e,
                            0x41, 0x4d, 0x45, 0x25, 0x5d, 0x3b, 0x0a, 0x0a, 0x70, 0x75, 0x62, 0x6c,
                            0x69, 0x63, 0x20, 0x63, 0x6c, 0x61, 0x73, 0x73, 0x20, 0x5b, 0x25, 0x53,
                            0x45, 0x52, 0x56, 0x49, 0x43, 0x45, 0x5f, 0x4e, 0x41, 0x4d, 0x45, 0x25,
                            0x5d, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x50, 0x72, 0x6f, 0x78,
                            0x79, 0x42, 0x75, 0x69, 0x6c, 0x64, 0x65, 0x72, 0x20, 0x7b, 0x0a, 0x0a,
                            0x09, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x20, 0x73, 0x74, 0x61, 0x74,
                            0x69, 0x63, 0x20, 0x5b, 0x25, 0x53, 0x45, 0x52, 0x56, 0x49, 0x43, 0x45,
                            0x5f, 0x4e, 0x41, 0x4d, 0x45, 0x25, 0x5d, 0x53, 0x65, 0x72, 0x76, 0x69,
                            0x63, 0x65, 0x20, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x28, 0x53, 0x74,
                            0x72, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x6f, 0x73, 0x74, 0x2c, 0x20, 0x69,
                            0x6e, 0x74, 0x20, 0x70, 0x6f, 0x72, 0x74, 0x29, 0x20, 0x7b, 0x0a, 0x09,
                            0x09, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x6e, 0x65, 0x77, 0x20,
                            0x5b, 0x25, 0x53, 0x45, 0x52, 0x56, 0x49, 0x43, 0x45, 0x5f, 0x4e, 0x41,
                            0x4d, 0x45, 0x25, 0x5d, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x50,
                            0x72, 0x6f, 0x78, 0x79, 0x28, 0x68, 0x6f, 0x73, 0x74, 0x2c, 0x70, 0x6f,
                            0x72, 0x74, 0x29, 0x3b, 0x0a, 0x09, 0x7d, 0x0a, 0x0a, 0x20, 0x20, 0x20,
                            0x20, 0x09, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x20, 0x73, 0x74, 0x61,
                            0x74, 0x69, 0x63, 0x20, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x64, 0x65, 0x73,
                            0x74, 0x72, 0x6f, 0x79, 0x28, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20,
                            0x20, 0x20, 0x20, 0x20, 0x20, 0x09, 0x2f, 0x2f, 0x54, 0x4f, 0x44, 0x4f,
                            0x0a, 0x20, 0x20, 0x20, 0x20, 0x09, 0x7d, 0x0a, 0x7d, 0x0a
                    };
                    uint32_t serviceProxyBuilderByteArrayLength = 274;

                    unsigned char structByteArray[] = {
                            0x70, 0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0x20, 0x5b, 0x25, 0x42, 0x41,
                            0x53, 0x45, 0x5f, 0x50, 0x41, 0x43, 0x4b, 0x41, 0x47, 0x45, 0x5f, 0x4e,
                            0x41, 0x4d, 0x45, 0x25, 0x5d, 0x3b, 0x0a, 0x0a, 0x70, 0x75, 0x62, 0x6c,
                            0x69, 0x63, 0x20, 0x63, 0x6c, 0x61, 0x73, 0x73, 0x20, 0x5b, 0x25, 0x53,
                            0x54, 0x52, 0x55, 0x43, 0x54, 0x5f, 0x4e, 0x41, 0x4d, 0x45, 0x25, 0x5d,
                            0x20, 0x7b, 0x0a, 0x5b, 0x25, 0x4d, 0x45, 0x4d, 0x42, 0x45, 0x52, 0x53,
                            0x25, 0x5d, 0x09, 0x0a, 0x09, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x20,
                            0x62, 0x79, 0x74, 0x65, 0x5b, 0x5d, 0x20, 0x73, 0x65, 0x72, 0x69, 0x61,
                            0x6c, 0x69, 0x7a, 0x65, 0x28, 0x29, 0x20, 0x7b, 0x0a, 0x09, 0x09, 0x2f,
                            0x2f, 0x54, 0x4f, 0x44, 0x4f, 0x28, 0x61, 0x6c, 0x69, 0x29, 0x0a, 0x09,
                            0x09, 0x2f, 0x2f, 0x66, 0x61, 0x6b, 0x65, 0x20, 0x69, 0x6d, 0x70, 0x6c,
                            0x65, 0x6d, 0x65, 0x6e, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x0a, 0x09,
                            0x09, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x6e, 0x65, 0x77, 0x20,
                            0x62, 0x79, 0x74, 0x65, 0x5b, 0x5d, 0x7b, 0x20, 0x39, 0x37, 0x20, 0x7d,
                            0x3b, 0x0a, 0x09, 0x7d, 0x0a, 0x09, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63,
                            0x20, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x64, 0x65, 0x73, 0x65, 0x72, 0x69,
                            0x61, 0x6c, 0x69, 0x7a, 0x65, 0x28, 0x62, 0x79, 0x74, 0x65, 0x5b, 0x5d,
                            0x20, 0x73, 0x65, 0x72, 0x69, 0x61, 0x6c, 0x69, 0x7a, 0x65, 0x64, 0x54,
                            0x6f, 0x6b, 0x65, 0x6e, 0x29, 0x20, 0x7b, 0x0a, 0x09, 0x09, 0x2f, 0x2f,
                            0x54, 0x4f, 0x44, 0x4f, 0x28, 0x61, 0x6c, 0x69, 0x29, 0x0a, 0x09, 0x09,
                            0x2f, 0x2f, 0x66, 0x61, 0x6b, 0x65, 0x20, 0x69, 0x6d, 0x70, 0x6c, 0x65,
                            0x6d, 0x65, 0x6e, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x0a, 0x09, 0x09,
                            0x73, 0x65, 0x74, 0x56, 0x61, 0x6c, 0x75, 0x65, 0x28, 0x22, 0x74, 0x65,
                            0x73, 0x74, 0x2d, 0x74, 0x6f, 0x6b, 0x65, 0x6e, 0x22, 0x29, 0x3b, 0x0a,
                            0x09, 0x7d, 0x0a, 0x7d, 0x0a
                    };
                    uint32_t structByteArrayLength = 293;
                    //
                    std::string serviceProxyTmpStr(reinterpret_cast<char const *>(serviceProxyByteArray),
                                                   serviceProxyByteArrayLength);
                    serviceProxyTmpStr_ = serviceProxyTmpStr;

                    std::string abstractServiceTmpStr(reinterpret_cast<char const *>(absractServiceByteArray),
                                                      absractServiceByteArrayLength);
                    abstractServiceTmpStr_ = abstractServiceTmpStr;

                    std::string requestHandlerTmpStr(reinterpret_cast<char const *>(requestHandlerByteArray),
                                                     requestHandlerByteArrayLength);
                    requestHandlerTmpStr_ = requestHandlerTmpStr;

                    std::string serviceTmpStr(reinterpret_cast<char const *>(serviceByteArray), serviceByteArrayLength);
                    serviceTmpStr_ = serviceTmpStr;

                    std::string serviceProxyBuilderTmpStr(reinterpret_cast<char const *>(serviceProxyBuilderByteArray),
                                                          serviceProxyBuilderByteArrayLength);
                    serviceProxyBuilderTmpStr_ = serviceProxyBuilderTmpStr;

                    std::string structTmpStr(reinterpret_cast<char const *>(structByteArray), structByteArrayLength);
                    structTmpStr_ = structTmpStr;
                }

                void
                JavaGenerator::ReadTemplateFiles() {
                    //using the ds to write .hot file

                    //TODO use buffer reading
//			    char buffer[100];
//			    FILE* f = fopen("/home/developer/Desktop/templates/struct.tmp","rb");
//				std::string str;
//			    while(true){
//			        unsigned int r = fread(buffer , sizeof(char), 10 ,f);
//			        str += reinterpret_cast< char const* >(buffer);
//			        if(r == 0){
//			            break;
//			        }
//			    }
//
//			    fclose(f);
//			    f = fopen("/home/developer/Desktop/templates/new.tmp","wb");
//			    fwrite(str.c_str() , sizeof(char), str.length(),f);
//			    fclose(f);

                    is.open("/home/developer/projects/hottentot-git/generator/java/templates/struct.tmp", std::ios::in);
                    //TODO use buffer reader
                    char c;
                    while ((c = is.get()) != -1) {
                        structTmpStr_ += c;
                    }
                    is.close();
                    is.open("/home/developer/projects/hottentot-git/generator/java/templates/abstractService.tmp",
                            std::ios::in);
                    //TODO use buffer reader
                    while ((c = is.get()) != -1) {
                        abstractServiceTmpStr_ += c;
                    }
                    is.close();

                    //service interface
                    is.open("/home/developer/projects/hottentot-git/generator/java/templates/service.tmp",
                            std::ios::in);
                    //TODO use buffer reader
                    while ((c = is.get()) != -1) {
                        serviceTmpStr_ += c;
                    }
                    is.close();
                    //service proxy
                    is.open("/home/developer/projects/hottentot-git/generator/java/templates/serviceProxy.tmp",
                            std::ios::in);
                    while ((c = is.get()) != -1) {
                        serviceProxyTmpStr_ += c;
                    }
                    is.close();

                    //service proxy builder
                    is.open("/home/developer/projects/hottentot-git/generator/java/templates/serviceProxyBuilder.tmp",
                            std::ios::in);
                    //TODO use buffer reader
                    while ((c = is.get()) != -1) {
                        serviceProxyBuilderTmpStr_ += c;
                    }
                    is.close();

                    //request handler
                    is.open("/home/developer/projects/hottentot-git/generator/java/templates/requestHandler.tmp",
                            std::ios::in);
                    //TODO use buffer reader
                    while ((c = is.get()) != -1) {
                        requestHandlerTmpStr_ += c;
                    }
                    is.close();
//			std::cout << "---------------" << std::endl;
//			std::cout << structTmpStr_;
//			std::cout << abstractServiceTmpStr_;
//			std::cout << serviceTmpStr_;
//			std::cout << serviceProxyBuilderTmpStr_;
//			std::cout << serviceProxyTmpStr_;
//			std::cout << requestHandlerTmpStr_;
                }

                void
                JavaGenerator::GenerateStructs(::naeem::hottentot::generator::ds::Module *pModule) {
                    //loop on structs in everey module
                    //cout << structTmpStr << endl << "-----" << endl;
                    for (int i = 0; i < pModule->structs_.size(); i++) {
                        ::naeem::hottentot::generator::ds::Struct *pStruct = pModule->structs_.at(i);
                        std::string path = outDir_ + "/" + pStruct->name_.c_str() + ".java";
                        os.open(path.c_str(), std::ios::trunc);
                        std::string basePackageName = pModule->package_;
                        std::string replacableStructTmpStr = structTmpStr_;
                        while (replacableStructTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                            replacableStructTmpStr.replace(replacableStructTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                                                           basePackageName);
                        }
                        while (replacableStructTmpStr.find("[%STRUCT_NAME%]") != std::string::npos) {
                            replacableStructTmpStr.replace(replacableStructTmpStr.find("[%STRUCT_NAME%]"), 15,
                                                           pStruct->name_);
                        }
                        std::string declarationStr;
                        std::string getterSetterStr;

                        std::string declarationJavaType;
                        std::string capitalizedDeclarationJavaType;



                        for (int i = 0; i < pStruct->declarations_.size(); i++) {
                            //TODO change string to string
                            ::naeem::hottentot::generator::ds::Declaration *declarationPtr = pStruct->declarations_.at(
                                    i);

                            declarationJavaType = ConvertType(declarationPtr->type_);
                            declarationJavaType  = ConvertType(declarationPtr->type_);
                            std::string declarationName = declarationPtr->variable_;
                            std::string capitalizedDeclarationName = Capitalize(declarationPtr->variable_);
                            declarationStr +=
                                    TAB_STR + "private " + declarationPtr->type_ + " " + declarationName + ";\n";
                            getterSetterStr += TAB_STR + "public void set" + capitalizedDeclarationName + "(" +
                                               declarationPtr->type_ + " " + declarationName + ") {\n";
                            getterSetterStr +=
                                    TAB_STR + TAB_STR + "this." + declarationName + " = " + declarationName + ";\n";
                            getterSetterStr += TAB_STR + "}\n";
                            getterSetterStr +=
                                    TAB_STR + "public " + declarationPtr->type_ + " get" + capitalizedDeclarationName +
                                    "() {\n";
                            getterSetterStr += TAB_STR + TAB_STR + "return " + declarationPtr->variable_ + ";\n";
                            getterSetterStr += TAB_STR + "}\n";
                        }
                        replacableStructTmpStr.replace(replacableStructTmpStr.find("[%MEMBERS%]"), 11,
                                                       declarationStr + getterSetterStr);

                        //serilize method
                        std::string serializeMethodStr;
                        for (int i = 0; i < pStruct->declarations_.size(); i++) {
                            ::naeem::hottentot::generator::ds::Declaration *declarationPtr = pStruct->declarations_.at(
                                    i);
                            std::string capitalizedDeclarationName = Capitalize(declarationPtr->variable_);
                            serializeMethodStr += TAB_STR + TAB_STR + TAB_STR + "byte[] serialized" + capitalizedDeclarationName + " = PDTSerializer.get";
                            declarationJavaType = ConvertType(declarationPtr->type_);
                            capitalizedDeclarationJavaType = Capitalize(declarationJavaType);
                            std::cout << declarationJavaType;
                            //
                            serializeMethodStr += capitalizedDeclarationJavaType + "(";
                            serializeMethodStr += declarationPtr->variable_;
                            serializeMethodStr += capitalizedDeclarationJavaType + ");\n";
                        }
                        serializeMethodStr += TAB_STR + TAB_STR + TAB_STR + "byte[] output = new byte[";
                        for (int i = 0; i < pStruct->declarations_.size(); i++) {
                            ::naeem::hottentot::generator::ds::Declaration *declarationPtr = pStruct->declarations_.at(
                                    i);
                            std::string capitalizedDeclarationName = Capitalize(declarationPtr->variable_.c_str());
                            serializeMethodStr += "serialized" + capitalizedDeclarationName + ".length";
                            if (i == pStruct->declarations_.size() - 1) {
                                serializeMethodStr += "];\n";
                            } else {
                                serializeMethodStr += " + ";
                            }
                        }

                        serializeMethodStr += TAB_STR + TAB_STR + TAB_STR + "int counter = 0;\n";
                        serializeMethodStr += TAB_STR + TAB_STR + TAB_STR + "//use a loop for every property\n";
                        for (int i = 0; i < pStruct->declarations_.size(); i++) {
                            ::naeem::hottentot::generator::ds::Declaration *declarationPtr = pStruct->declarations_.at(
                                    i);
                            declarationJavaType = ConvertType(declarationPtr->type_);
                            capitalizedDeclarationJavaType = Capitalize(declarationJavaType);
                            serializeMethodStr += TAB_STR + TAB_STR + TAB_STR + "for (int i = 0; i < serialized" +
                                                  capitalizedDeclarationJavaType + ".length; i++) {\n";
                            serializeMethodStr += TAB_STR + TAB_STR + TAB_STR + TAB_STR + "output[counter++] = serialized" +
                                                  capitalizedDeclarationJavaType + "[i];\n";
                            serializeMethodStr += TAB_STR + TAB_STR + TAB_STR + "}\n";
                        }
                        serializeMethodStr += TAB_STR + TAB_STR + TAB_STR + "return output;";
                        //
                        replacableStructTmpStr.replace(replacableStructTmpStr.find("[%SERIALIZE_METHOD_BODY%]"), 25,
                                                       serializeMethodStr);
                        // sample code
                        //       byte[] serializedId = PDTSerializer.getInt16(id);
                        //       byte[] serializedValue = PDTSerializer.getString(value);
                        //       byte[] output = new byte[serializedId.length + serializedValue.length];
                        //       int counter = 0;
                        //       //use a loop for every property
                        //       for (int i = 0; i < serializedId.length; i++) {
                        //           output[counter++] = serializedId[i];
                        //       }
                        //       for (int i = 0; i < serializedValue.length; i++) {
                        //           output[counter++] = serializedValue[i];
                        //       }
                        //       return output;
                        os.write(replacableStructTmpStr.c_str(), replacableStructTmpStr.size());
                        os.close();
                    }
                }

                void
                JavaGenerator::GenerateAbstractService(::naeem::hottentot::generator::ds::Module *pModule) {
                    //loop for every services
                    ::naeem::hottentot::generator::ds::Service *pService;
                    std::string replacableAbstractServiceTmpStr;
                    for (int i = 0; i < pModule->services_.size(); i++) {
                        //write abstractService.tmp
                        std::string basePackageName = pModule->package_;
                        pService = pModule->services_.at(i);
                        std::string path = outDir_ + "/Abstract" + pService->name_.c_str() + "Service.java";
                        os.open(path.c_str(), std::ios::trunc);
                        replacableAbstractServiceTmpStr = abstractServiceTmpStr_;


                        while (replacableAbstractServiceTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                            replacableAbstractServiceTmpStr.replace(
                                    replacableAbstractServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
                        }
                        while (replacableAbstractServiceTmpStr.find("[%SERVICE_NAME%]") != std::string::npos) {
                            replacableAbstractServiceTmpStr.replace(
                                    replacableAbstractServiceTmpStr.find("[%SERVICE_NAME%]"), 16, pService->name_);
                        }
                        std::stringstream ssID;
                        //TODO get service ID from hot parser
                        //ssID << pService->id_;
                        ssID << "1";
                        replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%SERVICE_ID%]"),
                                                                14, ssID.str());
                        os.write(replacableAbstractServiceTmpStr.c_str(), replacableAbstractServiceTmpStr.size());
                        os.close();
                    }
                }

                void
                JavaGenerator::GenerateServiceInterface(::naeem::hottentot::generator::ds::Module *pModule) {
                    ::naeem::hottentot::generator::ds::Service *pService;
                    std::string replacableServiceTmpStr;
                    for (int i = 0; i < pModule->services_.size(); i++) {
                        //write abstractService.tmp
                        std::string basePackageName = pModule->package_;
                        pService = pModule->services_.at(i);
                        //write service interface
                        std::string replacableServiceTmpStr = serviceTmpStr_;
                        //std::cout << outDir_;
                        std::string path = outDir_ + "/" + pService->name_.c_str() + "Service.java";
                        os.open(path.c_str(), std::ios::trunc);
                        while (replacableServiceTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                            replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                                                            basePackageName);
                        }
                        while (replacableServiceTmpStr.find("[%SERVICE_NAME%]") != std::string::npos) {
                            replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%SERVICE_NAME%]"), 16,
                                                            pService->name_);
                        }
                        std::string serviceMethodsStr;
                        //loop for service methods
                        ::naeem::hottentot::generator::ds::Method *pMethod;
                        for (int i = 0; i < pService->methods_.size(); i++) {
                            pMethod = pService->methods_.at(i);
                            serviceMethodsStr += TAB_STR + "" + pMethod->returnType_ + " " + pMethod->name_ + "(";
                            //loop on methods arguments
                            ::naeem::hottentot::generator::ds::Argument *pArg;
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                pArg = pMethod->arguments_.at(i);
                                serviceMethodsStr += pArg->type_ + " " + pArg->variable_;
                                if (i < pMethod->arguments_.size() - 1) {
                                    serviceMethodsStr += ",";
                                }
                            }
                            serviceMethodsStr += ");";
                        };
                        replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%SERVICE_METHODS%]"), 19,
                                                        serviceMethodsStr);
                        os.write(replacableServiceTmpStr.c_str(), replacableServiceTmpStr.size());
                        os.close();

                    }
                }

                void
                JavaGenerator::GenerateServiceProxyBuilder(::naeem::hottentot::generator::ds::Module *pModule) {
                    ::naeem::hottentot::generator::ds::Service *pService;
                    std::string replacableServiceProxyBuilderTmpStr;
                    for (int i = 0; i < pModule->services_.size(); i++) {
                        //write abstractService.tmp
                        std::string basePackageName = pModule->package_;
                        pService = pModule->services_.at(i);
                        std::string replacableServiceProxyBuilderTmpStr;
                        //write service proxy builder
                        std::string path = outDir_ + "/" + pService->name_.c_str() + "ServiceProxyBuilder.java";
                        os.open(path.c_str(), std::ios::trunc);
                        replacableServiceProxyBuilderTmpStr = serviceProxyBuilderTmpStr_;
                        while (replacableServiceProxyBuilderTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                            replacableServiceProxyBuilderTmpStr.replace(
                                    replacableServiceProxyBuilderTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                                    basePackageName);
                        }
                        while (replacableServiceProxyBuilderTmpStr.find("[%SERVICE_NAME%]") != std::string::npos) {
                            replacableServiceProxyBuilderTmpStr.replace(
                                    replacableServiceProxyBuilderTmpStr.find("[%SERVICE_NAME%]"), 16, pService->name_);
                        }
                        os.write(replacableServiceProxyBuilderTmpStr.c_str(),
                                 replacableServiceProxyBuilderTmpStr.size());
                        os.close();
                    }
                }

                void
                JavaGenerator::GenerateRequestHandler(::naeem::hottentot::generator::ds::Module *pModule) {
                    ::naeem::hottentot::generator::ds::Service *pService;
                    std::string replacableRequestHandlerTmpStr;
                    std::string basePackageName = pModule->package_;
                    for (int i = 0; i < pModule->services_.size(); i++) {
                        std::string basePackageName = pModule->package_;
                        pService = pModule->services_.at(i);
                        std::string path = outDir_ + "/" + pService->name_.c_str() + "RequestHandler.java";
                        os.open(path.c_str());
                        std::string serviceName = pService->name_;
                        std::string lowerCaseServiceName = pService->name_;
                        lowerCaseServiceName[0] += 32;
                        replacableRequestHandlerTmpStr = requestHandlerTmpStr_;


                        while (replacableRequestHandlerTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                            replacableRequestHandlerTmpStr.replace(
                                    replacableRequestHandlerTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
                        }
                        while (replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]") != std::string::npos) {
                            replacableRequestHandlerTmpStr.replace(
                                    replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]"), 16, pService->name_);
                        }
                        replacableRequestHandlerTmpStr.replace(
                                replacableRequestHandlerTmpStr.find("[%SERVICE_NAME_LOWERCASE%]"), 26,
                                lowerCaseServiceName);

                        ::naeem::hottentot::generator::ds::Method *pMethod;
                        std::string methodConditionStr;

                        for (int i = 0; i < pService->methods_.size(); i++) {
                            pMethod = pService->methods_.at(i);
                            std::string lowerCaseReturnType = pMethod->returnType_;
                            lowerCaseReturnType[0] += 32;
                            std::stringstream ssID;
                            //TODO(alisharifi) make method id by hashing
                            //ssID << pMethod->id_;
                            ssID << 1;
                            methodConditionStr += "if(methodId == " + ssID.str() + "){\n";
                            methodConditionStr +=
                                    TAB_STR + TAB_STR + TAB_STR + "List <Argument> args = request.getArgs();\n";
                            ::naeem::hottentot::generator::ds::Argument *pArg;
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                pArg = pMethod->arguments_.at(i);
                                std::stringstream ssI;
                                ssI << i;
                                methodConditionStr +=
                                        TAB_STR + TAB_STR + TAB_STR + "Argument arg" + ssI.str() + " = args.get(" +
                                        ssI.str() + ");\n";
                                methodConditionStr += TAB_STR + TAB_STR + TAB_STR + "byte[] serialized" + pArg->type_;
                                methodConditionStr += " = arg" + ssI.str() + ".getData();\n";
                                methodConditionStr +=
                                        TAB_STR + TAB_STR + TAB_STR + pArg->type_ + " " + pArg->variable_ + " = new " +
                                        pArg->type_ + "();\n";
                                methodConditionStr +=
                                        TAB_STR + TAB_STR + TAB_STR + pArg->variable_ + ".deserialize(serialized" +
                                        pArg->type_ + ");\n";
                            }
                            methodConditionStr +=
                                    TAB_STR + TAB_STR + TAB_STR + pMethod->returnType_ + " " + lowerCaseReturnType +
                                    " = null;\n";
                            methodConditionStr += TAB_STR + TAB_STR + TAB_STR + "Response response = new Response();\n";
                            //methodConditionStr += TAB_STR + TAB_STR + "try{\n";
                            methodConditionStr +=
                                    TAB_STR + TAB_STR + TAB_STR + lowerCaseReturnType + " = " + lowerCaseServiceName +
                                    "Impl." + pMethod->name_ + "(";
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                pArg = pMethod->arguments_.at(i);
                                methodConditionStr += pArg->variable_;
                                if (i < pMethod->arguments_.size() - 1) {
                                    methodConditionStr += pArg->variable_ += ",";
                                }
                            }
                            methodConditionStr += ");\n";
                            methodConditionStr +=
                                    TAB_STR + TAB_STR + TAB_STR + "byte[] serialized" + pMethod->returnType_ + " = " +
                                    lowerCaseReturnType + ".serialize();\n";
                            methodConditionStr += TAB_STR + TAB_STR + TAB_STR + "response.setStatusCode((byte) 100);\n";
                            methodConditionStr +=
                                    TAB_STR + TAB_STR + TAB_STR + "response.setData(serialized" + pMethod->returnType_ +
                                    ");\n";
                            methodConditionStr += TAB_STR + TAB_STR + TAB_STR + "response.setLength(serialized" +
                                                  pMethod->returnType_ + ".length + 1);\n";
                            methodConditionStr += TAB_STR + TAB_STR + TAB_STR + "return response;\n";
                            methodConditionStr += TAB_STR + TAB_STR + "}";

                        }
                        replacableRequestHandlerTmpStr.replace(
                                replacableRequestHandlerTmpStr.find("[%METHOD_CONDITIONS%]"), 21,
                                methodConditionStr);
                        os.write(replacableRequestHandlerTmpStr.c_str(), replacableRequestHandlerTmpStr.size());
                        os.close();
                    }
                }

                void
                JavaGenerator::GenerateServiceProxy(::naeem::hottentot::generator::ds::Module *pModule) {
                    ::naeem::hottentot::generator::ds::Service *pService;
                    std::string basePackageName = pModule->package_;
                    for (int i = 0; i < pModule->services_.size(); i++) {
                        std::string replacableServiceProxyStrTmp = serviceProxyTmpStr_;
                        pService = pModule->services_.at(i);
                        std::string path = outDir_ + "/" + pService->name_.c_str() + "ServiceProxy.java";
                        os.open(path.c_str(), std::ios::trunc);
                        pService = pModule->services_.at(i);
                        while (replacableServiceProxyStrTmp.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                            replacableServiceProxyStrTmp.replace(
                                    replacableServiceProxyStrTmp.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
                        }
                        while (replacableServiceProxyStrTmp.find("[%SERVICE_NAME%]") != std::string::npos) {
                            replacableServiceProxyStrTmp.replace(replacableServiceProxyStrTmp.find("[%SERVICE_NAME%]"),
                                                                 16, pService->name_);
                        }

                        //loop on service methods
                        ::naeem::hottentot::generator::ds::Method *pMethod;
                        std::string methodsStr;
                        for (int i = 0; i < pService->methods_.size(); i++) {
                            pMethod = pService->methods_.at(i);
                            pMethod = pService->methods_.at(i);
                            methodsStr += "public " + pMethod->returnType_ + " " + pMethod->name_ + "(";
                            ::naeem::hottentot::generator::ds::Argument *pArg;
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {

                                pArg = pMethod->arguments_.at(i);
                                methodsStr += pArg->type_ + " " + pArg->variable_;
                                if (i < pMethod->arguments_.size() - 1) {
                                    methodsStr += ",";
                                }
                            }
                            methodsStr += ") { \n";
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                methodsStr += TAB_STR + TAB_STR + "//serialize " + pArg->variable_ + "\n";
                                methodsStr += TAB_STR + TAB_STR + "byte[] serialized" + pArg->type_ + " = " +
                                              pArg->variable_ + ".serialize();\n";
                            }
                            methodsStr += "\n";
                            methodsStr += TAB_STR + TAB_STR + "//make request\n";
                            methodsStr += TAB_STR + TAB_STR + "Request request = new Request();\n";
                            std::stringstream serviceId;
                            //TODO(alisharifi) make service id by hashing
                            //serviceId << pService->id_;
                            serviceId << "1";
                            methodsStr += TAB_STR + TAB_STR + "request.setServiceId((byte) " + serviceId.str() + ");\n";
                            std::stringstream methodId;
                            //TODO(alisharifi) make method id by hashing
                            //methodId << pMethod->id_;
                            methodId << "1";
                            methodsStr += TAB_STR + TAB_STR + "request.setMethodId((byte) " + methodId.str() + ");\n";
                            std::stringstream argSize;
                            argSize << pMethod->arguments_.size();
                            methodsStr +=
                                    TAB_STR + TAB_STR + "request.setArgumentCount((byte) " + argSize.str() + ");\n";
                            methodsStr += TAB_STR + TAB_STR + "request.setType(Request.RequestType.";

                            //std::cout << pService->serviceType_;
                            if (pService->serviceType_ == 0) {
                                methodsStr += "InvokeStateless";
                            } else if (pService->serviceType_ == 1) {
                                methodsStr += "InvokeStatefull";
                            }
                            methodsStr += ");\n";
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                std::stringstream ssI;
                                pArg = pMethod->arguments_.at(i);
                                ssI << i;
                                methodsStr += TAB_STR + TAB_STR + "Argument arg" + ssI.str() + " = new Argument();\n";
                                methodsStr += TAB_STR + TAB_STR + "arg" + ssI.str() + ".setDataLength(" +
                                              pArg->variable_.c_str() + ".serialize().length);\n";
                                methodsStr +=
                                        TAB_STR + TAB_STR + "arg" + ssI.str() + ".setData(" + pArg->variable_.c_str() +
                                        ".serialize());\n";
                                methodsStr += TAB_STR + TAB_STR + "request.addArgument(arg" + ssI.str() + ");\n";
                            }
                            //calculate request length
                            methodsStr += TAB_STR + TAB_STR + "int dataLength = 0;\n";
                            methodsStr += TAB_STR + TAB_STR + "//calculate data length for every argument\n";
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                pArg = pMethod->arguments_.at(i);
                                std::string argDataLengthVarName = pArg->variable_ + "DataLength";
                                std::string argDataLengthByteArrayLengthVarName =
                                        pArg->variable_ + "DataLengthByteArrayLength";
                                methodsStr += TAB_STR + TAB_STR + "//calulate " + argDataLengthVarName + "\n";
                                methodsStr += TAB_STR + TAB_STR + "int " + argDataLengthVarName + "= serialized" +
                                              pArg->type_ + ".length;\n";
                                methodsStr +=
                                        TAB_STR + TAB_STR + "int " + argDataLengthByteArrayLengthVarName + " = 1;\n";
                                methodsStr += TAB_STR + TAB_STR + "if (" + argDataLengthVarName + " >= 0x80) {\n";
                                methodsStr +=
                                        TAB_STR + TAB_STR + TAB_STR + "if (" + argDataLengthVarName + " <= 0xff) {\n";
                                methodsStr += TAB_STR + TAB_STR + TAB_STR + TAB_STR + "//ex 0x81 0xff\n";
                                methodsStr += TAB_STR + TAB_STR + TAB_STR + TAB_STR + "" +
                                              argDataLengthByteArrayLengthVarName + " = 2;\n";
                                methodsStr += TAB_STR + TAB_STR + TAB_STR + "} else if (" + argDataLengthVarName +
                                              " <= 0xffff) {\n";
                                methodsStr += TAB_STR + TAB_STR + TAB_STR + TAB_STR + "//ex 0x82 0xff 0xff\n";
                                methodsStr += TAB_STR + TAB_STR + TAB_STR + TAB_STR + "" +
                                              argDataLengthByteArrayLengthVarName + " = 3;\n";
                                methodsStr += TAB_STR + TAB_STR + TAB_STR + "} else if (" + argDataLengthVarName +
                                              " <= 0xffffff) {\n";
                                methodsStr += TAB_STR + TAB_STR + TAB_STR + TAB_STR + "//ex 0x83 0xff 0xff 0xff\n";
                                methodsStr += TAB_STR + TAB_STR + TAB_STR + TAB_STR + "" +
                                              argDataLengthByteArrayLengthVarName + " = 4;\n";
                                methodsStr += TAB_STR + TAB_STR + TAB_STR + "}\n";
                                methodsStr += TAB_STR + TAB_STR + "}\n";
                                methodsStr += TAB_STR + TAB_STR + "dataLength += " + argDataLengthVarName + " + " +
                                              argDataLengthByteArrayLengthVarName + ";\n";
                            }
                            methodsStr += TAB_STR + TAB_STR + "//\n";
                            methodsStr += TAB_STR + TAB_STR + "request.setLength(4 + dataLength);\n";
                            methodsStr += TAB_STR + TAB_STR + "//connect to server\n";
                            methodsStr += TAB_STR + TAB_STR + "TcpClient tcpClient = TcpClientFactory.create();\n";
                            methodsStr += TAB_STR + TAB_STR + "try{\n";
                            methodsStr += TAB_STR + TAB_STR + TAB_STR + "tcpClient.connect(host, port);\n";
                            methodsStr += TAB_STR + TAB_STR + "} catch (TcpClientConnectException e) {\n";
                            methodsStr += TAB_STR + TAB_STR + TAB_STR + "throw new HottentotRuntimeException(e);\n";
                            methodsStr += TAB_STR + TAB_STR + "}\n";
                            methodsStr += TAB_STR + TAB_STR + "//serialize request according to HTNP\n";
                            methodsStr += TAB_STR + TAB_STR + "Protocol protocol = ProtocolFactory.create();\n";
                            methodsStr += TAB_STR + TAB_STR +
                                          "byte[] serializedRequest = protocol.serializeRequest(request);\n";
                            methodsStr += TAB_STR + TAB_STR + "//send request\n";
                            methodsStr += TAB_STR + TAB_STR + "try {\n";
                            methodsStr += TAB_STR + TAB_STR + TAB_STR + "tcpClient.write(serializedRequest);\n";
                            methodsStr += TAB_STR + TAB_STR + "} catch (TcpClientWriteException e) {\n";
                            methodsStr += TAB_STR + TAB_STR + TAB_STR + "throw new HottentotRuntimeException(e);\n";
                            methodsStr += TAB_STR + TAB_STR + "}\n";
                            methodsStr += TAB_STR + TAB_STR + "//read response from server\n";
                            methodsStr += TAB_STR + TAB_STR + "byte[] buffer = new byte[256];\n";
                            methodsStr += TAB_STR + TAB_STR + "while (!protocol.IsResponseComplete()) {\n";
                            methodsStr += TAB_STR + TAB_STR + TAB_STR + "byte[] dataChunkRead;\n";
                            methodsStr += TAB_STR + TAB_STR + TAB_STR + "try {\n";
                            methodsStr += TAB_STR + TAB_STR + TAB_STR + TAB_STR + "dataChunkRead = tcpClient.read();\n";
                            methodsStr += TAB_STR + TAB_STR + TAB_STR + "} catch (TcpClientReadException e) {\n";
                            methodsStr +=
                                    TAB_STR + TAB_STR + TAB_STR + TAB_STR + "throw new HottentotRuntimeException(e);\n";
                            methodsStr += TAB_STR + TAB_STR + TAB_STR + "}\n";
                            methodsStr +=
                                    TAB_STR + TAB_STR + TAB_STR + "protocol.processDataForResponse(dataChunkRead);\n";
                            methodsStr += TAB_STR + TAB_STR + "}\n";
                            methodsStr += TAB_STR + TAB_STR + "//deserialize token part of response\n";
                            methodsStr += TAB_STR + TAB_STR + "Response response = protocol.getResponse();\n";
                            methodsStr += TAB_STR + TAB_STR + "//close everything\n";
                            methodsStr += TAB_STR + TAB_STR + "//deserialize " + pMethod->returnType_ +
                                          "part from response\n";
                            std::string lowerCaseReturnType = pMethod->returnType_;
                            lowerCaseReturnType[0] += 32;
                            methodsStr += TAB_STR + TAB_STR + "" + pMethod->returnType_ + " " + lowerCaseReturnType +
                                          "= null;\n";
                            methodsStr += TAB_STR + TAB_STR + "if (response.getStatusCode() == -1) {\n";
                            methodsStr += TAB_STR + TAB_STR + TAB_STR + "//\n";
                            methodsStr += TAB_STR + TAB_STR + "} else {\n";
                            methodsStr += TAB_STR + TAB_STR + TAB_STR + "" + lowerCaseReturnType + "= new " +
                                          pMethod->returnType_ + "();\n";
                            methodsStr += TAB_STR + TAB_STR + TAB_STR + "" + lowerCaseReturnType +
                                          ".deserialize(response.getData());\n";
                            methodsStr += TAB_STR + TAB_STR + "}\n";
                            methodsStr += TAB_STR + TAB_STR + "return " + lowerCaseReturnType + ";\n";
                            methodsStr += TAB_STR + "}\n";
                        }
                        replacableServiceProxyStrTmp.replace(replacableServiceProxyStrTmp.find("[%METHODS%]"), 11,
                                                             methodsStr);
                        os.write(replacableServiceProxyStrTmp.c_str(), replacableServiceProxyStrTmp.size());
                        os.close();
                    }
                }
            }
        }
    }
}
