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
#include "y.tab.h"
%}
%%
int {
  fprintf(stdout, "INT seen.\n");
  yylval.string = malloc(yyleng); 
  sprintf(yylval.string, "%s", yytext);
  return TYPE;
}
double {
  fprintf(stdout, "DOUBLE seen.\n");
  yylval.string = malloc(yyleng); 
  sprintf(yylval.string, "%s", yytext);
  return TYPE;
}
string {
  fprintf(stdout, "STRING seen.\n");
  yylval.string = malloc(yyleng); 
  sprintf(yylval.string, "%s", yytext);
  return TYPE;
}
bool {
  fprintf(stdout, "BOOL seen.\n");
  yylval.string = malloc(yyleng); 
  sprintf(yylval.string, "%s", yytext);
  return TYPE;
}
module {
  fprintf(stdout, "MODULE seen.\n");
  return MODULE;
}
struct {
  fprintf(stdout, "STRUCT seen.\n");
  return STRUCT;
}
[a-zA-Z]([a-zA-Z0-9])* {
  fprintf(stdout, "IDENTIFIER seen.\n");
  yylval.string = malloc(yyleng); 
  sprintf(yylval.string, "%s", yytext);
  return IDENTIFIER;
}
[\{\}\;\.] { 
  fprintf(stdout, "'%c' seen.\n", *yytext);
  return *yytext; 
}
[ \t\r\n] ;
. { 
  fprintf(stderr, "Unknown token: %c\n", *yytext); 
}
%%