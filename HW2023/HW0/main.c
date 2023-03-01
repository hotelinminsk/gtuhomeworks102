#include <stdio.h>
#include "util.h"
#include "util.h"



int main() {

    /* A fractional number: 13/7 */
    int num1 = 13, den1 = 7;
    /* A fractional number: 13/7 */
    int num2 = 30, den2 = 11;
    /* An unitilized fractional number */
    int num3, den3;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    //fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    //fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    //fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    //fraction_print(num3, den3);
    printf("\n");

    /*
     TODO: Complete this code to read two fractional numbers and print their 
             multiplication and division results...
    */

    int choice=1;
    while(choice!=0){


    do
    {   
        printf("PLEASE DONT GIVE NEGATIVE OR NULL NUMBERS AND CHARACTERS");
        printf("\n-------------------------------");
        printf("\nPlease give numerator1: ");
        scanf("%d",&num1);
        printf("\nPlease give denominator1: ");
        scanf("%d",&den1);
        printf("\nPlease give numerator2: ");
        scanf("%d",&num2);
        printf("\nPlease give denominator2: ");
        scanf("%d",&den2);
    } while (den1 < 0 || den1 == 0 || den2 < 0 || den2 == 0);

    printf("For addition insert(1),substraction(2),multipication(3),division(4),exit(0)\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        //Addition of fractional number;
        fraction_add(num1,den1,num2,den2,&num3,&den3);
        break;
    case 2:
        //Substraction of fractional numbers;
        fraction_sub(num1,den1,num2,den2,&num3,&den3);
        break;
    case 3:
        //multipication of fractional numbers;
        fraction_mul(num1,den1,num2,den2,&num3,&den3);
        break;
    case 4:
        //division of fractional numbers
        fraction_div(num1,den1,num2,den2,&num3,&den3);
        break;
    case 0:
        //if 0 break
        break;
    default:
        //if any other char/num break
        break;
    }
    }
    
    return(0);
}
