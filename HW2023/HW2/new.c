#include <stdio.h> 
#include <stdlib.h>
#include <math.h>


void main(void){
    double result;
    result = 1323;
    int resultFinder = (int)result;
    int resultFinder2 = (int)result;

    int resultCopy = (int)result;
    

    int m=4;
    int n=3;
    int resultCopy2 = (int)result;
    int digit;
   int digitCount = 0;
   
    while(resultFinder){
        
        resultFinder /= 10;
        digitCount++;
    }
    printf("digits = %d\n\n",digitCount);
    int rk2 = digitCount -1;
    int rk = digitCount;
    int rk3 = digitCount;
    int* digits = (int*)calloc(digitCount,sizeof(int)*digitCount);
    for(rk2;0<=rk2;rk2--){
        digits[rk2] = resultFinder2%10;
        resultFinder2 /= 10;
    }
    int j = 0;
    while(j < rk){
        printf("%d\n",digits[j]);
        j++;
    }
    rk=0;
    for(int j=0;j<m-n;j++){
        printf("%d",digits[j]);
        rk++;

    }
    //printf("/n rk = %d, j = %d",rk,j);
    //BURASI BOZUK TEKRAR YAPILACAK
    printf(".");
    for(int a=0;a<rk3;a++){
        printf("%d",digits[rk]);
        rk++;
    }
    
    
   
    


    //exponential bulma kismi e ussu kac olacak onu burasi buluyor

    for(int j=0;j<n;j++){
        result /= 10;

    }
   
    double result2 = result;
    int expoCounter = 0;
    while(resultCopy2 != (int)result){
        result *= 10;
        expoCounter++;
    }
    printf("e%d",expoCounter);
    
}