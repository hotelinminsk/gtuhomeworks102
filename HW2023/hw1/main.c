#include <stdio.h>
#include <stdlib.h>
#define MAX 10 //defined max and min values for part4 function
#define MIN 1
int part4(){
    int userInput;    
    printf("\nPlease give an integer which is between 1-10: ");
    scanf("%d",&userInput);//Taking a integer from user
    if(userInput <= 5){//checking if its less than or equal to 5
        printf("\nInteger u give is less than or equal to 5..\n");
    }
    else if (userInput > MAX || userInput < MIN)//checking the given integer is between bounds
    {
        printf("\nInteger u entered is not between 1-10, terminating..;");

    }
    else{
        printf("\nThe integer you entered is greater than 5..");
    }
    
}

int part3_multiplication(){
    int firstNum,secondNum,result; // declared the integer variables

    printf("\nPlease give two integers to find multiplication..\n");
    printf("Enter the first integer: ");
    scanf("%d",&firstNum);
    printf("\nEnter the second integer: ");
    scanf("%d",&secondNum);
    if(secondNum > firstNum){//we will get the second numbers digits by modulo operator because of this i will take firstNum is always bigger
        int temp = secondNum;
        secondNum = firstNum;
        firstNum = temp;
    }
    int *digits = (int*)calloc(3,sizeof(int)*3);// we allocated a memmory for a array that at most 3 digits long 
    int digCount=0;
    int temp = secondNum;
    while(temp){
        digits[digCount] = temp % 10;
        temp = temp/10;
        digCount++;
    }//this will give the digits on reverse order least significant digit will be first on the array 
    //
    int firstMult,secondMult,thirdMult;
    firstMult = firstNum * digits[0];
    secondMult = firstNum * digits[1];
    thirdMult = firstNum * digits[2];
    result = firstNum * secondNum;
    
    
    printf("%9d\n%9d\n*\n---------\n%9d\n%8d\n%7d\n+\n---------\n%9d\n",firstNum,secondNum,firstMult,secondMult,thirdMult,result);

}

int part2_sum(){
    int firstNum,secondNum;//we have our integer variables to hold the values 
    printf("\nPlease give two integers to find the sum..\n");
    printf("Enter the first integer: ");
    scanf("%d",&firstNum);//we take first number from user
    printf("\nEnter the second integer: ");
    scanf("%d",&secondNum);//the second one
    int result = firstNum + secondNum;//add those numbers
    printf("Result : \n\n");
    printf("%6d\n%6d\n+\n------\n%6d\n",firstNum,secondNum,result);//show them to user with alignments

    return 0;
}
int part1_gcd(int firstNum,int secondNum,int basePtr){
   
    if(secondNum > firstNum){//we check if the second number is bigger than first one 
        int temp = firstNum;//if that is the case we should change the values
        firstNum = secondNum;
        secondNum = temp;
        basePtr = temp;
        part1_gcd(firstNum,secondNum,basePtr);//base should always stay the same cause we want the number to divide both of the numbers with no remainders
    }
    if(firstNum % secondNum == 0 && basePtr % secondNum == 0){ // 
        //gcd is secondNumber
        return secondNum;
    }
    else{
        part1_gcd(firstNum,secondNum-1,basePtr);//secondnum is going to 
    }

}

void main(void){
    // PART1
    int returnGcd;
    int firstNum;// we malloced two integer pointers to hold values
    int secondNum;
    printf("\nPlease give 2 integers to take gcd");// ask user for integer values
    do
    {
        printf("\nFirst integer: ");
        scanf("%d",&firstNum);
        if(firstNum<0){ // if first integer is given 
        firstNum = firstNum * -1;
        }
        else if(firstNum == 0){
            printf("Please dont give zero..");
        }
    } while (firstNum == 0);//we dont want division to zero error
    
    do
    {
        printf("\nPlease give the second number: ");
        scanf("%d",&secondNum);
        if(secondNum < 0){
            secondNum = secondNum * -1;
        }
        else if(secondNum == 0){
            printf("Please dont give zero..");
        }
    } while (secondNum == 0);
    int base = secondNum;
    
         
    returnGcd = part1_gcd(firstNum,secondNum,base);
    if(returnGcd != 1){//check if return value is 1 or not if its 1 return values are co-prime
        printf("\nGCD is = %d\n",returnGcd);

    }
    else{
        printf("\nNumbers are co-prime...");
    }
    //PART2
    part2_sum();
    //PART3
    part3_multiplication();
    //PART4
    part4();
   
}