#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "util.h"

int at_least_one = 0;// a flag to check if the user bought anything or not

//function to read the receipt from the file and display it on the console
int read_receipt(){
    FILE *filePtr = NULL;
    char comingChar;
    if(at_least_one){
        printf("\n\n\n");
        filePtr = fopen("receipt.txt","r");//opening the receipt file for reading the last version of receipt
        while (feof(filePtr) == 0)
        {
            comingChar = getc(filePtr);
            printf("%c",comingChar); // printing the all chars by using while loop
        }
        printf("\n\n\n");

    }
    else{
        printf("\n**************************\n");
        printf("You did not buy anything.");
        printf("\n**************************\n");
    
    }
    
}

//function to create a receipt file and write the first texts
int create_receipt(){
    time_t rawtime;
    time(&rawtime);
    char buffer[80];
    struct tm *info;
    info = localtime(&rawtime);
    strftime(buffer,80,"%x-%I:%M%p", info);
    FILE *recePtr = fopen("receipt.txt","w");//12 18 open the receipt file 
    fprintf(recePtr,"|--------------------------------|\n");
    fprintf(recePtr,"|%-12s  %18s|\n","220104004106",buffer);
    fprintf(recePtr,"|--------------------------------|\n");
    
    fprintf(recePtr,"|%-15s  %15s|\n","PRODUCT","PRICE");
    fprintf(recePtr,"|--------------------------------|\n");
    fclose(recePtr);
    return 0; 
}

//function to calculate the discounts and taxes and write the final total on the receipt
void end_receipt(float last_price,int is_student){
    float discountStudent = 0;
    float discount150 = 0;
    float tax = last_price * 0.18;
    
    if(last_price >= 150){
        discount150 = last_price *0.10;
    }

    if(is_student){
        discountStudent = last_price * 0.125;
    }

    float total = last_price - discount150 - discountStudent + tax;

    FILE* filePtr = NULL;
    filePtr = fopen("receipt.txt","a");//open the file on append mode
    fprintf(filePtr,"|%-10s %21.2f|\n","TOTAL",last_price);    
    if(discount150>0 && discountStudent>0){
        fprintf(filePtr,"|%-15s %15.2f|\n|%-15s %13.2f|\n","150Tl discount: ",discount150,"Student discount: ",discountStudent);
    }
    else if(discount150>0 && discountStudent==0){
        fprintf(filePtr,"|%-15s %15.2f|\n","150Tl discount: ",discount150);
    }
    else if(discountStudent>0 && discount150==0){
        fprintf(filePtr,"|%-15s %13.2f|\n","Student Discount: ",discountStudent);

    }
    fprintf(filePtr,"|--------------------------------|\n");
    fprintf(filePtr,"|%-15s %16.2f|\n","Total:",total-tax);
    fprintf(filePtr,"|%-15s %16.2f|\n","Total+VAT:",total);

    fprintf(filePtr,"|--------------------------------|\n");

    fclose(filePtr);

}

int menu_printer(void){//firstly called function for writing menu str to menu.txt
    int newLineCount = 0;

    FILE *filePtr = NULL;
    filePtr = fopen("menu.txt","w");
    fprintf(filePtr,"Items\tPrices(TL)\n1)Iskender\t78.50\n2)Lahmacun\t24.50\n3)KoftePorsiyon\t65.45\n4)PirincPilavi\t25.00\n5)MercimekCorbasi\t25.50\n6)KellePaca\t35.50\n7)Doner Porsiyon\t45.00\n8)DilimBaklava\t17.50\n9)Kunefe\t 45.00\n10)Kaymak\t14.50");
    fclose(filePtr);
    
}

float price_return(FILE *filePtr,int choose){//returning the price value of the selected item on menu
    int counter = 0;
    float price;
    for(int i=0;i<11;i++){
                int id;
                if(i==0){
                    fscanf(filePtr,"%*[^\n]\n");//for passing the first line which ITEM AND PRICE text

                }
                else{
                    fscanf(filePtr,"%d)%*[^0-9]%f",&id,&price);//taking id and price values
                    }
                if(choose == id){//if the users choice is equal to id send the price data back
                    return price;
                }
            }
}

char* name_return(FILE *filePtr,int choose){//name_return function that return a char pointer which is the item name
    char* name = malloc(sizeof(char)*15);//allocating the memory for name variable
    int counter = 0;//counter variable for counting the newline characters to take right name value
    
    rewind(filePtr);
    while(feof(filePtr)==0){
                if(getc(filePtr)=='\n'){
                    counter++;
                }
                if(counter==choose){

                    fscanf(filePtr,"%*[^a-zA-Z]%s%*[^\n]\n",name);//simply pass all the data till you see an character take the string and pass any other data on line
                    //fgets(name,15,filePtr);

                    return name; // return the char pointer name
                    
            }
    }
    
    
    
    
    
}


int new_logic(){
    FILE *fileptr = NULL;
    int id;
    float price;
    int choose;
    int servings;
    int errorFlag = 0;

    
    fileptr = fopen("menu.txt","r");//open the menu txt on read mode
    create_receipt();//create the receipts initial texts like 220104004106 and time value
    
    float last_price1 = 0;
    char is_Student;//a boolean for checking the user is student or not
   int i = 0;
    do
   
    {
        
        rewind(fileptr);
        
        
        while(feof(fileptr)==0){
            printf("%c",getc(fileptr));//while loop for printing out the menu
        }
        
        do//do while loop for taking valid inputs on item choosing
        {
            if(errorFlag){
                printf("\nInvalid input try again!\n");
            }
            printf("\nPlease choose a item from menu(1-10): ");
            scanf("%d",&choose);
            if(choose>10 || choose<0){
                errorFlag = 1;
            }
            else{
                errorFlag= 0;
            }
        } while (errorFlag);
    
        
        if(choose != 0){//if the user is not choose 0 ask for serving
            printf("\nHow many serving you want?");
            scanf("%d",&servings);
        }
        
        
        getchar();//clear the buffer
        
        if(servings == 0 || choose == 0){
            
            if(at_least_one){//if  at least one item is buyed
                servings = 0;//for breaking out the while loop
                do
                { //do while loop for taking the valid input for isStudent variable
                    if(errorFlag){
                        printf("\nPlease give one of Y or N characters.\n");
                    }
                    printf("\nAre you a student?(Y/N): ");

                    scanf("%c",&is_Student);
                    if(is_Student != 'Y' && is_Student != 'N'){
                        errorFlag = 1;
                    }
                    else{
                        errorFlag = 0;
                    }
                } while (errorFlag);
                
                errorFlag = 0;
                switch (is_Student)
                {
                case 'Y'://if user is student
                    end_receipt(last_price1,1);
                    break;
                
                case 'N':
                    //if user is not student
                    end_receipt(last_price1,0);
                    break;
                default:
                    break;
                }
            }
            else{
                read_receipt();
                break;
            }
            //checkout
        }
        else{//if serving or choose data is not 0 
            at_least_one = 1;//at_least_one item is buyed
            FILE *recePtr = fopen("receipt.txt","a");//append the receipt 
            int counter = 0;
            char *name;
            rewind(fileptr);//rewind the filepointer which is reading menu
            price = price_return(fileptr,choose);//returning price
            price = price * servings;
            last_price1 += price;
            name = name_return(fileptr,choose);//returning name
            
            fprintf(recePtr,"|%-2d* %-20s %7.2f|\n",servings,name,price);//writing the data to receipt.txt 
            fclose(recePtr);//closing the receipt pointer
            
            }
                
            
           
            
      
        
    }while (servings != 0);
    
    if(at_least_one){
        read_receipt();

    }

}



