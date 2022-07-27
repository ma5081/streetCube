#ifndef CUBIE
#define CUBIE
#include "move.h"
#include "functions.h"
CubieCube::CubieCube()
{
    for(int i=0; i<8; i++) cp[i]=i;
    co = 0;
    for(int i=0; i<12; i++) ep[i]=i;
    eo = 0;
    scramble = "";
}
CubieCube::CubieCube(int cp[], int co, int ep[], int eo)
{
    for(int i=0; i<8; i++) this->cp[i]=cp[i];
    this->co = co;
    for(int i=0; i<12; i++) this->ep[i]=ep[i];
    this->eo = eo;
    scramble = "";
}
CubieCube::CubieCube(string algs)
{
    CubieCube cube = algo(algs);
    for(int i=0; i<8; i++) this->cp[i]=cube.cp[i];
    this->co = cube.co;
    for(int i=0; i<12; i++) this->ep[i]=cube.ep[i];
    this->eo = cube.eo;
    scramble = "";
}
CubieCube::CubieCube(CubieCube* that)
{
    for(int i=0; i<8; i++) this->cp[i]=that->cp[i];
    this->co = that->co;
    for(int i=0; i<12; i++) this->ep[i]=that->ep[i];
    this->eo = that->eo;
    scramble = "";
}

void CubieCube::print()
{
    // printf("%d.%d.(",co,eo);
    for(int i=7; i>=0; i--)
    {
        printf("%d",cco(co,i));
    }
    printf(".");
    for(int i=11; i>=0; i--)
    {
        printf("%d",ceo(eo,i));
    }
    printf(".(");
    for(int i=0; i<8; i++)
    {
        printf("%d ",cp[i]);
    }
    printf(").(");
    for(int i=0; i<12; i++)
    {
        printf("%d ",ep[i]);
    }
    printf(")\n");
}
FaceCube CubieCube::translate()
{
    FaceCube fc = FaceCube();
    for(int i=0; i<8; i++)
    {
        int ori = uco(this->co,i);
        for(int j=0; j<3; j++)
            fc.f[cornerFacelet[i][(j+ori)%3]]=cornerColor[cp[i]][j];
    }
    for(int i=0; i<12; i++)
    {
        int ori = ceo(this->eo,i);
        for(int j=0; j<2; j++)
            fc.f[edgeFacelet[i][(j+ori)%2]]=edgeColor[ep[i]][j];
    }
    return fc;
}
void CubieCube::rotRes(int a, int m)
{
    int t[6];
    for(int i=0; i<6; i++)
    {
        t[i] = r[rot[a*3+m][i]];
    }
    for(int i=0; i<6; i++) r[i]=t[i];
}
void CubieCube::edgeMult(CubieCube* that)
{
    int e_per[12];
    int e_ori = 0;
    for(int i=0; i<12; i++)
    {
        e_per[i] = this->ep[that->ep[i]];
        e_ori += (ceo(that->eo,i) ^ ceo(this->eo,(that->ep[i])))<<i;
    }
    for(int i=0; i<12; i++)
        this->ep[i]=e_per[i];
    
    this->eo=e_ori;
}
void CubieCube::cornMult(CubieCube* that)
{
    int c_per[8];
    int c_ori = 0;
    int ori = 0;
    for(int i=0; i<8; i++)
    {
        c_per[i] = this->cp[that->cp[i]];

        int ori_a = uco(this->co,that->cp[i]);
        int ori_b = uco(that->co,i);
        if(ori_a < 3 && ori_b < 3) // two regular cubes
        {
            ori = ori_a + ori_b;
            if(ori >= 3)
                ori -= 3;
        }
        else if(ori_a < 3 <= ori_b) // cube b is in a mirrored state
        {
            ori = ori_a + ori_b;
            if(ori >= 6)
                ori -= 3; // the composition also is in a mirrored state
        }
        else if(ori_a >= 3 > ori_b) // cube a is in a mirrored state
        {    
            ori = ori_a - ori_b;
            if(ori < 3)
                ori += 3; // the composition is a mirrored cube
        }
        else if(ori_a >= 3 && ori_b >= 3) // if both cubes are in mirrored states
        {    
            ori = ori_a - ori_b;
            if(ori < 0)
                ori += 3; // the composition is a regular cube
        }

        c_ori += ori*pow(3,i);
    }
    for(int i=0; i<8; i++)
        this->cp[i]=c_per[i];
    this->co=c_ori;
}

void CubieCube::operator=(CubieCube* that)
{
    for(int i=0; i<8; i++) this->cp[i]=that->cp[i];
    this->co = that->co;
    for(int i=0; i<12; i++) this->ep[i]=that->ep[i];
    this->eo = that->eo;
    for(int i=0; i<3; i++) this->r[i]=that->r[i];
    this->scramble = that->scramble;
}
void CubieCube::operator=(CubieCube c)
{
    for(int i=0; i<8; i++) this->cp[i]=c.cp[i];
    this->co = c.co;
    for(int i=0; i<12; i++) this->ep[i]=c.ep[i];
    this->eo = c.eo;
    for(int i=0; i<3; i++) this->r[i]=c.r[i];
    this->scramble = c.scramble;
}
bool CubieCube::operator==(CubieCube* that)
{
    if(this->co!=that->co || this->eo!=that->eo) return false;
    for(int i=0; i<8; i++)
        if(this->cp[i]!=that->cp[i]) return false;
    for(int i=0; i<12; i++)
        if(this->ep[i]!=that->ep[i]) return false;
    return true;
}
CubieCube* CubieCube::operator*(CubieCube* that)
{
    this->cornMult(that);
    this->edgeMult(that);
    return this;
}
CubieCube CubieCube::operator*(CubieCube that)
{
    this->cornMult(&that);
    this->edgeMult(&that);
    CubieCube ret = CubieCube(this);
    return ret;
}
CubieCube CubieCube::operator*(int m)
{
    CubieCube prepic= CubieCube(this->cp,this->co,this->ep,this->eo);
    for(int i=1; i<m; i++)
        prepic*this;
    return prepic;
}
#endif