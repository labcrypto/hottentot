/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 LabCrypto Org.
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
#include <string.h>

#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <iostream>

#ifdef _MSC_VER
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#ifdef _MSC_VER
#include "../../hot.h"
#include "../../declaration.h"
#include "../../service.h"
#include "../../method.h"
#include "../../argument.h"
#include "../../enum.h"

#include "../../fasthash.h"

#include "../../cc/cc_generator.h"
#include "../../java/java_generator.h"
#else
#include "hot.h"
#include "declaration.h"
#include "service.h"
#include "method.h"
#include "argument.h"
#include "enum.h"

#include "fasthash.h"

#include "cc/cc_generator.h"
#include "java/java_generator.h"
#endif

void yyerror(char *);

extern "C" {
  int yylex(void);
}

unsigned int lineCounter = 1;
std::string lastType;
std::stack<std::string> stack;
::naeem::hottentot::generator::ds::Hot *currentHot;
::naeem::hottentot::generator::ds::Module *currentModule;
::naeem::hottentot::generator::ds::Enum *currentEnum;
::naeem::hottentot::generator::ds::Struct *currentStruct;
::naeem::hottentot::generator::ds::Service *currentService;
::naeem::hottentot::generator::ds::Method *currentMethod;

%}
%union {
  char *string;
}
%token MODULE
%token STRUCT
%token ENUM
%token <string> LIST
%token <string> SET
%token <string> MAP
%token STATELESS
%token STATEFUL
%token SERVICE
%token <string> ORD
%token <string> COMMENT
%token <string> NUMBER
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
                    currentStruct = new ::naeem::hottentot::generator::ds::Struct(currentModule);
                    // fprintf(stdout, ">>> GENERATOR: Struct object created.\n");
                    currentModule->AddStruct(currentStruct);
                    // fprintf(stdout, ">>> GENERATOR: Struct object has been added to model.\n");
                  } else {
                    fprintf(stdout, "Line %d: Structs can't be nested.\n", lineCounter);
                    exit(1);
                  }
                } STRUCT IDENTIFIER '{' struct_body '}' ';' {
                  // printf("Struct seen: %s\n", $3);
                  currentStruct->SetName($3);
                  currentStruct = NULL;
                }
                | {
                    if (currentService == NULL) {
                      currentService = new ::naeem::hottentot::generator::ds::Service("stateless", "", currentModule);
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
                      currentService = new ::naeem::hottentot::generator::ds::Service("stateful", "",currentModule);
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
                | {
                    if (currentEnum == NULL) {
                      currentEnum = new ::naeem::hottentot::generator::ds::Enum(currentModule);
                      currentModule->AddEnum(currentEnum);
                    } else {
                      fprintf(stdout, "SYNTAX ERROR: Enums can't be nested.\n");
                      exit(1);
                    }
                } ENUM IDENTIFIER '{' enum_body '}' ';' {
                  currentEnum->SetName($3);
                  currentEnum = NULL;
                }

enum_body:      enum_items;

enum_items:     enum_item
                | enum_items enum_item
                ;

enum_item:      NUMBER '=' IDENTIFIER ';' {
                  currentEnum->AddItem($3, atol($1));
                }
                ;

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
                    currentMethod = new ::naeem::hottentot::generator::ds::Method(currentService);
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
  fprintf(stderr, "Line %d: ERROR: %s\n", lineCounter, s);
}

int yywrap(void) {
  return 1;
}

extern FILE *yyin;

void printHelpMessageAndExit() {
  std::cout << std::endl;
  std::cout << "Hottentot Serialization and RPC Framework" << std::endl;
  std::cout << "NTNAEEM Co. 2016 Copyright" << std::endl;
  std::cout << "Usage: hot [OPTION]... [HOT-FILE]..." << std::endl;
  std::cout << "  OPTIONS:" << std::endl;
  std::cout << "    --java                     Generate java sources. [Default: disabled]" << std::endl;
  std::cout << "    --cc                       Generate C++ sources. [Default: enabled]" << std::endl;
  std::cout << "    --makefile                 Generate Makefile for C++ sources. [Default: disabled]" << std::endl;
  std::cout << "    --client                   Generate sources for C++ client. [Default: disabled]" << std::endl;
  std::cout << "    --stub                     Generate a C++ stub for service. [Default: disabled]" << std::endl;
  std::cout << "    --indent-with-spaces       Generator will produce indents using spaces. [Default: enabled]" << std::endl;
  std::cout << "    --indent-with-tabs         Generator will produce indents using tabs. [Default: disabled]" << std::endl;
  std::cout << "    --indent-space-count       Number of spaces for producing a single indent. [Default: 2]" << std::endl;
  std::cout << "    --out                      Path to output directory. [Default: hotgen]" << std::endl;
  std::cout << "    --parse                    Displays parse result in a tree format. [Default: disabled]" << std::endl;
  std::cout << "    --dont-generate            Don't generate sources. [Default: disabled]" << std::endl;
  std::cout << std::endl;
  std::cout << "For more information and examples, please visit https://github.com/NTNAEEM/hottentot" << std::endl;
  std::cout << std::endl;
  exit(1);
}

int main(int argc, char **argv) {
  bool isJava = false;
  bool isCC = false;
  bool isSpacesUsedForIndentation = true;
  bool makefileGenerated = false;
  bool clientGenerated = false;
  bool stubGenerated = false;
  bool dontGenerate = false;
  bool parse = false;
  uint8_t numberOfSpacesUsedForIndentation = 2;
  char *outputDir = 0;
  std::vector<char*> hots;
  for (uint16_t i = 1; i < argc;) {
    if (strcmp(argv[i], "--java") == 0) {
      isJava = true;
      i++;
    } else if (strcmp(argv[i], "--cc") == 0) {
      isCC = true;
      i++;
    } else if (strcmp(argv[i], "--indent-with-spaces") == 0) {
      isSpacesUsedForIndentation = true;
      i++;
    } else if (strcmp(argv[i], "--indent-with-tabs") == 0) {
      isSpacesUsedForIndentation = false;
      i++;
    } else if (strcmp(argv[i], "--makefile") == 0) {
      makefileGenerated = true;
      i++;
    } else if (strcmp(argv[i], "--client") == 0) {
      clientGenerated = true;
      i++;
    } else if (strcmp(argv[i], "--stub") == 0) {
      stubGenerated = true;
      i++;
    } else if (strcmp(argv[i], "--dont-generate") == 0) {
      dontGenerate = true;
      i++;
    } else if (strcmp(argv[i], "--parse") == 0) {
      parse = true;
      i++;
    } else if (strcmp(argv[i], "--help") == 0) {
      printHelpMessageAndExit();
    } else if (strcmp(argv[i], "--number-of-spaces-used-for-indentation") == 0) {
      numberOfSpacesUsedForIndentation = atoi(argv[i + 1]);
      i += 2;
    } else if (strcmp(argv[i], "--out") == 0) {
      outputDir = argv[i + 1];
      i += 2;
    } else {
      if (strlen(argv[i]) > 1 && strncmp(argv[i], "--", 2) == 0) {
        printf("ERROR: Unknown option: %s\n", argv[i]);
        printHelpMessageAndExit();
      }
      hots.push_back(argv[i]);
      i++;
    }
  }
  if (!isJava && !isCC) {
    isCC = true;
  }
  if (outputDir == 0) {
    outputDir = "hotgen";
  }
  if (hots.size() == 0) {
    std::cout << "ERROR: No hot file is selected for generation." << std::endl;
    printHelpMessageAndExit();
    exit(1);
  }
  for (uint16_t i = 0; i < hots.size(); i++) {
    yyin = fopen(hots[i],"r+");
    if (!yyin) {
      printf("ERROR: File can't be opened.\n");
      return 1;
    }
    yyparse();
    if (parse) {
      currentHot->Display();
    }
    ::naeem::hottentot::generator::GenerationConfig generationConfig;
    generationConfig.SetOutDir(outputDir);
    generationConfig.SetSpacesUsedInsteadOfTabsForIndentation(isSpacesUsedForIndentation);
    generationConfig.SetNumberOfSpacesUsedForIndentation(numberOfSpacesUsedForIndentation);
    generationConfig.SetMakefileGenerated(makefileGenerated);
    generationConfig.SetClientGenerated(clientGenerated);
    generationConfig.SetStubGenerated(stubGenerated);
    ::naeem::hottentot::generator::Generator *generator = 0;
    if (!dontGenerate && isCC) {
      generator = new ::naeem::hottentot::generator::cc::CCGenerator();
      ::naeem::hottentot::generator::cc::CCGenerator* ccGenerator =
          dynamic_cast< ::naeem::hottentot::generator::cc::CCGenerator*>(generator);
      ccGenerator->Generate(currentHot, generationConfig);
      if (makefileGenerated) {
        ccGenerator->GenerateMakefile(currentHot, generationConfig);
      }
      if (clientGenerated) {
        ccGenerator->GenerateClient(currentHot, generationConfig);
      }
      if (stubGenerated) {
        ccGenerator->GenerateStub(currentHot, generationConfig);
      }
    }
    if (!dontGenerate && isJava) {
      generator = new ::naeem::hottentot::generator::java::JavaGenerator();
      generator->Generate(currentHot, generationConfig);
    }
    delete generator;
    delete currentHot;
    currentHot = NULL;
  }
  return 0;
}