#  The MIT License (MIT)
#
#  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#  
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#  
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.
#

compile:
	yacc -d hot.y
	g++ -c y.tab.c
	flex hot.l
	g++ -c lex.yy.c
	g++ -c cc/cc_generator.cc -o cc_generator.o
	g++ -c java/java_generator.cc -o java_generator.o
	g++ -c dep/fasthash.cc -o fasthash.o
	g++ y.tab.o lex.yy.o cc_generator.o java_generator.o fasthash.o -lfl -ll -o hot
java: compile
	./hot --java --out ../examples/authentication/java/src/main/java/example/generated test2.hot
	#./hot --java --out /home/developer/Desktop/gen test2.hot
cc: compile
	./hot --cc --out gen test2.hot
