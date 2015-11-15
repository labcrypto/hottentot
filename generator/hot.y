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

#include "shared.h"
#include "ds/hot.h"
#include "ds/list_declaration.h"
#include "ds/set_declaration.h"
#include "ds/map_declaration.h"
#include "ds/service.h"


void yyerror(char *);

extern "C" {
  int yylex(void);
}


%}
%union {
  char *string;
}
%token MODULE
%token STRUCT
%token LIST
%token SET
%token MAP
%token STATELESS
%token STATEFUL
%token SERVICE
%token <string> ORD
%token <string> IDENTIFIER
%token <string> TYPE
%start hot
%%

hot:            modules { 
                  // printf("HOT parsed.\n"); 
                  printf("======================\n");
                  currentHot->Display();
                }
                ;

modules:        modules module
                |
                ;

module:         MODULE package '{' module_body '}' ';' {
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

item:           STRUCT IDENTIFIER '{' struct_body '}' ';' {
                  // printf("Struct seen: %s\n", $2);
                  currentStruct->SetName($2);
                  currentStruct = NULL;
                }
                | STATELESS SERVICE IDENTIFIER '{' service_body '}' ';' {
                  // printf("Stateless service seen: %s\n", $3);
                  currentService->SetName($3);
                  currentService->SetServiceType("stateless");
                  currentService = NULL;
                }
                | STATEFUL SERVICE IDENTIFIER '{' service_body '}' ';' {
                  // printf("Stateful service seen: %s\n", $3);
                  currentService->SetName($3);
                  currentService->SetServiceType("stateful");
                  currentService = NULL;
                }

struct_body:    declarations;

declarations:   declarations declaration
                |
                ;

declaration:    LIST '<' TYPE '>' IDENTIFIER ORD ';' {
                  // printf("Declaration3 seen:    LIST<%s> %s %s\n", $3, $5, $6);
                  currentStruct->AddDeclaration(new ::naeem::hottentot::generator::ds::ListDeclaration($3, $5, $6));
                }
                | LIST '<' IDENTIFIER '>' IDENTIFIER ORD ';' {
                  // printf("Declaration4 seen:    LIST<%s> %s %s\n", $3, $5, $6);
                  currentStruct->AddDeclaration(new ::naeem::hottentot::generator::ds::ListDeclaration($3, $5, $6));
                }
                | SET '<' TYPE '>' IDENTIFIER ORD ';' {
                  // printf("Declaration5 seen:    SET<%s> %s %s\n", $3, $5, $6);
                  currentStruct->AddDeclaration(new ::naeem::hottentot::generator::ds::SetDeclaration($3, $5, $6));
                }
                | SET '<' IDENTIFIER '>' IDENTIFIER ORD ';' {
                  // printf("Declaration6 seen:    SET<%s> %s %s\n", $3, $5, $6);
                  currentStruct->AddDeclaration(new ::naeem::hottentot::generator::ds::SetDeclaration($3, $5, $6));
                }
                | MAP '<' TYPE ','  TYPE '>' IDENTIFIER ORD ';' {
                  // printf("Declaration7 seen:    MAP<%s, %s> %s %s\n", $3, $5, $7, $8);
                  currentStruct->AddDeclaration(new ::naeem::hottentot::generator::ds::MapDeclaration($3, $5, $7, $8));
                }
                | MAP '<' TYPE ','  IDENTIFIER '>' IDENTIFIER ORD ';' {
                  // printf("Declaration7 seen:    MAP<%s, %s> %s %s\n", $3, $5, $7, $8);
                  currentStruct->AddDeclaration(new ::naeem::hottentot::generator::ds::MapDeclaration($3, $5, $7, $8));
                }
                | MAP '<' IDENTIFIER ','  TYPE '>' IDENTIFIER ORD ';' {
                  // printf("Declaration8 seen:    MAP<%s, %s> %s %s\n", $3, $5, $7, $8);
                  currentStruct->AddDeclaration(new ::naeem::hottentot::generator::ds::MapDeclaration($3, $5, $7, $8));
                }
                | MAP '<' IDENTIFIER ','  IDENTIFIER '>' IDENTIFIER ORD ';' {
                  // printf("Declaration8 seen:    MAP<%s, %s> %s %s\n", $3, $5, $7, $8);
                  currentStruct->AddDeclaration(new ::naeem::hottentot::generator::ds::MapDeclaration($3, $5, $7, $8));
                }
                | TYPE IDENTIFIER ORD ';' {
                  // printf("Declaration seen:    %s %s %s\n", $1, $2, $3);
                  currentStruct->AddDeclaration(new ::naeem::hottentot::generator::ds::Declaration($1, $2, $3));
                }
                | IDENTIFIER IDENTIFIER ORD ';' {
                  // printf("Declaration2 seen:    %s %s %s\n", $1, $2, $3);
                  currentStruct->AddDeclaration(new ::naeem::hottentot::generator::ds::Declaration($1, $2, $3));
                }
                ;

service_body:   methods
                ;

methods:        methods method
                |
                ;

method:         LIST '<' TYPE '>' IDENTIFIER '(' ')' ';' {
                } 
                | LIST '<' IDENTIFIER '>' IDENTIFIER '(' ')' ';' {
                } 
                | SET '<' TYPE '>' IDENTIFIER '(' ')' ';' {
                }
                | SET '<' IDENTIFIER '>' IDENTIFIER '(' ')' ';' {
                }
                | MAP '<' TYPE ',' TYPE '>' IDENTIFIER '(' ')' ';' {
                }
                | MAP '<' TYPE ',' IDENTIFIER '>' IDENTIFIER '(' ')' ';' {
                }
                | MAP '<' IDENTIFIER ',' TYPE '>' IDENTIFIER '(' ')' ';' {
                }
                | MAP '<' IDENTIFIER ',' IDENTIFIER '>' IDENTIFIER '(' ')' ';' {
                }
                | TYPE IDENTIFIER '(' ')' ';' {
                }
                | IDENTIFIER IDENTIFIER '(' ')' ';' {
                }
                | LIST '<' TYPE '>' IDENTIFIER '(' arguments ')' ';' {
                } 
                | LIST '<' IDENTIFIER '>' IDENTIFIER '(' arguments ')' ';' {
                } 
                | SET '<' TYPE '>' IDENTIFIER '(' arguments ')' ';' {
                }
                | SET '<' IDENTIFIER '>' IDENTIFIER '(' arguments ')' ';' {
                }
                | MAP '<' TYPE ',' TYPE '>' IDENTIFIER '(' arguments ')' ';' {
                }
                | MAP '<' TYPE ',' IDENTIFIER '>' IDENTIFIER '(' arguments ')' ';' {
                }
                | MAP '<' IDENTIFIER ',' TYPE '>' IDENTIFIER '(' arguments ')' ';' {
                }
                | MAP '<' IDENTIFIER ',' IDENTIFIER '>' IDENTIFIER '(' arguments ')' ';' {
                }
                | TYPE IDENTIFIER '(' arguments ')' ';' {
                }
                | IDENTIFIER IDENTIFIER '(' arguments ')' ';' {
                }
                ;

arguments:      argument
                | argument ',' arguments
                ;

argument:       LIST '<' TYPE '>' IDENTIFIER {
                }
                | LIST '<' IDENTIFIER '>' IDENTIFIER {
                }
                | SET '<' TYPE '>' IDENTIFIER {
                }
                | SET '<' IDENTIFIER '>' IDENTIFIER {
                }
                | MAP '<' TYPE ',' TYPE '>' IDENTIFIER {
                }
                | MAP '<' TYPE ',' IDENTIFIER '>' IDENTIFIER {
                }
                | MAP '<' IDENTIFIER ',' TYPE '>' IDENTIFIER {
                }
                | MAP '<' IDENTIFIER ',' IDENTIFIER '>' IDENTIFIER {
                }
                | TYPE IDENTIFIER {
                }
                | IDENTIFIER IDENTIFIER {
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
  yyin = fopen(argv[1],"r+");
  if (!yyin) {
    printf("ERROR: File can't be opened.\n");
    return 1;
  }
  yyparse();
  return 0;
}