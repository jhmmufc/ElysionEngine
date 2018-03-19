@echo off
title Engine source file generation
echo Starting generation of project source files using cmake
if not exist "\build\" mkdir build
cd build
cmake cmake -G "Visual Studio 15 2017" ../src