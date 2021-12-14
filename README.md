# This Project is Implementation of Track-Oriented Multiple hypothesis Tracking Algorithm (C++ Version)

### Introduction
This is a baseline implementation of the Track-Oriented Multiple hypothesis Tracking Algorithm using the Maximum Weighted Independent Set to solve the global hypothesis problem.

### Required Packages
- CMake
- Eigen
- fmt
- glog

### Runing MHT
For the limit of free time, I only successfully run on the Ubuntu Systerm with C++11 and requires packages.  
It may have more supports in the future.

It is easily to run on the terminal with following commands:
```
cd $PROJECT_DIR
mkdir build
cmake -DUSE_DEBUG=on -B build && make -C build -j4          # USE_DEBUG=on would print track infos 
./build/run_track
```