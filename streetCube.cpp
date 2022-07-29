#include <iostream>
#include <ctime>
    using namespace std;
#include "streetCube.h"
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
    cout<<itoe(co[ULB])<<" "<<itoe(eo[UB])<<" "<<itoe(co[UBR])<<endl
        <<itoe(eo[UL]) <<" "<<'U'         <<" "<<itoe(eo[UR]) <<endl
        <<itoe(co[UFL])<<" "<<itoe(eo[UF])<<" "<<itoe(co[URF])<<endl;
    cube = res(eo,co);
    cout<<cube.scramble<<endl;
}

// void getState(int b[])
// {
//     char c;
//     for(int i=0; i<8; i++)
//     {
//         cin>>c;
//         b[i] = etoi(c);
//         if(b[i]<0)
//             i--;
//     }
// }
void getState(int b[])
{
    char c;
    srand((unsigned)time(NULL));
    for(int i=0; i<8; i++)
    {
        b[i]=rand()%6;
    }
}