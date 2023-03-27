#include <stdio.h>
#include <stdlib.h>
#include "util.h"
int menu(void){
    int choice;
    printf("\nRun again(1),for exitting the program(2):");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        return 1;
        
    case 2:
        return 0;
    default:
        return 0;
        
    }

}
void main(void){
    do
    {
        part1_leapyear();
        int k = getchar(); // for clearing out the stream
        part2_scientific_calculator();
        int m = getchar();
        part3_grade_calculate();
    } while (menu() == 1);
    
}