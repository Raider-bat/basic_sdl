# Basic SDL Work

A small training project using the library SDL2

# Building With CMake

To build the project with CMake we’ll want to make a temporary build directory to store the various build artifacts so we don’t pollute our source directory with a bunch of junk. From this folder we can then run cmake -G "Your Generator" ../ and CMake will generate makefiles or project files for Your Generator. You can run cmake -H to see which generators are available on your system. You can also specify the build type with -DCMAKE_BUILD_TYPE=Type, passing Debug will use the debug flags we set above and likewise for Release.

```sh
$ mkdir build && cd build
$ cmake -G "Unix Makefiles"  -DCMAKE_BUILD_TYPE=Debug ../
$ make
$ make install
```
