<img src="https://github.com/LabCryptoOrg/hottentot/blob/master/docs/logo/hottentot.png" width="500px" />
# Hottentot RPC Framework
### About Hottentot
Hottentot is a RPC Framework. It allows developers to focus on their business on client and server sides. Hottentot is light weight and it does not need any additional dependency to get compiled and work. Currently, it generates source files for C++ and Java. Other languages will be added soon. See Examples section for going through a quick guide.

### Installation
#### Linux
First, download or clone the source code from Github. Then, install the dependencies for your own Linux disto. And at last, run `make` and `make install` in order to compile runtimes and generators. Dependencies for current Hottentot release are `build-essential`, `flex` and `bison`. Below, you will see a demonstration of Hottentot compilation in a Debian based distro.

```shell
 $ sudo apt-get install git build-essential bison flex
 $ git clone https://github.com/LabCryptoOrg/hottentot
 $ cd hottentot
 $ make
 $ sudo make install
 $ hot
```

You should see a help message explaining the parameters for `hot` executable.

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
