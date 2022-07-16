#ifndef HELPER
#define HELPER
#include <iostream>
 using namespace std;
#include <sstream>
#include "move.h"

int rotRes(int a, int r[])
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<r[i]; j++)
        {
            a = rot[i][a];
        }
    }
    return a;
}

CubieCube algo(string algs, CubieCube in)
{
    istringstream alg = istringstream(algs);

    CubieCube cube = CubieCube(in);
    int b=-1;
    int d=0;
    //alg>>a;
    while (!alg.eof())
    {
        int m[3] = {-1,0,0}; // extra move / rotation axis / f or null or p
        char a = '\0';
        char c = '\0';
        alg>>a;
        switch (a)
        {
        case 'E':
            m[0] = D;
        case 'd':
            m[1] = 0;
            m[2] = 3;
        case 'U':
            b=U;
            break;
        case 'M':
            m[0] = L;
        case 'l':
            m[1] = 1;
            m[2] = 3;
        case 'R':
            b=R;
            break;
        case 'b':
            m[1] = 2;
            m[2] = 3;
        case 'F':
            b=F;
            break;
        case 'u':
            m[1] = 0;
            m[2] = 1;
        case 'D':
            b=D;
            break;
        case 'r':
            m[1] = 1;
            m[2] = 1;
        case 'L':
            b=L;
            break;
        case 'S':
            m[0] = F;
        case 'f':
            m[1] = 2;
            m[2] = 1;
        case 'B':
            b=B;
            break;
        case 'x':
            m[1] = 1;
            m[2] = 1;
            b=-1;
            break;
        case 'y':
            m[1] = 0;
            m[2] = 1;
            b=-1;
            break;
        case 'z':
            m[1] = 2;
            m[2] = 1;
        default:
            b=-1;
            break;
        }

        alg>>c;
        switch(c)
        {
        case '3':
        case '\'':
            d = 2;
            if(m[2])
                cube.r[m[1]] = (cube.r[m[1]]+m[2]+2)%4;
            break;
        case '2':
            d = 1;
            if(m[2])
                cube.r[m[1]] = (cube.r[m[1]]+2)%4;
            break;
        default:
            d = 0;
            if(m[2])
                cube.r[m[1]] = (cube.r[m[1]]+m[2])%4;
            break;
        }
        if(b<0) continue;
        
        b = rotRes(b, cube.r); //rotation resolve
        b *= 3; //turn X to Xf (color to move)
        cube*advMoveCube[b+d];
        if(m[0]>=0)
        {
            m[0] = rotRes(m[0],cube.r); //rotation resolve
            m[0] *= 3; //turn X to Xf (color to move)
            m[0] += 2; //make it the opposite move
            cube*advMoveCube[m[0]-d];
        }
    }
    return cube;
}

void setup()
{
    for(int i=0; i<21; i++)
        permCube[i] = CubieCube(permCubeA[i]);
    for(int i=0; i<57; i++)
        orieCube[i] = CubieCube(orieCubeA[i]);
}

int etoi(char c) //convert enum name to number
{
    switch (c)
        {
        case 'U':
            return U;
        case 'R':
            return R;
        case 'F':
            return F;
        case 'D':
            return D;
        case 'L':
            return L;
        case 'B':
            return B;
        default:
            return -1;
        }
}
char itoe(int i) //converts enum number to name
{
        switch (i)
        {
        case U:
            return 'U';
        case R:
            return 'R';
        case F:
            return 'F';
        case D:
            return 'D';
        case L:
            return 'L';
        case B:
            return 'B';
        default:
            return '\0';
        }
}
#endif