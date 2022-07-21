#include <iostream>
#include <ctime>
    using namespace std;
#include "facelet.h"
#include "cubie.h"

int main()
{
    setup();
    CubieCube cube = CubieCube();
    int b[8];
    getState(b);
    int co[4];
    int eo[4];
    int* helpArr[8] = {&co[ULB], &eo[UB], &co[UBR], &eo[UL], &eo[UR], &co[UFL], &eo[UF], &co[URF]};
    for(int i = 0; i<8; i++)
        *helpArr[i]=b[i];
    cout<<itoe(co[ULB])<<itoe(eo[UB])<<itoe(co[UBR])<<endl
        <<itoe(eo[UL]) <<'U'         <<itoe(eo[UR]) <<endl
        <<itoe(co[UFL])<<itoe(eo[UF])<<itoe(co[URF])<<endl;
    CubieCube minOP = resOP(eo,co);
    cube*minOP;
    int T1E = 0;
    int T1C = 0;
    for(int i = 0; i<4; i++)
    {
        if(eo[i]==D)
            T1E = T1E|1<<i;
        if(co[i]==D)
            T1C = T1C|1<<i;
    }
    cube*pariCubeT1E[T1E];
    cube*pariCubeT1C[T1C];
    FaceCube projection = cube.translate();
    projection.printU();
}

void getState(int b[])
{
    char c;
    for(int i=0; i<8; i++)
    {
        cin>>c;
        b[i] = etoi(c);
        if(b[i]<0)
            i--;
    }
}
// void getState(int b[])
// {
//     char c;
//     srand((unsigned)time(NULL));
//     for(int i=0; i<8; i++)
//     {
//         b[i]=rand()%6;
//     }
// }

CubieCube resOP(int eo[], int co[])
{
    for(int i=0; i<4; i++)
    {
        if(eo[i]!=U && eo[i]!=D)
            break;
        if(co[i]!=U && co[i]!=D)
            break;
        if(i==3)
            return CubieCube();
    }
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
    if(!oPoss) return CubieCube();
    int minD=8;
    CubieCube minOP = CubieCube();
    for(int p=0; p<4; p++)
    {
        if(eo[p]==D||eo[p]==edgeColor[minOP.ep[p]][ceo(minOP.eo,p)%2])
            minD--;
        if(co[p]==D||co[p]==cornerColor[minOP.cp[p]][cco(minOP.co,p)%3])
            minD--;
    }
    for(int i=0; i<57; i++) 
    {
        if(ceo(oPoss,i))
        {
            for(int j=0; j<21; j++)
            {
                for(int k=-1; k<3; k++)
                {
                    for(int u=0; u<4; u++) 
                    {
                        if(ceo(oU[i],u))
                        {
                            CubieCube op = CubieCube(permCube[j]);
                            int curD=8;
                            if(k>=0)
                                op*advMoveCube[k];
                            op*orieCube[i];
                            if(u>0)
                               op*advMoveCube[u-1];
                            for(int p=0; p<4; p++)
                            {
                                if(eo[p]==D||eo[p]==edgeColor[op.ep[p]][ceo(op.eo,p)%2])
                                    curD--;
                                if(co[p]==D||co[p]==cornerColor[op.cp[p]][cco(op.co,p)%3])
                                    curD--;
                            }
                            if(curD<minD)
                            {
                                minD = curD;
                                minOP = op;
                                if(!minD) return minOP;
                            }
                        }
                    }
                }
            }
        }
    }
    return minOP;
}