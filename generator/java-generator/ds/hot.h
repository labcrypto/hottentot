//
// Created by alisharifi on 11/10/15.
//

#ifndef GENERATOR_HOT_H
#define GENERATOR_HOT_H


#include "struct.h"
#include "module.h"
#include <fstream>

class Hot {
public:
    ofstream os;
    ifstream is;
    vector<Module*> modules_;
    string structTmpStr;
    string abstractServiceTmpStr;
    string serviceTmpStr;
    string serviceProxyBuilderTmpStr;
    string requestHandlerTmpStr;
    string serviceProxyTmpStr;
    void FakeInsert();
    void GenerateStructs(Module*);
    void ReadTemplateFiles();
    void GenerateJava();
    void GenerateAbstractService(Module*);
    void GenerateServiceInterface(Module*);
    void GenerateServiceProxyBuilder(Module*);
    void GenerateRequestHandler(Module*);
    void GenerateServiceProxy(Module*);
    ~Hot();

};


#endif //GENERATOR_HOT_H
