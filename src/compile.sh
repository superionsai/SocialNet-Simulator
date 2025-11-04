#!/bin/bash
set -e
cd src

g++ -std=c++17 -O2 main.cpp socialnet.cpp avl.cpp avl.hpp socialnet.hpp -o main

./main.exe

echo "✅ Build complete. Run with: ./main"
