#include <iostream>
    using namespace std;
#include "facelet.h"
#include "cubie.h"

int main()
{
    setup();
    CubieCube cube = CubieCube();
    int* b = getState();
    int co[4];
    int eo[4];
    int j=0;
    int k=0;
    int* helpArr[8] = {&co[ULB], &eo[UB], &co[UBR], &eo[UL], &eo[UR], &co[UFL], &eo[UF], &co[URF]};
    for(int i = 0; i<8; i++)
    {
        if(b[i]==U) *helpArr[i]=0;
        else if(b[i]==D) *helpArr[i]=2;
        else *helpArr[i]=1;
    }
    int oPoints[57];
    fill_n(oPoints,57,9);
    for(int i=0; i<57; i++)
    {
        for(int u=-1; u<3; u++)
        {
            CubieCube comp = CubieCube()*orieCube[i];
            if(u>=0)
                comp*advMoveCube[u];
            int o = 0;
            for(int j=0; j<4; j++)
            {
                if(eo[j]==0)
                {
                    if(ceo(comp.eo,j)!=0)
                        o++;
                }
                if(co[j]==0)
                {
                    if(cco(comp.co,j)!=0)
                        o++;
                }
            }
            oPoints[i]=min(o,oPoints[i]);
        }
    }
    for(int i=0; i<57; i++)
    {
        if(oPoints[i]==0)
        {
            cube*orieCube[i];
            break;
        }
    }
    for(int i = 0; i<4; i++)
    {
        if(eo[i]==2)
        {
            cube*pariCubeT1[i];
        }
    }
    FaceCube projection = cube.translate();
    projection.printU();
}

int* getState()
{
    int* b = new int(8);
    char c;
    for(int i=0; i<8; i++)
    {
        cin>>c;
        switch (c)
        {
        case 'U':
            b[i]=U;
            break;
        case 'R':
            b[i]=R;
            break;
        case 'F':
            b[i]=F;
            break;
        case 'D':
            b[i]=D;
            break;
        case 'L':
            b[i]=L;
            break;
        case 'B':
            b[i]=B;
            break;
        default:
            i--;
            continue;
        }
    }
    return b;
}