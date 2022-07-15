#include <iostream>
    using namespace std;
#include "facelet.h"
#include "cubie.h"

// using the cube class created by Kociemba https://github.com/hkociemba/RubiksCube-TwophaseSolver

int main()
{
    CubieCube cube = CubieCube();
    FaceCube projection = FaceCube();
    string a = "";
    do{
        cube.print();
        projection.printA();
        cin>>a;
        cube = algo(a, cube);
        projection=cube.translate();
    } while (1);
}