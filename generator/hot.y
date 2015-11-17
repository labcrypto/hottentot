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
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <stack>
#include <stdint.h>
#include <iostream>

#include "ds/hot.h"
#include "ds/declaration.h"
#include "ds/service.h"
#include "ds/method.h"
#include "ds/argument.h"

#include "cc/cc_generator.h"


void yyerror(char *);

extern "C" {
  int yylex(void);
}

std::string lastType;
std::stack<std::string> stack;
::naeem::hottentot::generator::ds::Hot *currentHot;
::naeem::hottentot::generator::ds::Module *currentModule;
::naeem::hottentot::generator::ds::Struct *currentStruct;
::naeem::hottentot::generator::ds::Service *currentService;
::naeem::hottentot::generator::ds::Method *currentMethod;

%}
%union {
  char *string;
}
%token MODULE
%token STRUCT
%token <string> LIST
%token <string> SET
%token <string> MAP
%token STATELESS
%token STATEFUL
%token SERVICE
%token <string> ORD
%token <string> IDENTIFIER
%token <string> TYPE
%start hot
%type<string> type
%%

hot:            modules {                 
                }
                ;

modules:        modules module
                |
                ;

module:         {
                  if (currentHot == NULL) {
                    currentHot = new ::naeem::hottentot::generator::ds::Hot();
                    // fprintf(stdout, ">>> GENERATOR: Hot object created.\n");
                  }
                  if (currentModule == NULL) {
                    currentModule = new ::naeem::hottentot::generator::ds::Module();
                    // fprintf(stdout, ">>> GENERATOR: Module object created.\n");
                    currentHot->AddModule(currentModule);
                    // fprintf(stdout, ">>> GENERATOR: Module object has been added to hot.\n");
                    while (!stack.empty()) {
                      stack.pop();
                    }
                  } else {
                    fprintf(stdout, "SYNTAX ERROR: Modules can't be nested.\n");
                    exit(1);
                  }
                } MODULE package '{' module_body '}' ';' {
                  // printf("Module parsed.\n");
                  std::string package = "";
                  while (!stack.empty()) {
                    package += stack.top() + ".";
                    stack.pop();
                  }
                  currentModule->SetPackage(package.substr(0, package.size() - 1));
                  currentModule = NULL;
                }
                ;

package:        IDENTIFIER package { 
                  // printf("Package seen: %s\n", $1);
                  stack.push($1);
                }
                | IDENTIFIER '.' package { 
                  // printf("Package seen: %s\n", $1);
                  stack.push($1); 
                }
                |
                ;

module_body:    items
                ;

items:          items item
                |
                ;

item:           {
                  if (currentStruct == NULL) {
                    currentStruct = new ::naeem::hottentot::generator::ds::Struct();
                    // fprintf(stdout, ">>> GENERATOR: Struct object created.\n");
                    currentModule->AddStruct(currentStruct);
                    // fprintf(stdout, ">>> GENERATOR: Struct object has been added to model.\n");
                  } else {
                    fprintf(stdout, "SYNTAX ERROR: Structs can't be nested.\n");
                    exit(1);
                  }
                } STRUCT IDENTIFIER '{' struct_body '}' ';' {
                  // printf("Struct seen: %s\n", $3);
                  currentStruct->SetName($3);
                  currentStruct = NULL;
                }
                | {
                    if (currentService == NULL) {
                      currentService = new ::naeem::hottentot::generator::ds::Service();
                      currentModule->AddService(currentService);
                    } else {
                      fprintf(stdout, "SYNTAX ERROR: Services can't be nested.\n");
                      exit(1);
                    } 
                  } STATELESS SERVICE IDENTIFIER '{' service_body '}' ';' {
                  // printf("Stateless service seen: %s\n", $4);
                  currentService->SetName($4);
                  currentService->SetServiceType("stateless");
                  currentService = NULL;
                }
                | {
                    if (currentService == NULL) {
                      currentService = new ::naeem::hottentot::generator::ds::Service();
                      currentModule->AddService(currentService);
                    } else {
                      fprintf(stdout, "SYNTAX ERROR: Services can't be nested.\n");
                      exit(1);
                    } 
                  } STATEFUL SERVICE IDENTIFIER '{' service_body '}' ';' {
                  // printf("Stateful service seen: %s\n", $4);
                  currentService->SetName($4);
                  currentService->SetServiceType("stateful");
                  currentService = NULL;
                }

struct_body:    declarations;

declarations:   declaration
                | declarations declaration
                ;

declaration:    type IDENTIFIER ORD ';' {
                  // printf("Declaration3 seen:    LIST<%s> %s %s\n", $3, $5, $6);
                  currentStruct->AddDeclaration(new ::naeem::hottentot::generator::ds::Declaration($1, $2, $3));
                }
                ;

service_body:   methods
                ;

methods:        methods method
                |
                ;

method:         {
                  if (currentMethod == NULL) {
                    currentMethod = new ::naeem::hottentot::generator::ds::Method();
                    currentService->AddMethod(currentMethod);
                  }
                } type IDENTIFIER '(' arguments ')' ';' {
                  currentMethod->SetReturnType($2);
                  currentMethod->SetName($3);
                  currentMethod = NULL;
                }
                ;

arguments:      argument
                | arguments ',' argument
                |
                ;

argument:       type IDENTIFIER {
                  currentMethod->AddArgument(new ::naeem::hottentot::generator::ds::Argument($1, $2));
                  // printf("Argument has been added.\n");
                }
                ;

type:           LIST '<' type '>' {
                  $$ = (char*)malloc(strlen($1) + strlen($3) + 10);
                  strcpy($$, $1);
                  strcat($$, "<");
                  strcat($$, $3);
                  strcat($$, ">");
                }               
                | SET '<' type '>' {
                  $$ = (char*)malloc(strlen($1) + strlen($3) + 10);
                  strcpy($$, $1);
                  strcat($$, "<");
                  strcat($$, $3);
                  strcat($$, ">");
                }                
                | MAP '<' type ',' type '>' {
                  $$ = (char*)malloc(strlen($1) + strlen($3) + strlen($5) + 10);
                  strcpy($$, $1);
                  strcat($$, "<");
                  strcat($$, $3);
                  strcat($$, ",");
                  strcat($$, $5);
                  strcat($$, ">");
                }                
                | TYPE  {
                  $$ = (char *)malloc(strlen($1) + 2);
                  strcpy($$, $1);
                }
                | IDENTIFIER {
                  $$ = (char *)malloc(strlen($1) + 2);
                  strcpy($$, $1);
                }
                ;

%%

void yyerror(char *s) {
  fprintf(stderr, "ERROR: %s\n", s);
}

int yywrap(void) {
  return 1;
}

extern FILE *yyin;

int main(int argc, char **argv) {
  bool isJava = false;
  bool isCC = false;
  bool hotsBegun = false;
  char *outputDir = 0;
  char **hots = 0;
  uint16_t numOfHots = 0;
  for (uint16_t i = 1; i < argc;) {
    if (strcmp(argv[i], "--java") == 0) {
      if (hotsBegun) {
        fprintf(stderr, "Usage: hot [--java] [--cc] [--out OUTPUT_DIRECTORY] HOT_FILE [HOT FILE] [HOT_FILE] ...\n");
        exit(1);
      }
      isJava = true;
      i++;
    } else if (strcmp(argv[i], "--cc") == 0) {
      if (hotsBegun) {
        fprintf(stderr, "Usage: hot [--java] [--cc] [--out OUTPUT_DIRECTORY] HOT_FILE [HOT FILE] [HOT_FILE] ...\n");
        exit(1);
      }
      isCC = true;
      i++;
    } else if (strcmp(argv[i], "--out") == 0) {
      outputDir = argv[i + 1];
      i += 2;
    } else {
      if (hots == 0) {
        hotsBegun = true;
        hots = new char*[argc - i];
      }
      hots[numOfHots++] = argv[i++];
    }
  }
  if (!isJava && !isCC) {
    isCC = true;
  }
  std::cout << "Num: " << numOfHots << std::endl;
  std::cout << "Is Java: " << isJava << std::endl;
  std::cout << "Is CC: " << isCC << std::endl;
  std::cout << "Out: " << (outputDir == 0 ? "NOT SET" : outputDir) << std::endl;
  std::cout << "Hot files: \n";
  for (uint16_t i = 0; i < numOfHots; i++) {
    yyin = fopen(hots[i],"r+");
    if (!yyin) {
      printf("ERROR: File can't be opened.\n");
      return 1;
    }
    yyparse();
    currentHot->Display();
    if (isCC) {
      ::naeem::hottentot::generator::Generator *generator = new 
        ::naeem::hottentot::generator::cc::CCGenerator();
      generator->Generate(currentHot);
      delete generator;
      delete currentHot;
      currentHot = NULL;
    }
    if (isJava) {
      /*::naeem::hottentot::generator::Generator *generator = new 
        ::naeem::hottentot::generator::cc::CCGenerator();
      generator->Generate(currentHot);
      delete generator;
      delete currentHot;
      currentHot = NULL;*/
    }
    std::cout << hots[i] << std::endl;
  }
  return 0;
}