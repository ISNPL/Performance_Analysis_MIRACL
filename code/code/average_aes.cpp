#include <iostream>
#include <miracl.h>
#include "big.h" /* include MIRACL system */
#include <time.h>

using namespace std;
#define runtime 100
#define NB 4

int main()
{
    clock_t start, end;
    double max,min,sum,average,result;
    //nk -> aes-x (nk*8=x bits)
    int i, j, nk = 16;
    aes a;
    MR_BYTE y, x, m;
    double entime[100];
    double detime[100];
    char key[32];
    char block[16];
    //128bit plaintext
    char block2[16] = "abcadadddadadad";
    // Initialisation Vector
    char iv[16];

    //key size 32*8(aes256) 24*8(aes192) 16*8(aes128)
    for (i = 0; i < 32; i++)
        key[i] = 1;
    for (i = 0; i < 16; i++)
        iv[i] = i;
    // for (i = 0; i < 16; i++)
    //     block[i] = i;

    printf("Input message : ");
    for (int x = 0; x < 16; x++)
    {
        printf("%c", block2[x]);
    }
    printf("\n");

    //nk=key size (16byte=128bit)

    printf("Key = ");
    for (int x = 0; x < nk; x++)
    {
        printf("%d", key[x]);
    }

    printf("\nKey Size= %d bits\n", nk * 8);

    // nk aes bits
    if (!aes_init(&a, MR_OFB16, nk, key, iv))
    {
        printf("Failed to Initialize\n");
        return 0;
    }

    // printf("Plain=   ");
    // for (i=0;i<4*NB;i++) printf("%02x",block2[i]);
    // printf("\n");

    
    for (int i = 0; i < runtime; i++)
    {
        start =clock();
        aes_encrypt(&a, block2);
        end=clock();
        entime[i]=(double)(end - start);
    }

    max=entime[0];
    min=entime[0];
    sum=0;
    for (int j = 0; j < runtime; j++)
    {
        if(entime[j]>=max) max=entime[j];
        if(entime[j]<=min) min=entime[j];
        sum+=entime[j];
        //printf("%.70f\n",(entime[j]/CLOCKS_PER_SEC)*1000);
    }
    average=sum/runtime;

    // printf("Encrypt= ");
    // for (i=0;i<4*NB;i++) printf("%02x",(unsigned char)block2[i]);
    // printf("\n");

    printf("en max time : %.3f ms \n", (max/CLOCKS_PER_SEC)*1000);
    printf("en min time : %.3f ms \n", (min/CLOCKS_PER_SEC)*1000);
    printf("en average time : %.3f ms \n", (average/CLOCKS_PER_SEC)*1000);
    printf("\n");

    aes_reset(&a, MR_OFB16, iv);

    
    for (int i = 0; i < runtime; i++)
    {
        start =clock();
        aes_decrypt(&a, block2);
        end=clock();
        detime[i]=(double)(end - start);
    }

    max=detime[0];
    min=detime[0];
    sum=0;
    for (int j = 0; j < runtime; j++)
    {
        if(detime[j]>=max) max=detime[j]; 
        if(detime[j]<=min) min=detime[j];
        sum+=detime[j];
        //printf("%.70f\n",(detime[j]/CLOCKS_PER_SEC)*1000);
    }
    average=sum/runtime;

    // printf("Decrypt= ");
    // for (i=0;i<4*NB;i++) printf("%02x",block2[i]);
    // printf("\n");

    printf("de max time : %0.3f ms \n", (max/CLOCKS_PER_SEC)*1000);
    printf("de min time : %0.3f ms \n", (min/CLOCKS_PER_SEC)*1000);
    printf("de average time : %0.3f ms \n", (average/CLOCKS_PER_SEC)*1000);
    printf("\n");

    aes_end(&a);

    return 0;
}
