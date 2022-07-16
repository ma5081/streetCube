#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
    using namespace std;
    using namespace std::chrono;
#include "facelet.h"
#include "cubie.h"
#include "streetCube.cpp"
atomic<int> Q0;
atomic<int> Q1;
atomic<int> Q2;
atomic<int> Q3;
atomic<int> Q4;
atomic<int> Q5;
atomic<int> Q6;
atomic<int> Q7;
atomic<int>* avgD[]={&Q0,&Q1,&Q2,&Q3,&Q4,&Q5,&Q6,&Q7};
microseconds sumT;
atomic<int> counter;
mutex m;
mutex t;
condition_variable cv;
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
    for(int i=0; i<8; i++)
        atomic_init(avgD[i],0);
    atomic_init(&counter,0);
    for(int a=0; a<2; a++)
    {
        for(int b=0; b<2; b++)
        {
            for(int c=0; c<2; c++)
            {
                for(int d=0; d<2; d++)
                {
                    for(int e=0; e<2; e++)
                    {
                        for(int f=0; f<2; f++)
                        {
                            for(int g=0; g<2; g++)
                            {
                                for(int h=0; h<2; h++)
                                {
                                    int arr[8]={a,b,c,d,e,f,g,h};
                                    int j=-1;
                                    int eo[4];
                                    int co[4];
                                    for(int i=0; i<4; i++)
                                    {
                                        j++;
                                        eo[i]=arr[j];
                                        j++;
                                        co[i]=arr[j];
                                    }
                                    int eoco[8];
                                    for(int i=0; i<4; i++){eoco[i]=eo[i];eoco[i+4]=co[i];}
                                    counter++;
                                    thread th(testOP,eoco);
                                    th.detach();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    unique_lock<mutex> lock(m);
    cv.wait(lock,[]()
    {
        cout<<"time: "<<sumT.count()<<endl;
        for(int i=0; i<8; i++)
            cout<<i<<": "<<(*(avgD[i])/pow(2.0,8.0))*100<<"%"<<endl;
    });
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
    t.lock();
    sumT+=duration_cast<microseconds>(stop - start);
    t.unlock();
    *avgD[minD]++;
    lock_guard<mutex> lk(m);
    counter--;
    cv.notify_all();
}