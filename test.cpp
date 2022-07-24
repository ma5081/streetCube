#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
    using namespace std;
    using namespace std::chrono;
#include "facelet.h"
#include "cubie.h"
// atomic<int> Q0;
// atomic<int> Q1;
// atomic<int> Q2;
// atomic<int> Q3;
// atomic<int> Q4;
// atomic<int> Q5;
// atomic<int> Q6;
// atomic<int> Q7;
// atomic<int>* avgD[]={&Q0,&Q1,&Q2,&Q3,&Q4,&Q5,&Q6,&Q7};
int avgA[9]={0};
int avgB[9]={0};
int avgD[9]={0};
microseconds sumT;
// atomic<int> counter;
// mutex m;
// mutex t;
// condition_variable cv;
int res(int eo[], int co[]);
int checkD(int eo[], int co[], CubieCube op)
{
    int curD=8;
    for(int p=0; p<4; p++)
    {
        if(eo[p]==edgeColor[op.ep[p]][ceo(op.eo,p)])
            curD--;
        if(co[p]==cornerColor[op.cp[p]][cco(op.co,p)])
            curD--;
    }
    return curD;
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

int c()
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

int d()
{
    CubieCube op = CubieCube();
    for (int i = 0; i < 4; i++)
    {
        printf("%c\n",itoe(edgeColor[op.ep[i]][ceo(op.eo,i)%2]));
        printf("%c\n",itoe(cornerColor[op.cp[i]][ceo(op.co,i)%3]));
    }
}

int main()
{
    setup();
    b();
    // for(int i=0; i<8; i++)
    //     atomic_init(avgD[i],0);
    // atomic_init(&counter,0);
    // for(int a=0; a<1; a++)
    // {
    //     for(int b=0; b<1; b++)
    //     {
    //         for(int c=0; c<1; c++)
    //         {
    //             for(int d=0; d<1; d++)
    //             {
    //                 for(int e=0; e<1; e++)
    //                 {
    //                     for(int f=0; f<1; f++)
    //                     {
    //                         for(int g=0; g<1; g++)
    //                         {
    //                             for(int h=0; h<1; h++)
    //                             {
    //                                 int arr[8]={a,b,c,d,e,f,g,h};
    //                                 int j=-1;
    //                                 int eo[4];
    //                                 int co[4];
    //                                 for(int i=0; i<4; i++)
    //                                 {
    //                                     j++;
    //                                     eo[i]=arr[j];
    //                                     j++;
    //                                     co[i]=arr[j];
    //                                 }
    //                                 int eoco[8];
    //                                 for(int i=0; i<4; i++){eoco[i]=eo[i];eoco[i+4]=co[i];}
    //                                 testOP(eoco);
    //                                 // counter++;
    //                                 // thread th(testOP,eoco);
    //                                 // th.detach();

    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     printf("%d/6 done\n",a);
    // }
    // unique_lock<mutex> lock(m);
    // cv.wait(lock,[]()
    // {
    // cout<<"time: "<<sumT.count()<<endl;
    srand((unsigned)time(NULL));
    auto start = high_resolution_clock::now();
    int runs=1000;
    for(int i=0;i<runs;i++)
    {
        printf("%d\n",i);
        int eoco[8];
        for(int i=0; i<8; i++){eoco[i]=rand()%6;}
        int eo[4];
        int co[4];
        for(int i=0; i<4; i++){eo[i]=(int)eoco[i];co[i]=(int)eoco[i+4];}
        avgD[res(eo,co)]++;
    }
    auto stop = high_resolution_clock::now();
    auto avgdur = duration_cast<microseconds>(stop - start)/runs;
    for(int i=0; i<9; i++)
        cout<<i<<": "<<((avgD[i])/(double)runs)*100<<"%"<<endl;
    cout<<endl;
    for(int i=0; i<9; i++)
        cout<<i<<": "<<((avgB[i])/(double)runs)*100<<"%"<<endl;
    cout<<endl;
    for(int i=0; i<9; i++)
        cout<<i<<": "<<((avgA[i])/(double)runs)*100<<"%"<<endl;
    cout<<avgdur.count()<<endl;
    // });
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
                if(eo[i]==edgeColor[cube->ep[q]][(1+ceo(cube->eo,q))%2])
                {
                    if(!(j%2)) *cube*advMoveCube[Dp];
                    *cube*pariCubeSnS[0][(j>1)+i*2];
                    // cout<<pariSnSA[0][(j>1)+i*2]<<endl;
                    r = 1;
                    break;
                }
                else if(eo[i]==edgeColor[cube->ep[q]][(ceo(cube->eo,q))%2])
                {
                    if(j) *cube*advMoveCube[Df+j-1];
                    *cube*pariCubeT1E[1<<i];
                    r = 1;
                    break;
                }
            }
        }
        if(co[i]!=cornerColor[cube->cp[i]][cco(cube->co,i)%3]) // scan and snap corner
        {
            // printf("SnS: c%d ",i);
            for(int j = 0; j<4; j++)
            {
                int q = (j+i)%4+4;
                if(co[i]==cornerColor[cube->cp[q]][(1+cco(cube->co,q))%3])
                {
                    // printf("ori 1 with c%d ",q);
                    int d=0;
                    if((q-4)/2!=i/2) d+=2; // if corner is not on the same face, D2
                    if((cornerFacelet[q][1]/9)%3 == 2) // if the interesting facelet is in F or B
                    {
                        if(j%2) d++; // if corner is in slot 1 or 3, use D/
                        else d+=3; // if corner is in slot 0 or 2, use D'
                    }
                    if(d) *cube*advMoveCube[Df+(d-1)%3];
                    // printf("d: %d\n",d);
                    *cube*pariCubeSnS[3][i*2+0]; 
                    // cout<<pariSnSA[3][i*2+0]<<endl;
                    r = 1;
                    break;
                }
                else if(co[i]==cornerColor[cube->cp[q]][(2+cco(cube->co,q))%3])
                {
                    // printf("ori 2 with c%d ",q);
                    int d=0;
                    if((q-4)/2!=i/2) d+=2; // if corner is not on the same face, D2
                    if((cornerFacelet[q][2]/9)%3 == 2) // if the interesting facelet is in F or B
                    {
                        if(j%2) d++; // if corner is in slot 1 or 3, use D/
                        else d+=3; // if corner is in slot 0 or 2, use D'
                    }
                    // printf("d: %d\n",d);
                    if(d) *cube*advMoveCube[Df+(d-1)%3];
                    *cube*pariCubeSnS[3][i*2+1];
                    r = 1;
                    break;
                }
                else if(co[i]==cornerColor[cube->cp[q]][(cco(cube->co,q))%3])
                {
                    //printf("ori 0 with c%d\n",q);
                    if(j) *cube*advMoveCube[Df+j-1];
                    *cube*pariCubeT1C[1<<i];
                    r = 1;
                    break;
                }
            }
        }
    }
    return r;
}
int res(int eo[], int co[])
{
    // cout<<itoe(co[ULB])<<itoe(eo[UB])<<itoe(co[UBR])<<endl
    //     <<itoe(eo[UL]) <<'U'         <<itoe(eo[UR]) <<endl
    //     <<itoe(co[UFL])<<itoe(eo[UF])<<itoe(co[URF])<<endl;
    CubieCube cube = CubieCube();
    cube*resOP(eo,co);
    avgA[checkD(eo,co,cube)]++;
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
        cube*pariCubeT1E[T1E];
    if(T1C)
        cube*pariCubeT1C[T1C];
    avgB[checkD(eo,co,cube)]++;
    while(resSnS(eo,co,&cube));
    return checkD(eo,co,cube);
}
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
void testOP(int eoco[])
{
    auto start = high_resolution_clock::now();
    int eo[4];
    int co[4];
    for(int i=0; i<4; i++){eo[i]=(int)eoco[i];co[i]=(int)eoco[i+4];}
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
    auto stop = high_resolution_clock::now();
    // t.lock();
    auto duration=duration_cast<microseconds>(stop - start);
    cout<<duration.count()<<endl;
    // t.unlock();
    avgD[minD]++;
    // lock_guard<mutex> lk(m);
    // counter--;
    // cv.notify_all();
}
int f()
{
    setup();

}