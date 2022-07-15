#include <iostream>
    using namespace std;
#include <chrono>
    using namespace std::chrono;
#include "facelet.h"
#include "cubie.h"
int a()
{
    char l[] = {'U','R','F','D','L','B'};
    for(int i=0; i<6; i++)
    {
        for(int j=1; j<10; j++)
        {
            cout<<l[i]<<j<<", ";
        }
        cout<<endl;
    }
    return 0;
}
int b() // checks if auto generated OLLs and PLLs only affect LL
{
    setup();
    for(int i=0; i<21; i++)
    {
        for(int j=4; j<8; j++)
        {
            if(permCube[i].cp[j]!=j)
                {
                    printf("cpP: %d\n", i);
                    break;
                }

        }
        for(int j=4; j<12; j++)
        {
            if(permCube[i].ep[j]!=j)
                {
                    printf("epP: %d\n", i);
                    permCube[i].translate().printA();
                    break;
                }
        }
        if(permCube[i].co!=0) 
            printf("coP: %d\n", i);
        if(permCube[i].eo!=0) 
            printf("eoP: %d\n", i);
    }
    for(int i=0; i<57; i++)
    {
        for(int j=4; j<8; j++)
        {
            if(orieCube[i].cp[j]!=j)
                {
                    printf("cpO: %d\n", i);
                    break;
                }

        }
        for(int j=4; j<12; j++)
        {
            if(orieCube[i].ep[j]!=j)
                {
                    printf("epO: %d\n", i);
                    orieCube[i].translate().printA();
                    break;
                }
        }
    }
    return 0;
}

int main()
{
    auto start = high_resolution_clock::now();
    setup();
    for(int q=0; q<3600; q++)
    {
        for(int i=0; i<57; i++)
        {
            for(int j=0; j<21; j++)
            {
                for(int k=0; k<3; k++)
                {
                    CubieCube cube = CubieCube()*permCube[j]*advMoveCube[k]*orieCube[i];
                }
                CubieCube cube = CubieCube()*permCube[j]*orieCube[i];
            }
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;
}