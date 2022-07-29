#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
#include <mutex>
    using namespace std;
    using namespace std::chrono;
#include "facelet.h"
#include "cubie.h"
#include "streetCube.h"
int avgA[9]={0};
int avgB[9]={0};
int avgC[9]={0};
int avgD[9]={0};
int avgO[9]={0};
microseconds sumA;
microseconds sumB;
microseconds sumC;
microseconds sumD;
microseconds sumO;
mutex mA;
mutex mB;
mutex mC;
mutex mD;
mutex mO;
void res(int eo[], int co[], int a);
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

int c() // speed test
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
    return 0;
}

int d() //  
{
    CubieCube op = CubieCube();
    for (int i = 0; i < 4; i++)
    {
        printf("%c\n",itoe(edgeColor[op.ep[i]][ceo(op.eo,i)%2]));
        printf("%c\n",itoe(cornerColor[op.cp[i]][ceo(op.co,i)%3]));
    }
    return 0;
}
void fn(int ab[]) // thread function for checking all cubes
{
	int a = ab[0]; int b = ab[1];
	for(int c=0; c<6; c++)
    {
        for(int d=0; d<6; d++)
        {
            for(int e=0; e<6; e++)
            {
                for(int f=0; f<6; f++)
                {
                    for(int g=0; g<6; g++)
                    {
                        for(int h=0; h<6; h++)
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
                            auto start = high_resolution_clock::now();
                            auto stop = high_resolution_clock::now();
                            mO.lock();
                            avgO[checkD(eo,co,CubieCube())]++;
                            sumO += duration_cast<microseconds>(stop - start);
                            mO.unlock();
                            res(eo,co,0);
                        }
                    }
                }
            }
        }
    }
}
int main() // checks all possible cubes, returns time and percentage of cubes at distance after each step
{
    setup();
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    sumO = duration_cast<microseconds>(stop - start);
    sumA = duration_cast<microseconds>(stop - start);
    sumB = duration_cast<microseconds>(stop - start);
    sumC = duration_cast<microseconds>(stop - start);
    sumD = duration_cast<microseconds>(stop - start);
    thread th[36];
    for(int a=0; a<6; a++)
    {
        for(int b=0; b<6; b++)
        {
	        int ab[2]={a,b};
            th[a*6+b] = thread(fn,ab);
        }
    }
    for(int i=0; i<36; i++) th[i].join();
    int runs = pow(6,8);
    sumA /= runs;
    sumB /= runs;
    sumC /= runs;
    sumD /= runs;
    sumO /= runs;
    cout<<fixed<<setprecision(2);
    auto sumT = sumA+sumB+sumC+sumD+sumO;
    cout<<"\nTotal time (us): "<<sumT.count()<<endl;
    cout<<"benchmark time (us): "<<sumO.count()<<endl;
    for(int i=0; i<9; i++)
        cout<<i<<": "<<((avgO[i])/(double)runs)*100<<"%"<<endl;
    cout<<"OP time (us): "<<sumA.count()<<endl;
    for(int i=0; i<9; i++)
        cout<<i<<": "<<((avgA[i])/(double)runs)*100<<"%"<<endl;
    cout<<"T1 Parity time (us): "<<sumB.count()<<endl;
    for(int i=0; i<9; i++)
        cout<<i<<": "<<((avgB[i])/(double)runs)*100<<"%"<<endl;
    cout<<"SnS time (us): "<<sumC.count()<<endl;
    for(int i=0; i<9; i++)
        cout<<i<<": "<<((avgC[i])/(double)runs)*100<<"%"<<endl;
    cout<<"ReOri time (us): "<<sumD.count()<<endl;
    for(int i=0; i<9; i++)
        cout<<i<<": "<<((avgD[i])/(double)runs)*100<<"%"<<endl;
    return 0;
}

void res(int eo[], int co[], int a) // resolves cube state while checking time and distance
{
    CubieCube cube = CubieCube();
    auto start = high_resolution_clock::now();
    resOP(eo,co,&cube);
    auto stop = high_resolution_clock::now();
    mA.lock();
    avgA[checkD(eo,co,cube)]++;
    sumA += duration_cast<microseconds>(stop - start);
    mA.unlock();
    start = high_resolution_clock::now();
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
    }
    if(T1C)
    {
        cube*pariCubeT1C[T1C];
    }
    stop = high_resolution_clock::now();
    mB.lock();
    avgB[checkD(eo,co,cube)]++;
    sumB += duration_cast<microseconds>(stop - start);
    mB.unlock();
    start = high_resolution_clock::now();
    while(resSnS(eo,co,&cube));
    stop = high_resolution_clock::now();
    mC.lock();
    avgC[checkD(eo,co,cube)]++;
    sumC += duration_cast<microseconds>(stop - start);
    mC.unlock();
    start = high_resolution_clock::now();
    resOri(eo,co,&cube);
    stop = high_resolution_clock::now();
    mD.lock();
    avgD[checkD(eo,co,cube)]++;
    sumD += duration_cast<microseconds>(stop - start);
    mD.unlock();
}
int f() // used to test setup()
{
    setup();
    return 0;
}