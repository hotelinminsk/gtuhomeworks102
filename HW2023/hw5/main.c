#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*GLOBAL VARIABLES*/
char winner;
char letters[] = {'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};


typedef struct{
    float vector[3];
}color_struct;

typedef enum{
        RED =0,
        GREEN,
        BLUE,
        YELLOW,
        ORANGE,
}COLOR;

float colorVectors[5][3] ={
        {1,0,0}, // RED
        {0,1,0}, //GREEN
        {0,0,1}, // BLUE
        {0.5,0.5,0}, // YELLOW
        {0.5,0.5,0.2}, // 0RANGE
    };


/*END*/






/*FUNCTION DECLARATIONS*/
/*PART1 FUNCTIONS*/
void toLower(char*);
void frequency_printer(char letters[26],int letterCounts[26]);
void part1_lettercount(char letters[]);
/*PART2 FUNCTIONS*/
float euclidean_distance(float vect[],float baseColors[]);
COLOR colorMixer(COLOR col1,COLOR col2);
COLOR colorMixerCaller(COLOR(*colorMixer)(COLOR,COLOR),COLOR col1, COLOR col2);
void part2_colors();
/*PART 3 FUNCTIONS*/
int move(char board[3][3],char player);
void drawBoard(char board[3][3]);
void game_menu();
int checkWin(char board[3][3]);
int checkDraw(char board[3][3]);
void win();
void draw();
void gameLogic(char player1,char player2,char board[3][3]);
void startGame(char player1,char player2);
void game_menu();

/*END*/






/*PART1 FUNCTIONS*/
void toLower(char* letter){ // FUNCTION TO MAKE UPPERCASE LETTERS LOWERCASE
    *letter = *letter + 32;//if a letter is uppercase its ascii code is 32 lesser than its lowercase version 
                            //so we add 32 to letter to make it lowercase
}

void frequency_printer(char letters[26],int letterCounts[26]){ //this function takes letters array which has all lowercase letters and lettercounts array to print out the 
    printf("\nLetter frequency: \n");                          //letters counts
    for(int i=0;i<26;i++){
        printf("\n%-2c: %4d",letters[i],letterCounts[i]);
    }
}
void part1_lettercount(char letters[]){
    int* letterCounts = calloc(26,sizeof(int)*26); //allocated the memory for letterCounts array which has 26 items they all set to zero in the beggining because of calloc
    char fileName[100]; //an char array for fileName which we will take from user
    char comingChar; // a char variable for comingChar
    FILE *filePtr = NULL;
    printf("\nEnter the file name = ");
    scanf("%s",fileName);
    filePtr = fopen(fileName,"r");
    while(feof(filePtr) == 0){ //while our filePointer is not on end of file
        comingChar=getc(filePtr); // set the comingChar variable to fileptrs char
        if(comingChar>='A' && comingChar<='Z'){ //if comingChars ascii code is between A and Z(which means coming char is uppercase Letter)
            toLower(&comingChar); //call the toLower function to make it lowercase and set it to comingChar`s value because we send the pointer of comingChar
        }

        for(int i=0;i<26;i++){//if our char is equal to any of letters in letters array we gonna increment the value on the letterCounts which`s index is equal to letters index
            if(comingChar == letters[i]){
                
                letterCounts[i]++;

            }
           
        }
    }

    frequency_printer(letters,letterCounts); // calling the frequancy_printer function to print out the letters frequancy
    fclose(filePtr); // closing the filepointer
}
/*END OF PART1*/

/*PART2 FUNCTIONS*/
float euclidean_distance(float vect[],float baseColors[]){//euclidean_distance function
    float distance = 0;// creating the float distance variable
    for(int j=0;j<3;j++){
        distance  += pow((vect[j] - baseColors[j]),2);

    }
    return distance;
}


COLOR colorMixer(COLOR col1,COLOR col2){ //colormixer function
    float newColorVector[3];// creating the newColorVector

    for(int i =0;i<3;i++){//setting the newColorVector array`s values 
        newColorVector[i] = (colorVectors[col1][i] + colorVectors[col2][i])/2;
    }
    float minDistance = 999999;//mindistance equal to infinity
    COLOR closestColor; // closestColor variable
    for(int i=0;i<5;i++){
        float distance = euclidean_distance(newColorVector,colorVectors[i]);
        if(distance<minDistance){//if the distance is lower then minDistance value our new minDistance value is set to distance
            minDistance = distance;
            closestColor = i;
        }
    }
    return closestColor;
}   


        


COLOR colorMixerCaller(COLOR(*colorMixer)(COLOR,COLOR),COLOR col1, COLOR col2){//taking the colormixer functions pointer and col1 col2 as arguments
    COLOR mixedColor = colorMixer(col1,col2);//calling the function
    return mixedColor;
}
  
void part2_colors(){
    char colorChoice1;
    char colorChoice2;
    int errorFlag = 0;
    COLOR col1,col2;
    while(getchar()!= '\n');//clearing out the array

    printf("\nGive two colors for mixing.\n");
    do// do - while loop for not letting users to  input any invalid inputs 
    {
        if(errorFlag){
            printf("\nGive valid input.\n");
        }
        printf("First color[r,g,b,y,o]: ");
        colorChoice1 = getchar();
        if(colorChoice1 != 'r' &&colorChoice1 != 'g' &&colorChoice1 != 'b' &&colorChoice1 != 'y' &&colorChoice1 != 'o'){
            errorFlag = 1;
        }
        else{
            errorFlag = 0;
        }
    } while (errorFlag);


    while(getchar()!= '\n');

    do
    {// do - while loop for not letting users to  input any invalid inputs 
        if(errorFlag){
            printf("\nGive valid input.\n");
        }
        printf("Second color[r,g,b,y,o]: ");
        colorChoice2 = getchar();
        if(colorChoice2 != 'r' &&colorChoice2 != 'g' &&colorChoice2 != 'b' &&colorChoice2 != 'y' && colorChoice2 != 'o'){
            errorFlag = 1;
        }
        else{
            errorFlag = 0;
        }
    } while (errorFlag);
    
    switch (colorChoice1)
    {
    case 'r':
        col1 = RED;
        break;
    case 'g':
        col1 = GREEN;
        break;
    case 'b':
        col1 = BLUE;
        break;
    case 'y':
        col1 = YELLOW;
        break;
    case 'o':
        col1 = ORANGE;
        break;
    default:
        break;
    }

    switch (colorChoice2)
    {
    case 'r':
        col2 = RED;
        break;
    case 'g':
        col2 = GREEN;
        break;
    case 'b':
        col2 = BLUE;
        break;
    case 'y':
        col2 = YELLOW;
        break;
    case 'o':
        col2 = ORANGE;
        break;
    default:
        break;
    }
    
    COLOR lastColor = colorMixerCaller(&colorMixer,col1,col2);
    
    switch (lastColor)
    {
    case 0:
        printf("\nMIXED COLOR : RED [1,0,0]");
        break;
    case 1:
        printf("\nMIXED COLOR : GREEN [0,1,0]");

        break;
    case 2:
        printf("\nMIXED COLOR : BLUE [0,0,1]");

        break;
    case 3:
        printf("\nMIXED COLOR : YELLOW [0.5,0.5,0]");

        break;
    case 4:
        printf("\nMIXED COLOR : ORANGE [0.5,0.5,0.2]");

        break;
    default:
        break;
    }
    



    
}


/*END OF PART2*/


/*PART 3 FUNCTIONS*/
void drawBoard(char board[3][3]){//function to drawBoard
    for(int i=0;i<3;i++){
        printf("\n");
        printf("\t");
        for(int j=0;j<3;j++){
            printf("|");
            printf("%c",board[i][j]);
            printf("|");
        }
        printf("\n");
    }
    printf("\n");
}

int move(char board[3][3],char player){
    int x,y;
    int errorFlag = 0; // errorFlag to catch errors
    printf("\nRound of Player %c.\n",player);
    do
    {
        if(errorFlag){
            printf("\nYou can`t move to a place that already occupied!\nPlease give again(x,y):");
        }
        else{
            printf("\nPlease give an move(x,y): ");
        }
        scanf("%d %d",&x,&y);
        x -= 1;
        y -= 1;
        if(board[y][x] != '_'){//if the place that user choose is occupied ask for any other coordinates
            errorFlag = 1;
        }
        else{
            errorFlag = 0;
        }
    } while (errorFlag);

    if(board[y][x] == '_'){ // if place is not occupied change the place`s char value to player`s character 
        board[y][x] = player;
        return 1;
    }
    else{
        return 0;
    }
    
    
}
int checkDraw(char board[3][3]){//check if the position is draw
    int ocuppied_bool = 1;
    int m = 15;
    for(int i =0; i<3;i++){
        for(int j=0; j<3; j++){
            if(board[i][j] == '_' ){  //check if all the places on board is occupied
                ocuppied_bool = 0;
                break;
            }
            
        }
    }
   if(ocuppied_bool == 0){
    return 0;  //if its occupied return zero
   }
   else if(ocuppied_bool == 1){// if not occupied check if the position is win or not
     m = checkWin(board);
     if(m == 1){ // if position is win return zero
        return 0;
     }
     else{ // if not position is draw so return 1
        return 1;
     }
   }
}

int checkWin(char board[3][3]){//function to check the position is win or not
    char prevChar;
    for(int row=0;row<3;row++){ // checking the same row different column win conditions
        if((board[row][0] == board[row][1]) && (board[row][1] == board[row][2]) && (board[row][0] == board[row][2]) && (board[row][0] != '_')){
            if(board[row][0] == 'X'){ // checking for winners type is it X or O based on this changing the global variable winner
                winner = 'X';
            } 
            else{
                winner = 'O';
            }
            return 1;//if position is win return 1
        }
    }

    for(int col=0;col<3;col++){//checking the same column different row win conditions
        if((board[0][col] == board[1][col]) && (board[1][col] == board[2][col]) && (board[0][col] == board[2][col]) && (board[0][col] != '_')){
            //win
            if(board[0][col] == 'X'){// checking for winners type is it X or O based on this changing the global variable winner
                winner = 'X';
            } 
            else{
                winner = 'O';
            }
            return 1;//if position is win return 1
        }
    }

    if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && (board[0][0] != '_')) { //checking the diagonal win conditions
        if(board[0][0] == 'X'){// checking for winners type is it X or O based on this changing the global variable winner
                winner = 'X';
            } 
            else{
                winner = 'O';
            }
        return 1;//if position is win return 1
    }
    else if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]) && (board[0][2] != '_')) {//checking the diagonal win conditions
        if(board[0][2] == 'X'){// checking for winners type is it X or O based on this changing the global variable winner
                winner = 'X';
            } 
            else{
                winner = 'O';
            }
        return 1; //if position is win return 1
    }
    
    
    return 0;//if position is not match does not match any of the conditions above return 0
}

void win(){//function to call when position is win
    int choice;
    int errorFlag = 0;
    char d;
    while((d=getchar()) != '\n');
    printf("\nPlayer %c has won the game!",winner);
    do //a do while loop that asks the user if they want to play again or not, and prevents them from entering invalid input
    {
        if(errorFlag){
            printf("\nPlease give an valid input 1 or 2:");
        }
        else{
            printf("\nGAME HAS ENDED!\n");
            printf("Do you wanna play again?\n1-Yes\n2-Exit:");
        }
        scanf("%d",&choice);
        if(choice != 1 && choice != 2){
            errorFlag = 1;
        }
        else{
            errorFlag = 0;
        }

    } while (errorFlag);

    if(choice == 1){
        game_menu();
    }
    else{
        exit(1);
    }
    
}

void draw(){//function to call when the position is draw
    int choice;
    int errorFlag = 0;
    char d;
    fflush(stdin);
    printf("\n Game has ended,its a tie!");
    do//a do while loop that asks the user if they want to play again or not, and prevents them from entering invalid input
    {
        if(errorFlag){
            printf("\nPlease give an valid input 1 or 2:");
        }
        else{
            printf("\n\tGAME HAS ENDED!");
            printf("\nDo you wanna play again?\n1-Yes\n2-Exit:");
        }
        scanf("%d",&choice);
        if(choice != 1 && choice != 2){
            errorFlag = 1;
        }
        else{
            errorFlag = 0;
        }

    } while (errorFlag);

    if(choice == 1){
        game_menu();
    }
    else{
        exit(1);
    }
    
}

void gameLogic(char player1,char player2,char board[3][3]){//game logic function that takes input from the players in order and calls the functions in the correct order
    int drawFlag=0; // a boolean variable for checking the condition is draw or not if draw break the loop
    int winFlag = 0; // a boolean variable for checking the condition is win or not if win break the loop
    int is_moved = 0; // a boolean variable for checking the user is able to move or not
    do
    {
        is_moved = move(board,player1);
        if(is_moved){
            drawFlag = checkDraw(board);
            drawBoard(board);
            if(drawFlag){
                //DRAW END FUNCTIONUNU CAGIR
                draw();
                break;
            
            }
            winFlag = checkWin(board);
            if(winFlag){
                // WINNER END FUNCTION CAGIR
                win();
                break;
            
            }
        }
        
        is_moved = move(board,player2);
        if(is_moved){
            drawBoard(board);
            drawFlag = checkDraw(board);
            if(drawFlag){
                //call the draw function
                draw();
                break;
            
            }
            winFlag = checkWin(board);
            if(winFlag){
                // WINNER END FUNCTION CAGIR
                win();
                break;
            
            }
        }
        

    } while (1);
    
}
void startGame(char player1,char player2){//a function to set the board`s values to _ 
    char board[3][3] = {{'_','_','_'},{'_','_','_'},{'_','_','_'}};
    drawBoard(board);
    gameLogic(player1,player2,board);
}

void game_menu(){
    char player1,player2; // char variables for storing  players characters
    int errorFlag =0; // error boolean
    int choice;
    printf("\n\tTIC-TAC-TOE GAME\t\n");

    do
    {//do-while loop for ensuring the user provides the correct inputs
        if(errorFlag){
            printf("\n Please give an valid input 1 or 2: ");
        }
        else{
            printf("1)NEW GAME\n2)EXIT\n");

        }
        scanf("%d",&choice);
        if(choice != 1 && choice != 2){
            errorFlag = 1;
        }
        else{
            errorFlag = 0;
        }

    } while (errorFlag);

    if(choice == 1){
        char m;
        while( (m = getchar()) != '\n')
        printf("\nPlease give the characters you wanna use.\n");
        do
        {
            if(errorFlag){
                printf("\nPlease give an valid input (X or Y):");
            }
            else{
                printf("\nPlayer 1(Give X or O): ");
                scanf("%c",&player1);
                if(player1 != 'X' && player1 != 'O'){
                    errorFlag  = 1;
                }
                else{
                    errorFlag = 0;
                }

                if(player1 = 'X'){
                    player2 = 'O';
                }
                else{
                    player2 = 'X';
                }
                
            }
        } while (errorFlag);

       
        startGame(player1,player2);
        
    }
    

}
/*END OF PART3*/




void main(){
    part1_lettercount(letters);
    part2_colors();
    game_menu();
}



