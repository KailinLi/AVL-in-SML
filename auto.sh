#!/bin/bash
clang++ random.cc
./a.out
time ./c
time sml avl.sml
diff output.sml output.txt