# mkdir

### Try it!
In order to compile this utility the following packages are needed:

`sudo apt install build-essential libboost-program-options-dev`

Then you can compile `mkdir.cpp` with:

`g++ mkdir.cpp -o mkdir -lboost_options -std=c++2a`

Then you can test it out with:

`./mkdir <options> <directory names>`
