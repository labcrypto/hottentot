//
// Created by developer on 11/11/15.
//

#ifndef JAVA_GENERATOR_SERVICE_H
#define JAVA_GENERATOR_SERVICE_H

#include <string>
#include <vector>
#include "argument.h"
#include "method.h"

using namespace std;

class Service {
public:
    vector<Method*> methods_;
    string name_;
    int id_;
    int requestType_;
};


#endif //JAVA_GENERATOR_SERVICE_H
