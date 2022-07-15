#ifndef ENUMS
#define ENUMS
#include <iostream>

enum Facelet
{
    // Facelet Level
    U1,U2,U3,U4,U5,U6,U7,U8,U9,
    R1,R2,R3,R4,R5,R6,R7,R8,R9,
    F1,F2,F3,F4,F5,F6,F7,F8,F9,
    D1,D2,D3,D4,D5,D6,D7,D8,D9,
    L1,L2,L3,L4,L5,L6,L7,L8,L9,
    B1,B2,B3,B4,B5,B6,B7,B8,B9
};
enum Color
{
    // Side Color
    U, R, F, D, L, B
};
enum Corner
{
   // Corner Cubies
    URF,
    UFL,
    ULB,
    UBR,
    DFR,
    DLF,
    DBL,
    DRB
};

enum Edge
{
    // Edge Cubies
    UR,
    UF,
    UL,
    UB,
    DR,
    DF,
    DL,
    DB,
    FR,
    FL,
    BL,
    BR
};

enum Move
{
    // moves (forward - X/mid - X2/prime - X')
    Uf, Um, Up,
    Rf, Rm, Rp,
    Ff, Fm, Fp,
    Df, Dm, Dp,
    Lf, Lm, Lp,
    Bf, Bm, Bp
};

enum PLL
{
    // PLLs
    Aa, Ab,
    E,
    Ua, Ub,
    H,
    Z,
    Fl,
    T,
    V,
    Y,
    Ja, Jb,
    Ra, Rb,
    Na, Nb,
    Ga, Gb, Gc, Gd
};

enum BS
{
    // Basic Symmetries
    ROT_URF3,
    ROT_F2,
    ROT_U4,
    MIRR_LR2
};
#endif