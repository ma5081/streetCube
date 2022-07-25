#ifndef MOVES
#define MOVES
#include "defs.h"

// perm: array of corners/edges
// ortn: 
//      C: 3^URF +3^UFL +3^ULB +3^UBR +3^DFR +3^DLF +3^DBL +3^DRB
//      E: 2^UR | 2^UF | 2^UL | 2^UB | 2^DR | 2^DF | 2^DL | 2^DB | 2^FR | 2^FL | 2^BL | 2^BR
/* Control
int cpU[8] = {URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB};
int coU = 0;
int epU[12] = {UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR};
int eoU = 0; */

// U
int cpU[8]  = {UBR, URF, UFL, ULB, DFR, DLF, DBL, DRB};
int coU     = 0;
int epU[12] = {UB, UR, UF, UL, DR, DF, DL, DB, FR, FL, BL, BR};
int eoU     = 0;

// R
int cpR[8]  = {DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR};
int coR     = 2*pow(3,URF) +pow(3,UBR) +pow(3,DFR) +2*pow(3,DRB);
int epR[12] = {FR, UF, UL, UB, BR, DF, DL, DB, DR, FL, BL, UR};
int eoR     = 0;

// F
int cpF[8]  = {UFL, DLF, ULB, UBR, URF, DFR, DBL, DRB};
int coF     = pow(3,URF) +2*pow(3,UFL) +2*pow(3,DFR) +pow(3,DLF);
int epF[12] = {UR, FL, UL, UB, DR, FR, DL, DB, UF, DF, BL, BR};
int eoF     = 1<<UF  |  1<<DF  |  1<<FR | 1<<FL;

// D
int cpD[8]  = {URF, UFL, ULB, UBR, DLF, DBL, DRB, DFR};
int coD     = 0;
int epD[12] = {UR, UF, UL, UB, DF, DL, DB, DR, FR, FL, BL, BR};
int eoD     = 0;

// L
int cpL[8]  = {URF, ULB, DBL, UBR, DFR, UFL, DLF, DRB};
int coL     = pow(3,UFL) +2*pow(3,ULB) +2*pow(3,DLF) +pow(3,DBL);
int epL[12] = {UR, UF, BL, UB, DR, DF, FL, DB, FR, UL, DL, BR};
int eoL     = 0;

// B
int cpB[8]  = {URF, UFL, UBR, DRB, DFR, DLF, ULB, DBL};
int coB     = pow(3,ULB) +2*pow(3,UBR) +2*pow(3,DBL) +pow(3,DRB);
int epB[12] = {UR, UF, UL, BR, DR, DF, DL, BL, FR, FL, UB, DB};
int eoB     = 1<<UB  |  1<<DB  |  1<<BR | 1<<BL;

CubieCube basicMoveCube[6] =
{
    CubieCube(cpU, coU, epU, eoU),
    CubieCube(cpR, coR, epR, eoR),
    CubieCube(cpF, coF, epF, eoF),
    CubieCube(cpD, coD, epD, eoD),
    CubieCube(cpL, coL, epL, eoL),
    CubieCube(cpB, coB, epB, eoB)
};
CubieCube advMoveCube[18] =
{
    basicMoveCube[U], basicMoveCube[U]*2, basicMoveCube[U]*3,
    basicMoveCube[R], basicMoveCube[R]*2, basicMoveCube[R]*3,
    basicMoveCube[F], basicMoveCube[F]*2, basicMoveCube[F]*3,
    basicMoveCube[D], basicMoveCube[D]*2, basicMoveCube[D]*3,
    basicMoveCube[L], basicMoveCube[L]*2, basicMoveCube[L]*3,
    basicMoveCube[B], basicMoveCube[B]*2, basicMoveCube[B]*3
};
string pariT1EA[16] = //algorithms to move white edges to the top layer (any combinations)
{
    "", //none
    "S/ D2 S'", //0
    "M/ D2 M'", //1
    "M/ S/ D2 S' M'", //0|1 //
    "S' D2 S/", //2
    "y/ M' U2 M2 U2 M' y'", //2|0 //
    "M/ S' D2 S/ M'", //2|1 //
    "M/ D2 M' y/ M' U2 M2 U2 M' y'", //2|1|0
    "M' D2 M/", //3
    "M' S/ D2 S' M/", //3|0 //
    "M' U2 M2 U2 M'", //3|1
    "M' U2 M2 U2 M' S/ D2 S'", //3|1|0 //
    "M' S' D2 S/ M/", //3|2 //
    "M' D2 M/ y/ M' U2 M2 U2 M' y'", //3|2|0
    "M' U2 M2 U2 M' S' D2 S/", //3|2|1
    "M' U2 M2 U2 M' y/ M' U2 M2 U2 M' y'", //3|2|1|0
};
string pariT1CA[16] = //algorithms to move white corners to the top layer (any combinations)
{
    "", //none
    "R' D2 R/ D/ R' D' R/", //0
    "L/ D2 L' D' L/ D/ L'", //1
    "L/ R' D2 L' R/", //0|1
    "L' D2 L/ D/ L' D' L/", //2
    "R' D2 R/ D/ R' D' R/ L' D/ L/", //2|0
    "S/ L2 S'", //2|1
    "S/ L2 S' R' D2 R/ D/ R' D' R/", //2|1|0
    "R/ D2 R' D' R/ D/ R'", //3
    "S' R2 S/", //3|0
    "L/ D2 L' D' L/ D/ L' R/ D' R'", //3|1 
    "S' R2 S/ L/ D2 L' D' L/ D/ L'", //3|1|0
    "L' R/ D2 L/ R'", //3|2
    "S' R2 S/ L' D2 L/ D/ L' D' L/", //3|2|0
    "S/ L2 S' R/ D2 R' D' R/ D/ R'", //3|2|1
    "x' M' D2 U2 M' x/ D2 M2", //3|2|1|0
};
string permCubeA[21] = //algorithms for PLL taken from https://jperm.net/algs/pll
{
    "x/ R' U/ R' D2 R/ U' R' D2 R2 x'",
    "x/ R2 D2 R/ U/ R' D2 R/ U' R/ x'",
    "x' R/ U' R' D/ R/ U/ R' D' R/ U/ R' D/ R/ U' R' D' x/",
    "M2 U/ M/ U2 M' U/ M2",
    "M2 U' M/ U2 M' U' M2",
    "M2 U/ M2 U2 M2 U/ M2",
    "M' U/ M2 U/ M2 U/ M' U2 M2",
    "R' U' F' R/ U/ R' U' R' F/ R2 U' R' U' R/ U/ R' U/ R/",
    "R/ U/ R' U' R' F/ R2 U' R' U' R/ U/ R' F'",
    "R' U/ R' U' y/ R' F' R2 U' R' U/ R' F/ R/ F y'",
    "F/ R/ U' R' U' R/ U/ R' F' R/ U/ R' U' R' F/ R/ F'",
    "x/ R2 F/ R/ F' R/ U2 r' U/ r/ U2 x'",
    "R/ U/ R' F' R/ U/ R' U' R' F/ R2 U' R'",
    "R/ U' R' U' R/ U/ R/ D/ R' U' R/ D' R' U2 R'",
    "R2 F/ R/ U/ R/ U' R' F' R/ U2 R' U2 R/",
    "R/ U/ R' U/ R/ U/ R' F' R/ U/ R' U' R' F/ R2 U' R' U2 R/ U' R'",
    "R' U/ R/ U' R' F' U' F/ R/ U/ R' F/ R' F' R/ U' R/",
    "R2 U/ R' U/ R' U' R/ U' R2 U' D/ R' U/ R/ D'",
    "R' U' R/ U/ D' R2 U/ R' U/ R/ U' R/ U' R2 D/",
    "R2 U' R/ U' R/ U/ R' U/ R2 U/ D' R/ U' R' D/",
    "R/ U/ R' U' D/ R2 U' R/ U' R' U/ R' U/ R2 D'"
};
string orieCubeA[57] = //algorithms for OLL taken from https://jperm.net/algs/oll
{
    "R/ U2 R2 F/ R/ F' U2 R' F/ R/ F'",
    "r/ U/ r' U2 r/ U2 R' U2 R/ U' r'",
    "r' R2 U/ R' U/ r/ U2 r' U/ M'",
    "M/ U' r/ U2 r' U' R/ U' R' M'",
    "l' U2 L/ U/ L' U/ l/",
    "r/ U2 R' U' R/ U' r'",
    "r/ U/ R' U/ R/ U2 r'",
    "l' U' L/ U' L' U2 l/",
    "R/ U/ R' U' R' F/ R2 U/ R' U' F'",
    "R/ U/ R' U/ R' F/ R/ F' R/ U2 R'",
    "r/ U/ R' U/ R' F/ R/ F' R/ U2 r'",
    "M' R' U' R/ U' R' U2 R/ U' R/ r'",
    "F/ U/ R/ U' R2 F' R/ U/ R/ U' R'",
    "R' F/ R/ U/ R' F' R/ F/ U' F'",
    "l' U' l/ L' U' L/ U/ l' U/ l/",
    "r/ U/ r' R/ U/ R' U' r/ U' r'",
    "F/ R' F' R2 r' U/ R/ U' R' U' M'",
    "r/ U/ R' U/ R/ U2 r2 U' R/ U' R' U2 r/",
    "r' R/ U/ R/ U/ R' U' M' R' F/ R/ F'",
    "r/ U/ R' U' M2 U/ R/ U' R' U' M'",
    "R/ U2 R' U' R/ U/ R' U' R/ U' R'",
    "R/ U2 R2 U' R2 U' R2 U2 R/",
    "R2 D' R/ U2 R' D/ R/ U2 R/",
    "r/ U/ R' U' r' F/ R/ F'",
    "F' r/ U/ R' U' r' F/ R/",
    "R/ U2 R' U' R/ U' R'",
    "R/ U/ R' U/ R/ U2 R'",
    "r/ U/ R' U' r' R/ U/ R/ U' R'",
    "R/ U/ R' U' R/ U' R' F' U' F/ R/ U/ R'",
    "F/ R' F/ R2 U' R' U' R/ U/ R' F2",
    "R' U' F/ U/ R/ U' R' F' R/",
    "L/ U/ F' U' L' U/ L/ F/ L'",
    "R/ U/ R' U' R' F/ R/ F'",
    "R/ U/ R2 U' R' F/ R/ U/ R/ U' F'",
    "R/ U2 R2 F/ R/ F' R/ U2 R'",
    "L' U' L/ U' L' U/ L/ U/ L/ F' L' F/",
    "F/ R' F' R/ U/ R/ U' R'",
    "R/ U/ R' U/ R/ U' R' U' R' F/ R/ F'",
    "L/ F' L' U' L/ U/ F/ U' L'",
    "R' F/ R/ U/ R' U' F' U/ R/",
    "R/ U/ R' U/ R/ U2 R' F/ R/ U/ R' U' F'",
    "R' U' R/ U' R' U2 R/ F/ R/ U/ R' U' F'",
    "F' U' L' U/ L/ F/",
    "F/ U/ R/ U' R' F'",
    "F/ R/ U/ R' U' F'",
    "R' U' R' F/ R/ F' U/ R/",
    "R' U' R' F/ R/ F' R' F/ R/ F' U/ R/",
    "F/ R/ U/ R' U' R/ U/ R' U' F'",
    "r/ U' r2 U/ r2 U/ r2 U' r/",
    "r' U/ r2 U' r2 U' r2 U/ r'",
    "F/ U/ R/ U' R' U/ R/ U' R' F'",
    "R/ U/ R' U/ R/ U' B/ U' B' R'",
    "l' U2 L/ U/ L' U' L/ U/ L' U/ l/",
    "r/ U2 R' U' R/ U/ R' U' R/ U' r'",
    "R' F/ R/ U/ R/ U' R2 F' R2 U' R' U/ R/ U/ R'",
    "r' U' r/ U' R' U/ R/ U' R' U/ R/ r' U/ r/",
    "R/ U/ R' U' M' U/ R/ U' r'"
};
string pariSnSEA[8] = // Scan and Snap the corners
{
    "S/ D/ S'",
    "S/ D' S'",
    "M/ D/ M'",
    "M/ D' M'",
    "S' D/ S/",
    "S' D' S/",
    "M' D/ M/",
    "M' D' M/",
};
string pariSnSE2A[8] = // Scan and Snap mid layer edges
{
    "R/ E' R' E/",
    "R' E/ R/ E'",
    "F/ E' F' E/",
    "F' E/ F/ E'",
    "L/ E' L' E/",
    "L' E/ L/ E'",
    "B/ E' B' E/",
    "B' E/ B/ E'"
};
string pariSnSCA[8] = // Scan and Snap the edges
{
    "R' D/ R/",
    "R' D' R/",
    "L/ D/ L'",
    "L/ D' L'",
    "L' D/ L/",
    "L' D' L/",
    "R/ D/ R'",
    "R/ D' R'",
};
string pariSnSECA[8] = // Scan and Snap combos
{
    "B/ R' B'",
    "r' D/ r/",
    "l/ D' l'",
    "B' L/ B/",
    "F/ L' F'",
    "l' D/ l/",
    "r/ D' r'",
    "F' R/ F/"
};
string pariSnSCECA[8] = // Scan and Snap full combo
{
    "B/ R2 B' R/",
    "F' R2 F/ R'",
    "R/ F2 R' F/",
    "L' F2 L/ F'",
    "F/ L2 F' L/",
    "B' L2 B/ L'",
    "L/ B2 L' B/",
    "R' B2 R/ B'"
};
string* pariSnSA[5] = 
{
    pariSnSEA,
    pariSnSECA,
    pariSnSCECA,
    pariSnSCA,
    pariSnSE2A
};
string pariOriEA[4] = // algorithms for reorienting a single edge
{
    "R/ E2 R2 E/ R/ E/",
    "F/ E2 F2 E/ F/ E/",
    "L/ E2 L2 E/ L/ E/",
    "B/ E2 B2 E/ B/ E/"
};
string pariOriCA[8] = // algorithms for reorienting a single corner
{
    "R' D' R/ D/ R' D' R/",
    "R' D/ R/ D' R' D/ R/",
    "L/ D' L' D/ L/ D' L'",
    "L/ D/ L' D' L/ D/ L'",
    "L' D' L/ D/ L' D' L/",
    "L' D/ L/ D' L' D/ L/",
    "R/ D' R' D/ R/ D' R'",
    "R/ D/ R' D' R/ D/ R'",
};
CubieCube permCube[21]; // PLL phase to put the pieces in place for the OLL phase
CubieCube orieCube[57];// OLL phase to put the non-yellows in place
CubieCube pariCubeT1E[16]; // T1 puts the white edges in place
CubieCube pariCubeT1C[16]; // T1 puts the white corners in place
// T2 fixes the pieces that are left after T1 using SnS as the first step
CubieCube pariCubeSnS[5][8];
CubieCube pariCubeOriE[4];
CubieCube pariCubeOriC[8];
#endif