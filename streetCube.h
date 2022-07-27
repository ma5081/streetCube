#ifndef SCUBE
#define SCUBE
#include <iostream>
#include <ctime>
    using namespace std;
#include "facelet.h"
#include "cubie.h"
CubieCube res(int eo[], int co[])
{
    CubieCube cube = CubieCube();
    resOP(eo,co,&cube);
    int T1E = 0;
    int T1C = 0;
    for(int i = 0; i<4; i++)
    {
        if(eo[i]==D)
            T1E = T1E|1<<i;
        if(co[i]==D)
            T1C = T1C|1<<i;
    }
    if(T1E)
    {
        cube*pariCubeT1E[T1E];
        cube.scramble+="\n"+pariT1EA[T1E];
    }
    if(T1C)
    {
        cube*pariCubeT1C[T1C];
        cube.scramble+="\n"+pariT1CA[T1C];
    }
    cube.scramble+="\n";
    while(resSnS(eo,co,&cube));
    resOri(eo,co,&cube);
    return cube;
}
void resOri(int eo[], int co[], CubieCube *cube)
{
    for(int i=0; i<4; i++)
    {
        if(eo[i]!=edgeColor[cube->ep[i]][ceo(cube->eo,i)%2]) // reorient edge
        {
            cube->scramble+="\n"+pariOriEA[i];
            *cube*pariCubeOriE[i];
        }
        if(co[i]!=cornerColor[cube->cp[i]][cco(cube->co,i)%3])
        {
            bool b = co[i]!=cornerColor[cube->cp[i]][(1+cco(cube->co,i))%3];
            cube->scramble+="\n"+pariOriCA[i*2+b];
            *cube*pariCubeOriC[i*2+b];
        }
    }
}
int resSnS(int eo[], int co[], CubieCube *cube)
{
    int r = 0;
    for(int i = 0; i<4; i++)
    {
        if(eo[i]!=edgeColor[cube->ep[i]][ceo(cube->eo,i)%2]) // scan and snap edge
        {
            for(int j = 0; j<4; j++)
            {
                int q = (j+i)%4+4;
                int p = (j+i)%4+8;
                if(eo[i]==edgeColor[cube->ep[q]][(1+ceo(cube->eo,q))%2])
                {
                    if(!(j%2)) {*cube*advMoveCube[Dp];cube->scramble+=mtoc[Dp]+" ";}
                    cube->scramble+=pariSnSA[0][(j>1)+i*2]+" ";
                    *cube*pariCubeSnS[0][(j>1)+i*2];
                    r = 1;
                    break;
                }
                else if(eo[i]==edgeColor[cube->ep[q]][(ceo(cube->eo,q))%2])
                {
                    if(j) {*cube*advMoveCube[Df+j-1];cube->scramble+=mtoc[Df+j-1]+" ";}
                    cube->scramble+=pariT1EA[1<<i]+" ";
                    *cube*pariCubeT1E[1<<i];
                    r = 1;
                    break;
                }
                else if(eo[i]==edgeColor[cube->ep[p]][(1+ceo(cube->eo,p))%2]) // midlayer R/L
                {
                    int u = 0;
                    if((j+3)%4 > 1) // if edge is on the same layer
                    {
                        if(!(i%2)) // if the original piece is on R/L
                            u+=2;
                        else
                        {
                            if(j==3) u+=1;
                            else u+=3;
                        }
                    }
                    else if (i%2)
                    {
                        if(j==2) u+=1;
                        else u+=3;
                    }
                    if(u) 
                    {
                        int iadj = (i+u)%4; // finds new i
                        int jadj = (j-u+4)%4; // j in relation to the new adj
                        cube->scramble+=mtoc[u-1]+" ";
                        cube->scramble+=pariSnSA[4][iadj*2+(jadj==1)]+" ";
                        cube->scramble+=mtoc[2-(u-1)]+" ";
                        *cube*advMoveCube[u-1];
                        *cube*pariCubeSnS[4][iadj*2+(jadj==1)];
                        *cube*advMoveCube[2-(u-1)];
                    }
                    else
                        {*cube*pariCubeSnS[4][i*2+(j==1)];cube->scramble+=pariSnSA[4][i*2+(j==1)]+" ";} // i*2 gives the correct piece chosen, j==1 checks if the piece is the one on the right or left
                    r=1;
                    break;
                }
                else if(eo[i]==edgeColor[cube->ep[p]][(ceo(cube->eo,p))%2]) // midlayer F/B
                {
                    int u = 0;
                    if((j+3)%4 > 1) // if edge is on the same layer
                    {
                        if(i%2) // if the original piece is on F/B
                            u+=2;
                        else
                        {
                            if(j==3) u+=1;
                            else u+=3;
                        }
                    }
                    else if (!(i%2))
                    {
                        if(j==2) u+=1;
                        else u+=3;
                    }
                    if(u) 
                    {
                        int iadj = (i+u)%4; // finds the new i
                        int jadj = (j-u+4)%4; // finds the j in relation to new i
                        cube->scramble+=mtoc[u-1]+" ";
                        cube->scramble+=pariSnSA[4][iadj*2+(jadj==1)]+" ";
                        cube->scramble+=mtoc[2-(u-1)]+" ";
                        *cube*advMoveCube[u-1];
                        *cube*pariCubeSnS[4][iadj*2+(jadj==1)];
                        *cube*advMoveCube[2-(u-1)];
                    }
                    else
                        {*cube*pariCubeSnS[4][i*2+(j==1)];cube->scramble+=pariSnSA[4][i*2+(j==1)]+" ";} // i*2 gives the correct piece chosen, j==1 checks if the piece is the one on the front or back
                    r=1;
                    break;
                }
            }
        }
        if(co[i]!=cornerColor[cube->cp[i]][cco(cube->co,i)%3]) // scan and snap corner
        {
            for(int j = 0; j<4; j++)
            {
                int q = (j+i)%4+4;
                if(co[i]==cornerColor[cube->cp[q]][(1+cco(cube->co,q))%3])
                {
                    int d=0;
                    if((q-4)/2!=i/2) d+=2; // if corner is not on the same face, D2
                    if((cornerFacelet[q][1]/9)%3 == 2) // if the interesting facelet is in F or B
                    {
                        if(j%2) d++; // if corner is in slot 1 or 3, use D/
                        else d+=3; // if corner is in slot 0 or 2, use D'
                    }
                    if(d) {*cube*advMoveCube[Df+(d-1)%3];cube->scramble+=mtoc[Df+(d-1)%3]+" ";}
                    cube->scramble+=pariSnSA[3][i*2+0]+" ";
                    *cube*pariCubeSnS[3][i*2+0]; 
                    r = 1;
                    break;
                }
                else if(co[i]==cornerColor[cube->cp[q]][(2+cco(cube->co,q))%3])
                {
                    int d=0;
                    if((q-4)/2!=i/2) d+=2; // if corner is not on the same face, D2
                    if((cornerFacelet[q][2]/9)%3 == 2) // if the interesting facelet is in F or B
                    {
                        if(j%2) d++; // if corner is in slot 1 or 3, use D/
                        else d+=3; // if corner is in slot 0 or 2, use D'
                    }
                    if(d) {*cube*advMoveCube[Df+(d-1)%3];cube->scramble+=mtoc[Df+(d-1)%3]+" ";}
                    cube->scramble+=pariSnSA[3][i*2+1]+" ";
                    *cube*pariCubeSnS[3][i*2+1];
                    r = 1;
                    break;
                }
                else if(co[i]==cornerColor[cube->cp[q]][(cco(cube->co,q))%3])
                {
                    if(j) {*cube*advMoveCube[Df+j-1];cube->scramble+=mtoc[Df+j-1]+" ";}
                    cube->scramble+=pariT1CA[1<<i]+" ";
                    *cube*pariCubeT1C[1<<i];
                    r = 1;
                    break;
                }
            }
        }
    }
    return r;
}
void resOP(int eo[], int co[], CubieCube* cube)
{
    int uMin;
    int kMin;
    int oMin;
    int pMin;
    for(int i=0; i<4; i++)
    {
        if(eo[i]!=U && eo[i]!=D)
            break;
        if(co[i]!=U && co[i]!=D)
            break;
        if(i==3)
            return;
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
    if(!oPoss) return;
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
            for(int j=0; j<22; j++)
            {
                for(int k=-1; k<3; k++)
                {
                    for(int u=0; u<4; u++) 
                    {
                        if(ceo(oU[i],u))
                        {

                            CubieCube op = CubieCube();
                            if(j)
                                op*permCube[j-1];
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
                                uMin=u;
                                kMin=k+1;
                                oMin=i;
                                pMin=j;
                                minD = curD;
                                minOP = op;
                            }
                        }
                    }
                }
            }
        }
    }
    cube->scramble+="\n";
    if(pMin) cube->scramble+=pName[pMin-1]+" perm: "+permCubeA[pMin-1];
    if(pMin&&kMin) cube->scramble+=" ";
    if(kMin) cube->scramble+=mtoc[kMin-1];
    if(pMin||kMin) cube->scramble+="\n";
    cube->scramble+="OLL "+to_string(oMin)+": "+orieCubeA[oMin];
    if(uMin) cube->scramble+=" "+mtoc[uMin-1];
    *cube*minOP;
    return;
}
#endif