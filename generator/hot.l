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

%option noyywrap
%option never-interactive
%{
#include <stdio.h>

// #if defined(__WIN32__) || defined(__MACOS__)
#include "hot.tab.h"
// #else
// #include "y.tab.h"
// #endif

extern unsigned int lineCounter;

extern "C" int yylex();
%}
%x SINGLELINE_COMMENT MULTILINE_COMMENT
%%

"//" {
  BEGIN(SINGLELINE_COMMENT);
}
<SINGLELINE_COMMENT>. {
  // fprintf(stdout, "SINGLE LINE COMMENT seen: %s.\n", yytext);
}
<SINGLELINE_COMMENT>"\r\n" {
  lineCounter++;
  BEGIN(INITIAL);
}
<SINGLELINE_COMMENT>"\n" {
  lineCounter++;
  BEGIN(INITIAL);
}

"/*" {
  BEGIN(MULTILINE_COMMENT);
}
<MULTILINE_COMMENT>. {
  // fprintf(stdout, "MULTI LINE COMMENT seen: %s.\n", yytext);
}
<MULTILINE_COMMENT>"\r\n" {
  lineCounter++;
}
<MULTILINE_COMMENT>"\n" {
  lineCounter++;
}
<MULTILINE_COMMENT>"*/" {
  BEGIN(INITIAL); 
}

ord\([1-9][0-9]*\) {
  // fprintf(stdout, "ORD seen.\n");
  yylval.string = (char *)malloc(yyleng + 1); 
  sprintf(yylval.string, "%s", yytext);
  return ORD;
}
stateless {
  // fprintf(stdout, "STATELESS seen.\n");
  return STATELESS;
}
stateful {
  // fprintf(stdout, "STATEFUL seen.\n");
  return STATEFUL;
}
service {
  // fprintf(stdout, "SERVICE seen.\n");
  return SERVICE;
}
list {
  // fprintf(stdout, "LIST seen.\n");
  yylval.string = (char *)malloc(yyleng + 1); 
  sprintf(yylval.string, "%s", yytext);
  return LIST;
}
set {
  // fprintf(stdout, "SET seen.\n");
  yylval.string = (char *)malloc(yyleng + 1); 
  sprintf(yylval.string, "%s", yytext);
  return SET;
}
map {
  // fprintf(stdout, "MAP seen.\n");
  yylval.string = (char *)malloc(yyleng + 1); 
  sprintf(yylval.string, "%s", yytext);
  return MAP;
}
int {
  // fprintf(stdout, "INT seen.\n");
  yylval.string = (char *)malloc(yyleng + 1); 
  sprintf(yylval.string, "%s", yytext);
  return TYPE;
}
double {
  // fprintf(stdout, "DOUBLE seen.\n");
  yylval.string = (char *)malloc(yyleng + 1); 
  sprintf(yylval.string, "%s", yytext);
  return TYPE;
}
string {
  // fprintf(stdout, "STRING seen.\n");
  yylval.string = (char *)malloc(yyleng + 1); 
  sprintf(yylval.string, "%s", yytext);
  return TYPE;
}
bool {
  // fprintf(stdout, "BOOL seen.\n");
  yylval.string = (char *)malloc(yyleng + 1); 
  sprintf(yylval.string, "%s", yytext);
  return TYPE;
}
date {
  // fprintf(stdout, "DATE seen.\n");
  yylval.string = (char *)malloc(yyleng + 1); 
  sprintf(yylval.string, "%s", yytext);
  return TYPE;
}
module {
  // fprintf(stdout, "MODULE seen.\n");
  return MODULE;
}
struct {
  // fprintf(stdout, "STRUCT seen.\n");
  return STRUCT;
}
enum {
  return ENUM;
}
[0-9]([0-9])* {
  yylval.string = (char *)malloc(yyleng + 1); 
  sprintf(yylval.string, "%s", yytext);
  return NUMBER;
}
[a-zA-Z_]([a-zA-Z0-9_])* {
  // fprintf(stdout, "IDENTIFIER seen: %s\n", yytext);
  yylval.string = (char *)malloc(yyleng + 1); 
  sprintf(yylval.string, "%s", yytext);
  return IDENTIFIER;
}
[\{\}\;\.><,()=] { 
  // fprintf(stdout, "'%c' seen.\n", *yytext);
  return *yytext; 
}
\n {
  lineCounter++;
}
[ \t\r] ;
. { 
  // fprintf(stderr, "Line %d: Unknown token: %c\n", lineCounter, *yytext); 
}
%%
