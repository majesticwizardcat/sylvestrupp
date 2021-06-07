# Marabu
[Block chain course](https://new.blockchain-course.org/protocol.md) assignment implementation written in C++.  

### Installation

- First Clone the repository and the init the submodules:  
`git clone git@github.com:loukoum/marabu`  
`git submodule init`  
`git submodule update`  

- Install [ASIO](https://think-async.com/Asio/) using your package manager. You need the standalone version not the boost one:  
`brew install asio`

- Install cmake to build, you will need a C++ compiler like gcc clang:  
`brew install cmake`  

- Create a build directory and run cmake:  
`mkdir build`  
`cd build`  
`cmake ..`  

