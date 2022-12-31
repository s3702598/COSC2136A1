COSC2136A1
Assignment 1 - Program planning 2D robot path.
Author: Honorata Trojanowska s3702598

Written and compiled using C++ 14 standard.

To compile: 
g++ -Wall -Werror -std=c++14 -O -o tests/a1 main.cpp Node.cpp NodeList.cpp PathSolver.cpp

To run: 
./a1

To test:
cd tests
./a1 <test01.env >actual.out
diff actual.out test01.out

Change corresponding test numbers in above code to proceeed with other tests.