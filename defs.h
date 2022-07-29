#ifndef DEFS
#define DEFS
#include "enums.h"
#include <math.h>
#include <iostream>
    using namespace std;
// Map the corner positions to facelet positions.
int cornerFacelet[8][3] = 
            {
                {U9, R1, F3}, {U7, F1, L3}, {U1, L1, B3}, {U3, B1, R3},
                {D3, F9, R7}, {D1, L9, F7}, {D7, B9, L7}, {D9, R9, B7}
            };

// Map the edge positions to facelet positions.
int edgeFacelet[12][2] = 
            {
               {U6, R2}, {U8, F2}, {U4, L2}, {U2, B2}, {D6, R8}, {D2, F8},
               {D4, L8}, {D8, B8}, {F6, R4}, {F4, L6}, {B6, L4}, {B4, R6}
            };

// Map the corner positions to facelet colors.
int cornerColor[8][3] = 
            {
                {U, R, F}, {U, F, L}, {U, L, B}, {U, B, R},
                {D, F, R}, {D, L, F}, {D, B, L}, {D, R, B}
            };

// Map the edge positions to facelet colors.
int edgeColor[12][2] = 
            {
                {U, R}, {U, F}, {U, L}, {U, B}, {D, R}, {D, F},
                {D, L}, {D, B}, {F, R}, {F, L}, {B, L}, {B, R}
            };

// "constants"
#define N_PERM_4 = 24
#define N_CHOOSE_8_4 = 70

//
#define N_MOVE = 18  // number of possible face moves
#define N_PLL = 21 // number of PLLs
#define N_OLL = 57 // number of OLLs
//

#define N_TWIST = 2187  // 3^7 possible corner orientations in phase 1
#define N_FLIP = 2048  // 2^11 possible edge orientations in phase 1
#define N_SLICE_SORTED = 11880  // 12*11*10*9 possible positions of the FR, FL, BL, BR edges in phase 1
#define N_SLICE = N_SLICE_SORTED/N_PERM_4  // we ignore the permutation of FR, FL, BL, BR in phase 1
#define N_FLIPSLICE_CLASS = 64430  // number of equivalence classes for combined flip+slice concerning symmetry group D4h

#define N_U_EDGES_PHASE2 = 1680  // number of different positions of the edges UR, UF, UL and UB in phase 2
#define N_CORNERS = 40320  // 8! corner permutations in phase 2
#define N_CORNERS_CLASS = 2768  // number of equivalence classes concerning symmetry group D4h
#define N_UD_EDGES = 40320  // 8! permutations of the edges in the U-face and D-face in phase 2

#define N_SYM = 48  // number of cube symmetries of full group Oh
#define N_SYM_D4h = 16  // Number of symmetries of subgroup D4h

class FaceCube
{
public:
    int f[54];
    FaceCube();
    void printU(int j=0);
    void printA();
    void operator=(FaceCube);
};
class CubieCube
{
public:
    string scramble;
    int cp[8];
    int co;
    int ep[12];
    int eo;
    int r[6] = {U, R, F, D, L, B};

    CubieCube();
    CubieCube(int[], int, int[], int);
    CubieCube(string);
    CubieCube(CubieCube* that);
    void print();
    FaceCube translate();
    void rotRes(int,int);
    void edgeMult(CubieCube* that);
    void cornMult(CubieCube* that);
    void operator=(CubieCube* that);
    void operator=(CubieCube);
    bool operator==(CubieCube* that);
    CubieCube* operator*(CubieCube* that);
    CubieCube operator*(CubieCube that);
    CubieCube operator*(int);
};
// {U, R, F, D, L, B}
int rot[9][6] =
{
    {U, B, R, D, F, L},
    {U, L, B, D, R, F},
    {U, F, L, D, B, R},
    {F, R, D, B, L, U},
    {D, R, B, U, L, F},
    {B, R, U, F, L, D},
    {L, U, F, R, D, B},
    {D, L, F, U, R, B},
    {R, D, F, L, U, B}
};
// UI helpers
int rtoc[6][6] = //relative to color conversion by respective U
{
    {Yellow, Red, Blue, White, Orange, Green},
    {Red, Blue, Yellow, Orange, Green, White},
    {Blue, Yellow, Red, Green, White, Orange},
    {White, Green, Orange, Yellow, Blue, Red},
    {Green, Orange, White, Blue, Red, Yellow},
    {Orange, White, Green, Red, Yellow, Blue}
};
int ctor[6][6] =
{
    {U, R, F, D, L, B},
    {F, U, R, B, D, L},
    {R, F, U, L, B, D},
    {D, L, B, U, R, F},
    {B, D, L, F, U, R},
    {L, B, D, R, F, U}
};
char etoc[6] = {'Y','R','B','W','O','G'};
string mtoc[18] = 
{
    "U/","U2","U'",
    "R/","R2","R'",
    "F/","F2","F'",
    "D/","D2","D'",
    "L/","L2","L'",
    "B/","B2","B'"
};
string pName[21] =
{
    "Aa", "Ab",
    "E",
    "Ua", "Ub",
    "H",
    "Z",
    "F",
    "T",
    "V",
    "Y",
    "Ja", "Jb",
    "Ra", "Rb",
    "Na", "Nb",
    "Ga", "Gb", "Gc", "Gd"
};
// helper functions
int pow(int a, int b)
{
    return (int)pow((double)a,(double)b);
}
int ceo(int eo, int e)
{
    return (eo>>e)&1;
}
int cco(int co, int c)
{
    //CHANGED FOR TESTING
    int ret = (int)(co/(pow(3,c)))%3;
    return ret?(!(ret-1)+1):ret;
}
int uco(int co, int c)
{
    return (int)(co/(pow(3,c)))%3;
}
int a();
void getState(int[]);
int etoi(char);
char itoe(int);
CubieCube algo(string algs, CubieCube in=CubieCube());
void resOP(int[],int[],CubieCube*);
int resSnS(int[],int[],CubieCube*);
void resOri(int[],int[],CubieCube*);
void testOP(int eoco[]);
#endif