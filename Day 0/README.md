# mkdir
The bash shell utility `mkdir` is a tool used to create directories in most POSIX environments. I thought it would be fun to implement such functionality from C++ and maybe forge in some of my own features in the future. I will be using the C++ library Boost to handle the command line options and the Standard Template Libary (std) to work work with the filesystem. I would appreciate some sustains, nays, and comments on the 50 so lines of code I have written.

### Try it!
In order to compile this utility the following packages are needed:

`sudo apt install build-essential libboost-program-options-dev`

Then you can compile `mkdir.cpp` with:

`g++ mkdir.cpp -o mkdir -lboost_options -std=c++2a`

Then you can test it out with:

`./mkdir <options> <directory names>`
