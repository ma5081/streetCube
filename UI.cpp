#include "streetCube.h"
//#include <opencv2/opencv.hpp> WIP
// using namespace cv;
#include <stdlib.h>
#include <iostream>
using namespace std;

struct UFace // stores the piece in cube-sized blocks
{
    int f[9];
};

// this is the main code for user interaction
int main(int argc, char* argv[])
{
    setup();
    int w;
    int h;
    // get width/height
    cout<<"enter width (px - 240 max): ";
    cin>>w;
    cout<<"enter height (px - 240 max): ";
    cin>>h;
    int wMargin = (w%3)*2; //if non-divisible by 3, add margin
    w += wMargin;
    int hMargin = (h%3)*2; // add margin
    h += hMargin;
    if(h>240||w>240) {cout<<"width or height too large"<<endl;return 1;}
    UFace pixelart[60][60];
    for(int i=0; i<hMargin/2; i++) // add vertical margins
    {
        for(int j=0; j<w; j++)
        {
            pixelart[0][j/3].f[(i%3)*3+j%3]=0;
            pixelart[h/3][j/3].f[(i%3)*3+j%3]=0;
        }
    }
    for(int i=0; i<h; i++) // add horizontal margins
    {
        for(int j=0; j<wMargin; j++)
        {
            pixelart[i/3][0].f[(i%3)*3+j%3]=0;
            pixelart[i/3][w/3].f[(i%3)*3+j%3]=0;
        }
    }
    cout<<w<<"x"<<h<<endl;
    cout<<"insert the colors pixel by pixel using Y,R,B,W,O,G"<<endl;
    for(int i=hMargin/2; i<h-hMargin/2; i++) // fill out the rest of the cubes
    {
        for(int j=wMargin/2; j<w-wMargin/2; j++)
        {
            char in;
            cin>>in;
            for(int k=0; k<6; k++)
            {
                if(in==etoc[k]) 
                {
                    pixelart[i/3][j/3].f[(i%3)*3+j%3]=k; break;
                }
                if(k==5) j--;
            }
        }
    }
    CubieCube sols[60][60];
    int pw = w/3; // w in cubes
    int ph = h/3; // h in cubes
    for(int i=0; i<ph; i++) // gets the scrambles for all the cubes
    {
        for(int j=0; j<pw; j++)
        {
            int co[4];
            int eo[4];
            int* helpArr[9] = {&co[ULB], &eo[UB], &co[UBR], &eo[UL], NULL, &eo[UR], &co[UFL], &eo[UF], &co[URF]};
            int c = pixelart[i][j].f[4]; // finds color of U
            for(int k=0; k<9; k++)
            {
                if(k==4) continue;
                *helpArr[k] = ctor[c][pixelart[i][j].f[k]]; // compares color of U to the selected color and adds passed parameters
            }
            string orientation = "(U: "; // mentions how the cube should be held
            orientation+=etoc[c];
            orientation+=", F: ";
            orientation+=etoc[rtoc[c][2]];
            orientation+=")\n";
            sols[i][j] = res(eo,co); // get scramble
            sols[i][j].scramble = orientation+sols[i][j].scramble;
        }
    }
    char in;
    int curr[2] = {0,ph-1}; // start at bottom-most left-most cube move to the right and up
    do
    {
        system("clear");
        // print cubes
        for(int i=0;i<h;i++)
        {
            for(int j=0; j<w; j++)
            {
                cout<<etoc[pixelart[i/3][j/3].f[(i%3)*3+j%3]]<<" ";
            }
            cout<<endl;
        }
        // print scramble
        cout<<"cube ("<<curr[0]<<", "<<curr[1]<<") moves: "<<sols[curr[1]][curr[0]].scramble<<"\ncube should look like this :)\n";
        // print the cube being resolved
        for(int i=0;i<3;i++)
        {
            for(int j=0; j<3; j++)
            {
                cout<<etoc[pixelart[curr[1]][curr[0]].f[(i%3)*3+j%3]]<<" ";
            }
            cout<<endl;
        }
        // take command (wasd arrows or n for next and p for prev)
        cin>>in;
        switch (in)
        {
        case 'n':
            if(curr[0]+1==pw) curr[1]=(curr[1]-1+ph)%ph;
        case 'd':
            curr[0] = (curr[0]+1)%pw;
            break;
        case 'p':
            if(curr[0]-1<0) curr[1]=(curr[1]+1)%ph;
        case 'a':
            curr[0] = (curr[0]-1+pw)%pw;
            break;
        case 'w':
            curr[1]=(curr[1]-1+ph)%ph;
            break;
        case 's':
            curr[1]=(curr[1]+1)%ph;
            break;
        default:
            break;
        }
    } while(in!='q'); // q for quit
    
    return 0;
}

/////////////////  WIP  //////////////////////

// int main() {

//     string path = "streetCat.png";
//     Mat img = imread(path);
//     imshow("Image", img);
//     waitKey(0);
//     return 0;
// }