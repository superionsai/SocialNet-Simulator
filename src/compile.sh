#!/bin/bash
# ==========================================================
# SocialNet Project - Compile Script
# Location: src/
# Compiles all .cpp files in this folder into ./main
# Uses latest stable C++ standard (C++23)
# ==========================================================

set -e  # Exit immediately on error

echo "🔧 Compiling all .cpp files in $(pwd) ..."
echo "----------------------------------------------------------"

# Compile all cpp files with optimization and warnings
g++ -std=c++23 -O2 -Wall -Wextra *.cpp -o main

echo "✅ Compilation successful!"
echo "----------------------------------------------------------"
echo "🗂️  Executable created at: $(pwd)/main"
echo
echo "👉 Run the program using:"
echo "   ./main"
echo
