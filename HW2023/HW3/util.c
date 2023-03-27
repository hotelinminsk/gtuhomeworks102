#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "util.h"

int move_count = 0;

void game_help(){ //help function
    printf("The character is able to move one space in any of the four cardinal directions: up,down,left and right\nDiagonal moves are not allowed. The user will input their desired move using the following keys w for up,a for left,s for down,d for right.\nIf the character attempts to move through a wall game ends. ");
    game_menu();
}

int board(int boardRow,int boardCol,int *charX,int *charY,int *doorX,int *doorY){//function that draws board,door and users location as long as game finishes
    char player = 'C'; //character
    char door = 'D'; // door
    
    
    for(int i=0;i<boardCol*2;i++){ //top border
        printf("--");
    }
    printf("\n");
    printf("\n");
    for(int row=0;row<boardRow;row++){ //drawing the rows of board loop
        for(int col=0;col<boardCol;col++){ //drawing the column of board loop
            if(row== *charY && col == *charX){  //if loop is in the position of characters's coordinates  draw |C
                //user inside the box
                printf("|%c",player);
                
            }
            else if(row==*doorY && col == *doorX){  //if loop is in the position of door's coordinates  draw |D 
                //door inside the box
                printf("|%c",door);


            }
            else{ //If the loop is not in the position of the characters c and d simply draw | 
                printf("| ");
            }

        }
        printf("\n");
    }
    
    printf("\n");
    
    
    
    for(int i=0;i<boardCol*2;i++){//bottom border
        printf("--");
    }
}


int move(int *charX,int *charY,int boardX,int boardY,int *doorX,int *doorY){//function that allows the character to move in the desired direction
    getchar();//clearing the buffer 
    int is_win = 0; //boolean for checking is the situation is a win or not
    char input; //input variable for direction input
    move_count++; //move count is incremented as long as this function called
    printf("\nWHICH WAY YOU WANNA GO?:(w,a,s,d): ");
    scanf("%c",&input);
    
    switch (input)
    {
    case 'w'://if users direction input is w
        if(0 == *charY ){//if the user is placed on 0th row and still gives a w input then game is lost 
            printf("\nYou lose the game going back the menu...\n");
            game_menu();

            //end the game 
        }
        else{
            *charY -= 1;//if user is not placed on the 0th row on board,simply substract 1 from its y coordinates and check win condition
            is_win = winCheck(charX,charY,doorX,doorY); //check win condition
            if(is_win){//if user is winned the game simply return the game menu
                //user winned call menu
                game_menu();
                return 1;
            }
            else{//if user is not winned the game, draw the board 
                board(boardY,boardX,charX,charY,doorX,doorY);
                
                return 0;

            }
            

        }
        
        
        break;
    
    case 's'://if users direction input is s
     if(boardY-1 == *charY){//if user is placed last-1 row of board ant still gives a s input then game is lost
            //end the game 
            printf("\nYou lose the game going back the menu...\n");
            game_menu();
        }
        else{//else
            *charY += 1;//increment the users Y value by one and check if condition is win or not
            is_win = winCheck(charX,charY,doorX,doorY);
            if(is_win){//if win end the game and call menu afterwards
                //oyunu kazandı menuyu cagır
                game_menu();
                return 1;
            }
            else{//else
                board(boardY,boardX,charX,charY,doorX,doorY);//draw the board
                
                return 0;

            }

        }
        
        break;
    
    case 'd'://if users direction input is d
        if(*charX == boardX-2){//check if the user is placed on board columnlast-2 if user is placed there and still gives d input end the game
            //end the game
            printf("\nYou lose the game going back the menu...\n");
            game_menu();
        }
        else{//else
            *charX += 1;//increment users x value by one and check if the condition is win or not
            is_win = winCheck(charX,charY,doorX,doorY);
            if(is_win){//if condition is win call the game menu
                //oyunu kazandı menuyu cagır
                game_menu();
                return 1;
            }
            else{//if condition is not win draw the board
                board(boardY,boardX,charX,charY,doorX,doorY);
                
                return 0;

            }

        }
        break;
    
    case 'a'://if the users direction input is a 
        if(*charX == 0){//check if user placed on first column of board and gives a input, end the game
            //end the game
            printf("\nYou lose the game going back the menu...\n");
            game_menu();
        }
        else{//else
            *charX -= 1;//substract 1 from users x coordinates
            is_win = winCheck(charX,charY,doorX,doorY);//check if the condition is win or not
            if(is_win){//if condition is win end the game and call the game menu
                //oyunu kazandı menuyu cagır
                game_menu();
                return 1;
            }
            else{//if condition is not win draw the board
                board(boardY,boardX,charX,charY,doorX,doorY);
                
                return 0;

            }

        }
        break;
    default:
        break;
    }
}


int winCheck(int *charX,int* charY,int *doorX,int *doorY){//function for checking the condition is win or not
    if(*charX == *doorX && *charY == *doorY){ //if users x and y values are equal to doors x and y values game is win
        printf("\n*********************\n");
        printf("GAME IS OVER, YOU WON!");
        printf("\n*********************\n");
        printf("\nMOVE COUNT: %d",move_count);
        return 1;

    }
    else{
        return 0;
    }
}

int game_menu(){//game menu function
    int choice;//choice variable
    int errorFlag = 0;//a boolean for checking invalid inputs
    printf("\n\tMAIN MENU\t\n");
    do
    {
        
        if(errorFlag){//if errorflag is raised then it means user give a invalid input,warn him and ask again
            printf("\nPlease do not give any inputs other than 1,2,3...\n");
        }
        printf("\tNEW GAME(1)\t\n");
        printf("\tHELP(2)\t\n");
        printf("\tEXIT(3)\t\n");
        scanf("%d",&choice);//taking the choice input from user
        if(choice != 1 && choice != 2 && choice !=3){//if the input is not 1 2 or 3 then input is invalid and we raise the errorFlag
            errorFlag = 1;
        }
        else{
            errorFlag = 0;
        }
    } while (errorFlag);//as long as errorFlag is raised this loop will continious 
    
    switch (choice)//if the coice is valid check that inputs value  1 2 or 3
    {
    case  1://if the choice is 1 then call the game_logic function and start the game
        game_logic();
        break;
    case 2://if choice is 2 call the help function
        game_help();
        break;
    case 3://if choice is 3 exit the program
        exit(1);
        break;
    default:
        break;
    }

   return 0;

}


int game_logic(){//game_logic function for taking the row and column values of board from user creating user and doors positions
    srand(time(NULL));//seed of rand function 
    int boardX,boardY;//variables for boards x and y values which we will take from user
    int errorFlag = 0; //boolean for checking invalid inputs
    printf("\nPlease give board row size(max:10,min:5): ");
    //TAKING THE ROW SIZE WITHOUT ANy UNWANTED INPUTS 
    do
    {
        
        scanf("%d",&boardY);
         if(boardY<5){//if given board row size is less than 5 or bigger than 10  we warn the user with the correct error messages 
            printf("\nRow size cant be lesser than 5..");
            errorFlag = 1;
        }
        else if(boardY>10){
            printf("\nRow size cant be bigger than 10...");
            errorFlag = 1;
        }
        else{
            errorFlag = 0;
        }
    } while (errorFlag);//as long as errorFlag is raised this loop will continiue
    errorFlag = 0;
    
    
    printf("\nPlease give board column size(max:10,min:5): ");
    //TAKING THE COLUMN SIZE WITHOUT ANY UNWANTED INPUTS 
    do
    {
        
        scanf("%d",&boardX);//if given board column size is less than 5 or bigger than 10  we warn the user with the correct error messages 
        if(boardX<5){
            printf("\nColumn size cant be lesser than 5..");
            errorFlag = 1;
        }
        else if(boardX>10){
            printf("\ncolumn size cant be bigger than 10...");
            errorFlag = 1;
        }
        else{
            errorFlag = 0;
        }
    } while (errorFlag);//as long as errorFlag is raised this loop will continiue
    
    errorFlag = 0;
    int charX,charY,doorX,doorY;//we declare our variables that will store the character and door's x and y values
    
    switch (boardX)//we don't allow character or door to be created completely randomly, if we allow that character or door can sometimes be drawn out of bounds 
    {
    case 5://if user gives board's row value as 5 
        charX = rand() % 4 ;
        doorX = rand() % 4 ;
        break;
    case 6://if user gives board's row value as 6 
        charX = rand() % 5;
        doorX = rand() % 5;
        break;
    case 7://if user gives board's row value as 7 
        charX = rand() % 6;
        doorX = rand() % 6;
        break;
    case 8://if user gives board's row value as 8 
        charX = rand() % 7;
        doorX = rand() % 7;
        break;
    case 9://if user gives board's row value as 0 
        charX = rand() % 8;
        doorX = rand() % 8;
        break;
    case 10://if user gives board's row value as 10 
        charX = rand() % 9;
        doorX = rand() % 9;
        break;
    default:
        break;
    }

    switch (boardY)//we don't allow character or door to be created completely randomly, if we allow that character or door can sometimes be drawn out of bounds 
    {
    case 5://if user gives board's column value as 5 
        charY = rand() % 4;
        doorY = rand() % 4;
        break;
    case 6://if user gives board's column value as 6 
        charY = rand() % 5;
        doorY = rand() % 5;
        break;
    case 7://if user gives board's column value as 7 
        charY = rand() % 6;
        doorY = rand() % 6;
        break;
    case 8://if user gives board's column value as 8
        charY = rand() % 7;
        doorY = rand() % 7;
        break;
    case 9://if user gives board's column value as 9 
        charY = rand() % 8;
        doorY = rand() % 8;
        break;
    case 10://if user gives board's column value as 10 
        charY = rand() % 9;
        doorY = rand() % 9;
        break;
    default:
        break;
    }
    
    if(charX == doorX && charY == doorY){//It's a pretty small chance, but if the character and door coordinates are randomized equally, we manually change their values.
        charX = 0;
        charY = 5;
        doorY = 2;
        doorX = 4;
    }
    
    board(boardY,boardX,&charX,&charY,&doorX,&doorY);//first board

    int game_is_up = 0;//game is up boolean

    do
    {
        game_is_up = move(&charX,&charY,boardX,boardY,&doorX,&doorY);
        
    } while (game_is_up != 1);//This loop will continue to run until the game ends by losing or beating.

    
}
