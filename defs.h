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
#define N_MOVE = 18  // number of possible face moves
#define N_PLL = 21 // number of PLLs
#define N_OLL = 57 // number of OLLs

// FaceCube defined
class FaceCube
{
public:
    int f[54];
    FaceCube();
    void printU(int j=0);
    void printA();
    void operator=(FaceCube);
};
// CubieCube defined
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

// rotations
// {U, R, F, D, L, B} <- without rotations
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
int ctor[6][6] = //color to relative conversion by color
{
    {U, R, F, D, L, B},
    {F, U, R, B, D, L},
    {R, F, U, L, B, D},
    {D, L, B, U, R, F},
    {B, D, L, F, U, R},
    {L, B, D, R, F, U}
};

char etoc[6] = {'Y','R','B','W','O','G'}; // color strings

string mtoc[18] = // strings for HTM moves
{
    "U/","U2","U'",
    "R/","R2","R'",
    "F/","F2","F'",
    "D/","D2","D'",
    "L/","L2","L'",
    "B/","B2","B'"
};
string pName[21] = // strings for the names of the Perms
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
int pow(int a, int b) // powers of 2 ints
{
    return (int)pow((double)a,(double)b);
}
int ceo(int eo, int e) // returns the binary value in given spot
{
    return (eo>>e)&1;
}
int cco(int co, int c) // returns ternary value in given slot inverted for color rather than placement
{
    int ret = (int)(co/(pow(3,c)))%3;
    return ret?(!(ret-1)+1):ret;
}
int uco(int co, int c) // returns ternary value in given slot
{
    return (int)(co/(pow(3,c)))%3;
}
int checkD(int eo[], int co[], CubieCube op) // checks cube distance
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
int a();
void getState(int[]); // gets cube state for access to res()
int etoi(char); // returns int of relative given the relative's char
char itoe(int); // returns char of relative given the int
CubieCube algo(string algs, CubieCube in=CubieCube()); // given a string, returns a cube with the operations done
void resOP(int[],int[],CubieCube*); // resolves OP
int resSnS(int[],int[],CubieCube*); // resolves SnS once
void resOri(int[],int[],CubieCube*); // resolves reOri
#endif