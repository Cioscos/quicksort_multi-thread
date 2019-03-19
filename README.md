# quicksort_multi-thread
Library for a multithreaded quick-sort written in C

In the test folder, there is a file called "main.c" with an example of how to use the library.
If you want to build the example:

## Build example
- In the directory:
```
mkdir build
cd build
gcc -Wall -Wextra -I../include -O3 ../source/mt_sort.c ../test/main.c -o test -lpthread
```
### WARNING!
The test generates 1 mln of numbers randomly; this means that the program needs almost 4Gb of RAM on your device.
