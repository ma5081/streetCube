#ifndef FACELET
#define FACELET
#include "move.h"
#include <iostream>    
    using namespace std;

FaceCube::FaceCube() // default constructor
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<9; j++) f[i*9+j]=i; //color
    }
}

void FaceCube::printA() // print all faces
{
    for(int j=0; j<6; j++)
    {
        this->printU(j);
        cout<<'\n';
    }
}
void FaceCube::printU(int j) // print 1 face
{
    string p = "";
    for(int i=1; i<=9; i++)
    {
        switch (f[j*9+i-1])
        {
        case U:
            p+='U';
            break;
        case R:
            p+='R';
            break;
        case F:
            p+='F';
            break;
        case D:
            p+='D';
            break;
        case L:
            p+='L';
            break;
        case B:
            p+='B';
            break;
        default:
            break;
        }
        if(!(i%3))p+='\n';
        else p+=' ';
    }
    cout<<p;
}

void FaceCube::operator=(FaceCube that) // copy FaceCube
{
    for(int i=0; i<54; i++)
        this->f[i] = that.f[i];
}
#endif