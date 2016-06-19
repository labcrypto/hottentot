<img src="https://github.com/LabCryptoOrg/hottentot/blob/master/docs/logo/hottentot.png" width="500px" />
# Hottentot RPC Framework
### About Hottentot
Hottentot is a RPC Framework. It allows developers to focus on their business on client and server sides. Hottentot is light weight and it does not need any additional dependency to get compiled and work. Currently, it generates source files for C++ and Java. Other languages will be added soon. See Examples section for going through a quick guide.

### Installation
#### Linux
First, install the few dependencies which they are ususally pre-isntalled on most systems. Then download or clone the source code from Github. And at last, run `make` and `make install` in order to compile runtimes and generators. Dependencies for current Hottentot release are `build-essential`, `flex` and `bison`. Below, you will see a demonstration of Hottentot compilation in a Debian-based distro.

```shell
 $ sudo apt-get install git build-essential bison flex
 $ git clone https://github.com/LabCryptoOrg/hottentot
 $ cd hottentot
 $ make
 $ sudo make install
 $ hot
```

You should see a help message explaining the parameters for `hot` executable. Below is an exmaple.

```shell
$ hot
 ERROR: Target language is not specified

 Hottentot Serialization and RPC Framework
 LabCrypto Org. 2015-2016 Copyright
 Usage: hot [OPTION]... [HOT-FILE]...
   OPTIONS:
     --java                     Generate java sources. [Default: MANDATORY]
     --cc                       Generate C++ sources. [Default: MANDATORY]
     --makefile                 Generate Makefile for C++ sources. [Default: disabled]
     --client                   Generate sources for C++ client. [Default: disabled]
     --stub                     Generate a C++ stub for service. [Default: disabled]
     --indent-with-spaces       Generator will produce indents using spaces. [Default: enabled]
     --indent-with-tabs         Generator will produce indents using tabs. [Default: disabled]
     --indent-space-count       Number of spaces for producing a single indent. [Default: 2]
     --out                      Path to output directory. [Default: MANDATORY]
     --parse                    Displays parse result in a tree format. [Default: disabled]
     --dont-generate            Don\'t generate sources. [Default: disabled]
     --extend-module            A dot seperated string which will be added to module. [Default: '']
     --pom                      Generate POM file for java sources. [Default: disabled]
     --pom-group-id             GroupId of POM file. [Default: MANDATORT IF POM SPECIFIED.]
     --pom-artifact-id          ArtifactId of POM file. [Default: MANDATORT IF POM SPECIFIED.]
     --pom-version              Version of POM file. [Default: MANDATORT IF POM SPECIFIED.]

 For more information and examples, please visit https://github.com/LabCryptoOrg/hottentot

```

#### Windows

Support for Windows exists. We will add documentation so soon.

### Examples

#### Echo Server

First of all, you need to define a common interface between client and server. We call it HOT interface.
HOT interfaces should be saved to `.hot` files. This is our first simple HOT interface:

```
module ir.ntnaeem.hottentot.examples.echoserver {
  stateless service Echo {
    string say(string message);
  };  
};

```
Our HOT interface consists of a module which it has a stateless service inside. Echo service has a method which echos whatever has been passed to it. The interface is saved in a file named `echo.hot`. We generate our final source codes using the command below:

```shell
 
 $ hot --cc echo.hot

```

### Developers

Kamran Amini  (kam.cpp@gmail.com)
Ali Sharifi   (alisharifi01@gmail.com)
