//
// Created by alisharifi on 11/10/15.
//

#ifndef GENERATOR_HOT_H
#define GENERATOR_HOT_H


#include "struct.h"
#include "module.h"

class Hot {
public:
    void GenerateJava();
    void GenerateStructFiles();
    vector<Module*> modules_;
};


#endif //GENERATOR_HOT_H
