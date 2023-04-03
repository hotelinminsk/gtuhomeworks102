#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "util.h"

//Function to select a random choice for the AI player
int ai_select(){
    int choice ;
    srand(time(NULL));
    choice = rand() % 3 + 1;

    return choice;
}

//Function to check win conditions and return the result
int win_conditions(int user_choice,int ai_choice){
    if(user_choice == 1){
        switch (ai_choice)
        {
        case 1:
            //tie
            printf("\nYou chose Stone. I chose Stone.");
            return 0;
            break;
        
        case 2:
            //lose
            printf("\nYou chose Stone. I chose Paper.");
            return -1;
            break;
        case 3:
            //win
            printf("\nYou chose Stone. I chose Scissors.");

            return 1;
            break;
        default:
            break;
        }
    }
    else if(user_choice == 2){
        switch (ai_choice)
        {
        case 1:
            //win
            printf("\nYou chose Paper. I chose Stone.");

            return 1;
            break;
        
        case 2:
            //tie
            printf("\nYou chose Paper. I chose Paper.");

            return 0;
            break;
        case 3:
            printf("\nYou chose Paper. I chose Scissors.");

            //lose
            return -1;
            break;
        default:
            break;
        }
    }
    else if(user_choice == 3){
        switch (ai_choice)
        {
        case 1:
            //lose
            printf("\nYou chose Scissors. I chose Stone.");

            return -1;
            break;
        case 2:
            //win
            printf("\nYou chose Scissors. I chose Paper.");

            return 1;
            break;
        case 3:
            //tie
            printf("\nYou chose Scissors. I chose Scissors.");

            return 0;
            break;
        default:
            break;
        }        
    }

}
//Function to handle the game logic and call the functions on right order
int game_logic(){
    int user_choice;
    int ai_choice;
    int error_flag = 0;
    int result;
    do
    {
        if(error_flag){
            printf("\nPlease give a valid input.\n");
        }
        else{
            printf("\nPlease make a choice!\n");

        }
        printf("\n1)ROCK, 2)PAPER, 3)SCISSORS: \n");
        scanf("%d",&user_choice);
        if(user_choice != 1 && user_choice != 2 && user_choice != 3){
            error_flag = 1;
        }
        else{
            error_flag = 0;
        }
    } while (error_flag);
    
    

    ai_choice = ai_select();


    result = win_conditions(user_choice,ai_choice);

    switch (result)
    {
    case -1:
        printf("You lose the game!\n");
        break;
    
    case 0:
        printf("Its a TIE!\n");
        break;
    case 1:
        printf("You won the game!\n");
        break;
    default:
        break;
    }


    
}

//Function for dislpayin the game menu and handling the user inputs
int game_menu(){
    char newgame_choice;
    int error_flag = 0;  
    
do {
    error_flag = 0;
    game_logic();
    printf("\nDo you want to play again? (Y/N): ");
    while(getchar() != '\n');//while loop for clearing the buffer
    do//do while loop for error handling
    {
        if(error_flag){
            printf("\nPlease give a valid input: ");
        }
        newgame_choice = getchar();
        if (newgame_choice != 'Y' && newgame_choice != 'N'){
            error_flag =1;
        }
        
        else{
            error_flag = 0;
        }
        while (getchar() != '\n');//while loop for clearing the buffer

        
    } while (error_flag);
    
} while(newgame_choice == 'Y');   
    

    

}