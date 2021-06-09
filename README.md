C++ micro optimization examples
===============================

These are just some random examples for C++ micro optimizations. It would be great
to add more and more examples based on Agner Fog's Optimizing software in C++ book.
I am not expert in this topic at all, take nothing for granted here :)

Credits to Agner Fog, Timur Doumler, Chandler Carruth, and many others.
I put links to their videos and books.

Environment
-----------

 - Install https://github.com/google/benchmark
 - Install g++ or clang with -std=c++20 support
 - Install optional tools, e.g.: pacman -S base-devel perf cpupower kcachegrind valgrind sudo

Workflow
========

Set the CPU governor to performance mode
```
make cpu-on
```

Make commands
```
# clean
make clean

# build and run a single test file
make build-loop_unrolling
make run-loop_unrolling

# perf examples
make stat-branch_prediction
make record-abstract_machine
make report

# kcachegrind
make callgrind-global_storage
make kcachegrind

# just run everything
make
```

Set the CPU governor to powersave mode
```
make cpu-off
```
