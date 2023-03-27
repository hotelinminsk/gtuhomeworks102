#include <stdio.h>
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
void scientific_writer(double baseNum,int allDigits,int decimalDigits,int is_negative){
printf("\n*******************\n");
printf("The result is:");


if(is_negative==1){
    printf("-");
    baseNum = baseNum * -1;  //FIRST WE CHECK IF THE GIVEN RESULT IS NEGATIVE OR NOT 
}
else if(is_negative==5){
    printf("1/"); //IF FUNCTION TAKES IS NEGATIVE ARGUMENT EQUAL TO ZERO THIS MEANS ITS A NEGATIVE POWER
}

double baseCopy2 = baseNum; // A COPY OF BASENUM FOR MATHEMATICAL 

int baseNumCopy1 = (int)baseNum; // a copy of basenum in integer format for finding the integer parts digit count
int intDigit=0; // integer digit counter
int exponentCounter = 0; // our exponent counter
int isLower = 0; // a boolean for checking the exponents sign (if our number is lower than base number e+%d if bigger than basenum e-%d )
while(baseNumCopy1){
    baseNumCopy1 /= 10;   //from integer copy of our number we find out the integer digit count with basically dividing the number by 10 
    intDigit++;
}
if(allDigits-decimalDigits>intDigit){ //if allDigits-decimalDiggits variables which given by user is bigger than the orginal numbers integer digit count
    for(int i=0;i<(allDigits-decimalDigits)-intDigit;i++){
        baseCopy2 *= 10;       //simply multiply the copy number by 10 as user wanted
        exponentCounter++;    //while multiplying the copy number by 10 also increment the exponentcounter
    }
    isLower = 1; //if allDigits-decimalDigits is bigger than orginal numbers integer part our exponent is should be -

}
else{ //if alldigits-decimalDigits variables which given by user is less than the orginal numbers integer digit count 
    for(int i=0;i<intDigit-(allDigits-decimalDigits);i++){
        baseCopy2 /= 10;  //divide the copy number by 10 
        exponentCounter++; //while dividingt by 10 also increment the exponentCounter
    }
    isLower = 0;//if int digit is bigger than llDigits-decimalDigits then  exponent is should be +
}

printf("%0*.*lf",allDigits,decimalDigits,baseCopy2); 
if(isLower){
    printf("e-%d\n",exponentCounter);
}
else{
    printf("e+%d\n",exponentCounter);

}
}

void  part1_leapyear(){ //LEAP YEAR FINDING FUNCTION
    int year;
    printf("**********************\n");
    printf("Please give a year: ");
    scanf("%d",&year); // TAKING INTEGER YEAR INPUT
    if((year % 4 == 0 && year % 100 != 0)|| year % 400 == 0){ // If the year value is divisible by 4, not divisible by 100, or divisible by 400
        printf("%d is a leap year!\n",year); //we say that given year is a leap year and print the correct line
    }
    else{
        printf("%d is not a leap year!\n",year); //if not the given year is not a leap year
    }
    printf("**********************\n");

    
       
}




void part2_scientific_calculator(){
    
    char operator;
    char type_of_calc;
    int m,n; // m is number of total digits of result, n is number of decimals after decimal point(warn user if n>m)
    int errorFlag=0;//we keep a flag for returning explained error messages
    
   
    //(+, -,  *,  /,!,^,%) operators
    //types = I , S
    
    do //checking if the user gives only S and I characters, if user gives any other char the loop will ask again
    {
        if(errorFlag){
            printf("Please give S or I characters!..\n");
        }
        else{
            printf("\nWhich output style you want to see?(S=scientific,I=normal): ");
        }
       
        
        scanf("%c",&type_of_calc);
        
        
        if(type_of_calc != 'I' && type_of_calc != 'S'){
            errorFlag = 1;
        }
        else{
            errorFlag = 0;
        }
    } while (errorFlag);
    errorFlag = 0;
    int r= getchar(); // for clearing the stream
    if(type_of_calc=='S' || type_of_calc=='s'){//if given type_of_calc value is equal to S or s this big if statement will begin 
        do //If a different value than expected is entered, this loop will continue until a correct input is received.
        {
            if(errorFlag){
                printf("\nError! N value can`t be bigger than m and both of the values can`t be zeros, please give m & n values again..");

            }
            printf("\nPlease enter m(total digits of result) and n(number of decimals after decimal point) values: ");
            scanf("%d %d",&m,&n);
                  
            if(n>m || m == 0 ||m>9||n>9){ //if given n value is bigger than m or m is equal to zero or  n and m  are bigger than 9 this loop will ask again for valid inputs
                errorFlag = 1;
            }
            else{
                errorFlag = 0;
            }
        }
        while (errorFlag);
        
        
        double first_operand,second_operand;
        double result;
        int is_negative = 0;
        r = getchar(); // for clearing the stream
        printf("\nPlease give operator(+,*,/,!,^,-,%)");
        scanf("%c",&operator);
        switch (operator)
        {
        case '+'://if given operator is equal to + take two operands from user add them and send the result data to scientific_writer function
            printf("\nPlease give two operands: ");
            scanf("%lf %lf",&first_operand,&second_operand);
            result = first_operand + second_operand;
            if(result<0){
                is_negative = 1;
                
            }
            else{
                is_negative = 0;

            }
            scientific_writer(result,m,n,is_negative);

            

            break;
        case '-'://if given operator is equal to - take two operands from user extract  them and send the result data to scientific_writer function
            
            printf("\nPlease give two operands: ");
            scanf("%lf %lf",&first_operand,&second_operand);
            result = first_operand - second_operand;
            if(result<0){
                is_negative = 1;
            }                               //checking if the result value is negative or not
            else{
                is_negative = 0;
            }
            scientific_writer(result,m,n,is_negative);         
            break;
       
        case '*'://if given operator is equal to * take two operands from user mutiply them and send the result data to scientific_writer function
            printf("\nPlease give two operands: ");
            scanf("%lf %lf",&first_operand,&second_operand);
            result = first_operand * second_operand;
            if(result<0){
                is_negative = 1;
            }                               //checking if the result value is negative or not
            else{
                is_negative = 0;
            }
            scientific_writer(result,m,n,is_negative);  
            break;
        
        case '/':
            printf("\n*****************\n");
            do// there is a do-while loop for avoid to divide by zero error 
            {
                if(errorFlag){
                    printf("Dividing by zero error!..\n");
                }
                printf("\nPlease give two operands: ");
                scanf("%lf %lf",&first_operand,&second_operand);
                if(second_operand==0){
                    errorFlag = 1;
                }
            } while (second_operand == 0);
            errorFlag = 0;
            printf("\n*****************\n");
            result = first_operand / second_operand; // divided the two given numbers and save them in the result variable.
            
            if(result<0){
                is_negative = 1;
            }                           //checking if the result value is negative or not
            else{
                is_negative = 0;
            }
            
            scientific_writer(result,m,n,is_negative);  
            break;
        
        
        case '!'://if given operator is equal to ! take only one operand from user, calculate the result then  send the result data to scientific_writer function
            do{
                if(errorFlag){
                    printf("\nCant take a negative numbers factorial!...");
                }
                printf("\nPlease give only one operand: ");
                scanf("%lf",&first_operand);
                if(first_operand<0){
                    errorFlag = 1; //if given operand input is less than zero we ask again because we cant take negative numbers factorial
                }
            }while (errorFlag);
            
            
            if(first_operand==0){
                printf("\n1");
            }                              //checking if given operand is 0 or 1 if thats the case result is simply 1 
            else if(first_operand==1){
                printf("\n1");
            }
            else{
                result = 1;
            for(int j=1;j<=first_operand;j++){
                result = result * j;
                                             }
                scientific_writer(result,m,n,is_negative);
            }
            
            break;
        
        case '^'://if given operator is ^, take 2 operands from user like  first one is the  base and second operand is power calculate and send the result data to scientific printer function
            printf("\n*****************\n");
            printf("Give base number: ");
            scanf("%lf",&first_operand);
            printf("\nGive the power: ");
            scanf("%lf",&second_operand);
            printf("\n*****************\n");
            int is_negativePow = 0; // a boolean variable for checking if the given power value is negative or not
            if(second_operand==0){ // if the given second operand(power value) is equal the zero result is simply 1
                result = 1;
            }
            else if(first_operand == 1){// if the given first operand(base value) is equal the 1 result is simply 1
                result = 1;
            }
            else if(second_operand < 0 ){//if second operand is less than zero
                int is_negativePow= 5; //the is_negativePow boolean is equal to five
                second_operand = -1 * second_operand; // changing the second_operand value's sign to positive
                result = pow(first_operand,second_operand); // then take the power and store it in the result variable

            }
            else if(first_operand<0){ // if first operand(basenumber) is less then zero
                if((int)second_operand % 2 == 0){//check if the second_operand(power)'s integer value is multiple of 2 or not
                    first_operand = -1 * first_operand; // if the second_operator is multiple of 2 change the first_operand's value to positive and make the calculations
                    result = pow(first_operand,second_operand);
                }
                else//if the second_operand(power)'s integer value is not multiple of 2
                {
                    first_operand = -1 * first_operand;//to avoid any errors make first_operand positive again
                    result = pow(first_operand,second_operand);//make the calculations and store the data in result variable
                
                    result = result * -1; // then change the sign of result value to negative again
                

                }
            }
            else{ // in any other case simply use math.h librarys pow function and store the value in result variable
                result = pow(first_operand,second_operand);
            }
            
            
            scientific_writer(result,m,n,is_negativePow);//send the data to scientific_writer function
            printf("\n*****************\n");
            break;

            break;
        case '%'://if the given operator is % use the math.h librarys fmod function and send the data to scientific_writer function

            printf("\n*****************\n");
            do
            {
                if(errorFlag){
                    printf("Dont give negative numbers..\n");
                }
                printf("\nPlease give two operands: ");
                scanf("%d %d",&first_operand,&second_operand);
                if(first_operand < 0 || second_operand<0){ //if given inputs are less than 0 we ask user again for new inputs
                    errorFlag = 1;
                }
            } while (errorFlag);
            printf("\n*****************\n");
            result = fmod(first_operand,second_operand);
            scientific_writer(result,m,n,is_negative);
            break;
        default:
            break;
        }
    }
    else{//if the given type_of_calc value is not equal to S or s then this else statement will work
        int first_operand,second_operand;
        do //check if the user gives valid operator characters else ask again
        {
            if(errorFlag){
                printf("\nPlease give a valid operator character(+,*,/,!,^,-,%): ");

            }
            else{
                printf("\nPlease give operator(+,*,/,!,^,-,%)");

            }
            getchar();//clearing out the stream 
            scanf("%c",&operator);
            if(operator != '+' && operator != '-' && operator != '*' && operator != '%' && operator != '^'){ //if the operator input is not what we wanted we gonna ask again 
                errorFlag = 1;
            }
        } while (errorFlag);
        
        int result = 0;
        int is_negativePow = 0;
        switch (operator)
        {
        case '+'://if operator character is + simply add two given operands and print them to console
            printf("\n*****************\n");
            printf("\nPlease give two operands: ");
            scanf("%d %d",&first_operand,&second_operand);
            printf("\n*****************\n");
            printf("The result is : %d",first_operand+second_operand);
            break;
        case '-'://if operator character is - simply substract two given operands and print them to console
            printf("\n*****************\n");
            printf("\nPlease give two operands: ");
            scanf("%d %d",&first_operand,&second_operand);
            printf("\n*****************\n");
            printf("The result is : %d",first_operand-second_operand);
            break;
        case '*'://if operator character is * simply multiply two given operands and print them to console
            printf("\n*****************\n");
            printf("\nPlease give two operands: ");
            scanf("%d %d",&first_operand,&second_operand);
            printf("\n*****************\n");
            printf("The result is : %d",first_operand*second_operand);
            break;
        case '/'://if given operator character is / take two operands from user and make sure that second one is not zero and 
                //divide the two numbers and simply print them to console
            printf("\n*****************\n");
            do// there is a do-while loop for avoid to divide by zero error 
            {
                if(errorFlag){
                    printf("Dividing by zero error!..\n");
                }
                printf("\nPlease give two operands: ");
                scanf("%d %d",&first_operand,&second_operand);
                if(second_operand==0){
                    errorFlag = 1;
                }
            } while (second_operand == 0);
            errorFlag = 0;
            printf("\n*****************\n");
            printf("The result is : %d",first_operand/second_operand);
            break;
       
        case '!'://if given operator is equal to ! make sure that given  number is not less than zero
                //if the number is positive as we wanted simply take factorial  and print to the console
            do{
                if(errorFlag){
                    printf("\nCant take a negative numbers factorial!...");
                }
                printf("\nPlease give only one operand: ");
                scanf("%lf",&first_operand);
                if(first_operand<0){
                    errorFlag = 1;
                }
            }while (errorFlag);
            if(first_operand==0){
                printf("\nThe result is; 1");
            }
            else if(first_operand==1){
                printf("\nThe result is: 1");
            }
            else{
                result = 1;
                for(int j=1;j<=first_operand;j++){
                result = result * j;
                }
                printf("\nThe result is : %d",result);
            }
            break;
        case '^':
            

            printf("\n*****************\n");
            printf("Give base number: ");
            scanf("%d",&first_operand);
            printf("\nGive the power: ");
            scanf("%d",&second_operand);
            printf("\n*****************\n");
            
            if(second_operand==0){
                result = 1;
            }                           //if second operand is equal to zero or first_operand is equal to 1 result is simply 1
            else if(first_operand == 1){
                result = 1;                 
            }
            else if(second_operand < 0 ){ //if second operand is less than zero 
                is_negativePow= 1; //checking negativePower boolean
                second_operand = -1 * second_operand; //make sure  the second operand is positive sign to avoid any errors may cause by pow function
                result = pow(first_operand,second_operand); // use the math.h librarys pow function and store the data in result variable
               

            }
            else if(first_operand<0){//if first operand is less than zero
                if(second_operand % 2 == 0){ // check if the second operand is multiple or 2 or not
                    first_operand = -1 * first_operand; //if thats the case change the value of first operand to positive
                    result = pow(first_operand,second_operand); // use the math.h librarys pow function and store the data in result variable 
                    
                }
                else
                {
                    first_operand = -1 * first_operand;//if second operand is not multiple of 2 
                    result = pow(first_operand,second_operand); //simply take the power 
                    result = result * -1; // then multiply it by -1 to change the sign 
                

                }
            }
            else{
                result = pow(first_operand,second_operand); //simply take the power of 2 given numbers
            }
            
            if(is_negativePow){//if the given second_operand is negative print it like this
                printf("The result is: 1/%d",result);
                printf("\n*****************\n");

            }
            else{//if not print it like this
                printf("The result is : %d",result);
                printf("\n*****************\n");
            }
            break;
        
        
        case '%':
            printf("\n*****************\n");
            do
            {
                if(errorFlag){ 
                    printf("Dont give negative numbers..\n");
                }
                printf("\nPlease give two operands: ");
                scanf("%d %d",&first_operand,&second_operand);
                if(first_operand < 0 || second_operand<0){
                    errorFlag = 1;
                }
            } while (errorFlag);
            printf("\n*****************\n");
            printf("The result is : %d",first_operand%second_operand);

            break;
        default:
            break;
        }
    }
    



}


void part3_grade_calculate(){
    float exam_results = 0, assgn_results = 0;//two variables for each different result type 0.4 and 0.6
    float final_grade=0; // final grade variable
    float grade1,grade2,grade3; // variables for all exam grades
    float assgn1,assgn2;//2 variables for assignment grades
    
    printf("*****************\n");
    printf("Enter 3 exam grades of student: ");
    scanf("%f %f %f", &grade1, &grade2, &grade3);   //we take 3 inputs for each grade variable
    printf("\nEnter 2 assignment grades of student: ");
    scanf(" %f %f", &assgn1, &assgn2);//we take 2 inputs for each assignment grade variable
   exam_results = ((grade1+grade2+grade3)/3) * 0.6;//our exam results 
   assgn_results = ((assgn1+assgn2)/2) * 0.4; //assignment results
   final_grade = exam_results+assgn_results;//final grede
    if(final_grade>=60.0){// if final grade bigger or equal to 60 print passed
        printf("\nFinal Grade: %.2lf, Passed!",final_grade);
    }                                                                       //printing out the outputs as wanted 
    else if(final_grade<60.0){
        printf("\nFinal Grade: %.2lf, Failed!",final_grade);

    }

    printf("\n*****************\n");
    


}
