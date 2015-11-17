//
// Created by alisharifi on 11/10/15.
//

#ifndef GENERATOR_MODULE_H
#define GENERATOR_MODULE_H
#include <string>
#include <vector>
#include "struct.h"
#include "service.h"
using namespace std;


class Module {
public:
    string name_;
    vector<Struct*> structs_;
    vector<Service*> services_;
};


#endif //GENERATOR_MODULE_H
