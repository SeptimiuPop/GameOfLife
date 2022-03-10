#!/bin/bash

clear
cd bin

echo "Building the test enviroment..."
echo

g++ -c ../test/*.cpp -I ../App/headers
g++ *.o -o mainTest.exe -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system # to link.

./mainTest.exe 

cd ..
ls App/src