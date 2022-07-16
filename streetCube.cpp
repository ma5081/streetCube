#include <iostream>
    using namespace std;
#include "facelet.h"
#include "cubie.h"

int notmain()
{
    setup();
    CubieCube cube = CubieCube();
    int* b = getState();
    int co[4];
    int eo[4];
    int* helpArr[8] = {&co[ULB], &eo[UB], &co[UBR], &eo[UL], &eo[UR], &co[UFL], &eo[UF], &co[URF]};
    for(int i = 0; i<8; i++)
        *helpArr[i]=b[i];
    CubieCube minOP = resOP(eo,co);
    cube*minOP;
    for(int i = 0; i<4; i++)
    {
        if(eo[i]==D)
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
        b[i] = etoi(c);
        if(b[i]<0)
            i--;
    }
    return b;
}

CubieCube resOP(int eo[], int co[])
{
        long oPoss=0;
    int oU[57]={};
    for(int i=0; i<57; i++) //check for U congruent OLLs
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
                if(o) break;
            }
            if(!o){oPoss = oPoss|(1<<i);oU[i]=oU[i]|(1<<(u+1));}
        }
    }
    int minD=9;
    CubieCube minOP = CubieCube();
    for(int i=0; i<57; i++) 
    {
        if(ceo(oPoss,i))
        {
            for(int j=0; j<21; j++)
            {
                for(int k=-1; k<3; k++)
                {
                    for(int u=-1; u<3; u++) 
                    {
                        if(ceo(oU[i],u))
                        {
                            CubieCube op = CubieCube(permCube[j]);
                            int curD=8;
                            if(k>=0)
                                op*advMoveCube[k];
                            op*orieCube[i];
                            if(u>=0)
                               op*advMoveCube[u];
                            for(int p=0; p<4; p++)
                            {
                                if(eo[i]==D||eo[i]==(edgeColor[op.ep[i]][ceo(op.eo,i)%2]))
                                    curD--;
                                if(co[i]==D||co[i]==cornerColor[op.cp[i]][ceo(op.co,i)%3])
                                    curD--;
                            }
                            if(curD<minD)
                            {
                                minD = curD;
                                minOP = op;
                            }
                        }
                    }
                }
            }
        }
    }
    return minOP;
}