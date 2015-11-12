//
// Created by alisharifi on 11/10/15.
//

#ifndef GENERATOR_STRUCT_H
#define GENERATOR_STRUCT_H

#include <string>
#include <vector>
#include "member.h"
using namespace std;
class Struct {
public:
    string name_;
    vector<Member*> members_;
};


#endif //GENERATOR_STRUCT_H
