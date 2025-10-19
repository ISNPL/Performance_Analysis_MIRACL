#include <iostream>
#include <cstring>
#include <fstream>
#include "big.h"
#include <time.h>
#include "ecn.h"

using namespace std;

#define runtime 100

Miracl precision(50,0);

//curve : brainpoolP160r1 160bit 상의 유한체에서 정의된 elliptic curve

char *ecp=(char *)"E95E4A5F737059DC60DFC7AD95B3D8139515620F";


char *eca=(char *)"340E7BE2A280EB74E2BE61BADA745D97E8F7C300";
char *ecb=(char *)"1E589A8595423412134FAA2DBDEC95C8D8675E58";

/* elliptic curve - point of prime order (x,y) */

char *ecx=(char *)"BED5AF16EA3F6A4F62938C4631EB5AF7BDBCDBC3";
char *ecy=(char *)"1667CB477A1A8EC338F94741669C976316DA6321";

// verifying site : https://www.di-mgt.com.au/sha_testvectors.html

int main()
{

    clock_t start, end;
    double max,min,sum,average,result;
    time_t seed;
    
    Big a,b,p,q,d,x,y,x1,y1,x2,y2,c;
    ECn g,g2,ea,eb;
    miracl *mip=&precision;

    time(&seed);
    irand((long)seed);

    // 커브 생성
    mip->IOBASE=16;
    // a=-3;
    // b=0;
    // p=2129;
    a=eca;
    b=ecb;
    p=ecp;
    ecurve(a,b,p,MR_BEST);  // means use PROJECTIVE if possible, else AFFINE coordinates
    // x1=491;
    // y1=34;
    // x2=548;
    // y2=42;
    x=ecx;
    y=ecy;
    mip->IOBASE=10;
    g=ECn(x,y);
    // g=ECn(x1,y1);
    // g2=ECn(x,y);
    ea=eb=g;

    //d=5;
    d=rand(160,2);
    cout<<d<<endl;
    // ea*=d;
    // cout<<ea<<endl;  

    cout<<"point*"<<endl;
    //cout<< d << " * " << g .< " = ";
    result=0;
    for (int x = 0; x < runtime; x++){
        start = clock();
        ea*=d;
        end = clock();
        result+=(double)(end-start);
    }
    cout<<ea<<endl;  
    result = ((result/CLOCKS_PER_SEC)*1000)/runtime;
    printf("average time : %0.3f ms \n", result);
    printf("\n");

    ////////////////////////////////////////////////////

    cout<<"point+"<<endl;
    //cout<< d << " + " << g << " = ";
    
    result=0;
    for (int x = 0; x < runtime; x++){
        start = clock();
        ea+=eb;
        end = clock();
        result+=(double)(end-start);
    }
    cout<<ea<<endl;  
    result = ((result/CLOCKS_PER_SEC)*1000)/runtime;
    printf("average time : %0.3f ms \n", result);
    printf("\n");

    return 0;
}