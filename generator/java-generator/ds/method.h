//
// Created by developer on 11/12/15.
//

#ifndef JAVA_GENERATOR_METHOD_H
#define JAVA_GENERATOR_METHOD_H

#include <string>
#include <vector>
#include "argument.h"

class Method {
public:
    vector<Argument*> args_;
    string returnType_;
    string name_;
};


#endif //JAVA_GENERATOR_METHOD_H
