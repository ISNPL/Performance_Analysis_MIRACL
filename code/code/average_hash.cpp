#include <iostream>
#include <cstring>
#include <fstream>
#include "big.h"
#include <time.h>

#define runtime 100

using namespace std;

void InitializeRandomSeed()
{
	srand((unsigned int)time(0));
}

char GetRandomCharacter()
{
	return 'a' + (rand() % 26);
}

int main()
{
    char hash[10000];
    double time[100];
    int i; 
    sha256 sh256;
    clock_t start, end;
    double max,min,sum,average;
    
    cout<<"Input byte : ";
    int length;
    cin>>length;

    InitializeRandomSeed();

    printf("\n");

    for (int x = 0; x < runtime; x++)
    {
        char *test = new char(length);

        for (int z = 0; z < length; z++)
        {
        test[z]=GetRandomCharacter();
        //printf("%c",test[z]);
        }

        start = clock();
        shs256_init(&sh256);
        for (i=0;test[i]!=0;i++) shs256_process(&sh256,test[i]);
        shs256_hash(&sh256,hash); 
        end = clock();
    
        time[x]=(double)(end-start);
        delete[] test;
        // printf("SHA-256 result :\n");
        // for (i=0;i<32;i++) printf("%02x",(unsigned char)hash[i]);
        // printf("\n"); 
    }

    max=time[0];
    min=time[0];
    sum=0;
    for (int j = 0; j < runtime; j++)
    {
        if(time[j]>=max) max=time[j];
        if(time[j]<=min) min=time[j];
        sum+=time[j];
        //printf("%f\n",time[j]);
    }
    average=sum/runtime;
    
    printf("max time : %.3f ms \n", (max/CLOCKS_PER_SEC)*1000);
    printf("min time : %.3f ms \n", (min/CLOCKS_PER_SEC)*1000);
    printf("average time : %.3f ms \n", (average/CLOCKS_PER_SEC)*1000);
    printf("\n");

    return 0;
}