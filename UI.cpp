#include "streetCube.h"
#include <fstream>
#include <iostream>
#include <winsock2.h>
    using namespace std;
int main(int argc, char* argv[])
{
    //if(argc<1) {printf("no photo name input\n"); return 1;}
    ifstream in(argv[1]);
    unsigned int w, h;

    in.seekg(16);
    in.read((char *)&w, 4);
    in.read((char *)&h, 4);

    w = ntohl(w);
    h = ntohl(h);

    cout<<w<<"x"<<h<<endl;
}