#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    if(numerator==0 && denominator != 0){
        printf("0\n");
    }
    else if(numerator == 0 && denominator == 0){
        printf("\nIndefinite number.\n");
    }
    else if(denominator == 0){
        printf("\nUndefined\n");
    }
    else{
    printf("%d//%d\n", numerator, denominator);

    }
}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = (n1*d2) - ( n2*d1);
    *d3 = d1*d2;
    fraction_simplify(n3,d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1 * n2;
    *d3 = d1 * d2;
    
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2;
    *d3 = d1*n2;
    fraction_simplify(n3, d3);
} /* end fraction_div */

/* Simplify the given fraction such that they are divided by their GCD */
void fraction_simplify(int * n, int * d) {
    int is_negative = 0; // a flag for checking the given number is negative or not
    if(*n < 0){
        is_negative = 1;
    }
    int gcN;
    int base = *d; // d`s base value;
    if(is_negative){ //if we have a negative value we should send the positive version 
        *n = *n * -1;
        gcN = gcd(*n,*d,&base);
        //gcN = gcN * -1; //after that we make it negative again
        *n = *n * -1;
    }
    else{ //if not negative just call the function
    
        gcN = gcd(*n,*d,&base);//we send n`s value d`s value and base pointer.

    }
    if(gcN == 1){
        //numbers are co-prime
        //if numbers are coprime we send them to printer as they are
        printf("\nAnswer is: ");
        
        fraction_print(*n,*d);
    }
    else{
        //if they are not co prime we should divide them to gcd and send them to printer
        *n= *n / gcN;
        *d = *d / gcN;
        printf("\nAnswer is: ");
        fraction_print(*n,*d);
    }
} /* end fraction_div */



//GCD FUNCTION FOR SIMPLIFYING
int gcd(int n,int d,int *base){
    if(d>n){
        int temp;
        temp = n;
        n = d;
        d = temp;
    }
    if(d==1){
        return 1; //Numbers are co-prime;
    }
    else{
        if(*base % d == 0 && n % d == 0 ){
            return d; // d is the common divisor;

        }
        else{
            return gcd(n,d-1,base);
        }
    }

}