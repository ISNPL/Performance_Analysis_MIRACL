#include <iostream>
#include <fstream>
#include "big.h"
#include <time.h>

using namespace std;

#define QBITS 160
#define PBITS 1024 
#define runtime 100
Miracl precision=500;

int main()
{
    //ofstream common("ex.dss");    /* construct file I/O streams */
    Big a,e,p,r;
    miracl *mip=&precision;
    clock_t start, end;
    double max,min,sum,average,result;
    long seed;
    double time[100];

    cout << "Enter 9 digit random number seed  = ";

    cin >> seed;
    irand(seed);

    //64bits random number 2^64~=10^20
    // a=rand(64,2);
    // p=rand(64,2);
    // e=rand(64,2);

    // cout << "a= " << a << endl;
    // cout << "e= " << e << endl;
    // cout << "p= " << p << endl;

    for (int i = 0; i < runtime; i++)
    {
        a=rand(64,2);
        p=rand(512,2);
        e=rand(512,2);
        
        start = clock();
        r=pow(a,e,p);
        end = clock();

        time[i]=(double)(end-start);
    }

    cout << "a^e mod p = " << r << endl;

    max=time[0];
    min=time[0];
    sum=0;
    for (int j = 0; j < runtime; j++)
    {
        if(time[j]>=max) max=time[j];
        if(time[j]<=min) min=time[j];
        sum+=time[j];
        printf("%f\n",time[j]);
    }
    average=sum/runtime;

    printf("max time : %.3f ms \n", (max/CLOCKS_PER_SEC)*1000);
    printf("min time : %.3f ms \n", (min/CLOCKS_PER_SEC)*1000);
    printf("average time : %.3f ms \n", (average/CLOCKS_PER_SEC)*1000);
    printf("\n");

    // common << a << endl;
    // common << e << endl;
    // common << r << endl;
    return 0;

}