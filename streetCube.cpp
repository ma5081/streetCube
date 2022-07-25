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
    cout<<endl;
    cube.translate().printU();
    int T1E = 0;
    int T1C = 0;
    for(int i = 0; i<4; i++)
    {
        if(eo[i]==D)
            T1E = T1E|1<<i;
        if(co[i]==D)
            T1C = T1C|1<<i;
    }
    cout<<T1C<<endl;
    if(T1E)
        cube*pariCubeT1E[T1E];
    if(T1C)
        cube*pariCubeT1C[T1C];
    cout<<endl;
    cube.translate().printU();
    int r = 0;
    do
    {
        r = 0;
        for(int i = 0; i<4; i++)
        {
            if(eo[i]!=edgeColor[cube.ep[i]][ceo(cube.eo,i)%2]) // scan and snap edge
            {
                for(int j = 0; j<4; j++)
                {
                    int q = (j+i)%4+4;
                    int p = (j+i)%4+8;
                    if(eo[i]==edgeColor[cube.ep[q]][(1+ceo(cube.eo,q))%2])
                    {
                        if(!(j%2)) {cube*advMoveCube[Dp];printf("did D'\n");}
                        cube*pariCubeSnS[0][(j>1)+i*2];
                        cout<<pariSnSA[0][(j>1)+i*2]<<endl;
                        r = 1;
                        break;
                    }
                    else if(eo[i]==edgeColor[cube.ep[q]][(ceo(cube.eo,q))%2])
                    {
                        if(j) cube*advMoveCube[Df+j-1];
                        cube*pariCubeT1E[1<<i];
                        r = 1;
                        break;
                    }
                    else if(eo[i]==edgeColor[cube.ep[p]][(1+ceo(cube.eo,p))%2]) // midlayer R/L
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
                        cout<<"R/L "<<u<<" between e"<<i<<" and e"<<p<<endl;
                        if(u) 
                        {
                            int adj = ((j+i+3)%4)<1; // finds if the piece is on R=1 or L=0
                            int jadj = j-(i-!adj*2+4)%4;
                            advMoveCube[u-1];
                            cube*pariCubeSnS[4][adj*4+(jadj==1)];
                        }
                        else
                            cube*pariCubeSnS[4][i*2+(j==1)]; // i*2 gives the correct piece chosen, j==1 checks if the piece is the one on the right or left
                        r=1;
                        break;
                    }
                    else if(eo[i]==edgeColor[cube.ep[p]][(ceo(cube.eo,p))%2]) // midlayer F/B
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
                        cout<<"F/B "<<u<<" between e"<<i<<" and e"<<p<<endl;
                        if(u) 
                        {
                            int adj = ((j+i)%4)<1; // finds if the piece is on F=1 or B=0
                            int jadj = j-(i-!adj*2+1+4)%4;
                            advMoveCube[u-1];
                            cube*pariCubeSnS[4][adj*4+(jadj==1)];
                        }
                        else
                            cube*pariCubeSnS[4][i*2+(j==1)]; // i*2 gives the correct piece chosen, j==1 checks if the piece is the one on the front or back
                        r=1;
                        break;
                    }
                }
            }
            if(co[i]!=cornerColor[cube.cp[i]][cco(cube.co,i)%3]) // scan and snap corner
            {
                printf("SnS: c%d ",i);
                for(int j = 0; j<4; j++)
                {
                    int q = (j+i)%4+4;
                    if(co[i]==cornerColor[cube.cp[q]][(1+cco(cube.co,q))%3])
                    {
                        printf("ori 1 with c%d ",q);
                        int d=0;
                        if((q-4)/2!=i/2) d+=2; // if corner is not on the same face, D2
                        if((cornerFacelet[q][1]/9)%3 == 2) // if the interesting facelet is in F or B
                        {
                            if(j%2) d++; // if corner is in slot 1 or 3, use D/
                            else d+=3; // if corner is in slot 0 or 2, use D'
                        }
                        if(d) cube*advMoveCube[Df+(d-1)%3];
                        printf("d: %d\n",d);
                        cube*pariCubeSnS[3][i*2+0]; 
                        cout<<pariSnSA[3][i*2+0]<<endl;
                        r = 1;
                        break;
                    }
                    else if(co[i]==cornerColor[cube.cp[q]][(2+cco(cube.co,q))%3])
                    {
                        printf("ori 2 with c%d ",q);
                        int d=0;
                        if((q-4)/2!=i/2) d+=2; // if corner is not on the same face, D2
                        if((cornerFacelet[q][2]/9)%3 == 2) // if the interesting facelet is in F or B
                        {
                            if(j%2) d++; // if corner is in slot 1 or 3, use D/
                            else d+=3; // if corner is in slot 0 or 2, use D'
                        }
                        printf("d: %d\n",d);
                        if(d) cube*advMoveCube[Df+(d-1)%3];
                        cube*pariCubeSnS[3][i*2+1];
                        r = 1;
                        break;
                    }
                    else if(co[i]==cornerColor[cube.cp[q]][(cco(cube.co,q))%3])
                    {
                        printf("ori 0 with c%d\n",q);
                        if(j) cube*advMoveCube[Df+j-1];
                        cube*pariCubeT1C[1<<i];
                        r = 1;
                        break;
                    }
                }
            }
        }
    } while(r==1);
    cout<<endl;
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
    string a;
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
                                a = permCubeA[j]+" "+(char)k+" "+orieCubeA[i]+" "+(char)u;
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
    cout<<a<<endl;
    return minOP;
}