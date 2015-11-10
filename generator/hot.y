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
void yyerror(char *);
%}
%union {
  char *string;
}
%token MODULE
%token STRUCT
%token <string> IDENTIFIER
%token <string> TYPE
%start hot
%%

hot:            modules { 
                  printf("HOT parsed.\n"); 
                }
                ;

modules:        modules module
                |
                ;

module:         MODULE package '{' module_body '}' ';' {
                  printf("Module parsed.\n");
                }
                ;

package:        IDENTIFIER package { 
                  printf("Package seen: %s\n", $1); 
                }
                | IDENTIFIER '.' package { 
                  printf("Package seen: %s\n", $1); 
                }
                |
                ;

module_body:    structs
                ;

structs:        structs struct
                |
                ;

struct:         STRUCT IDENTIFIER '{' struct_body '}' ';' {
                  printf("Struct seen: %s\n", $2);
                }

struct_body:    declarations;

declarations:   declarations declaration
                |
                ;

declaration:    TYPE IDENTIFIER ';' {
                  printf("Declaration seen:    %s %s\n", $1, $2);
                }
                | IDENTIFIER IDENTIFIER ';' {
                  printf("Declaration2 seen:    %s %s\n", $1, $2);
                }

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