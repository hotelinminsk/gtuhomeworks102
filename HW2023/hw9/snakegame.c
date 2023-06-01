#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef struct 
{
    int row;
    int col;
}point;

typedef struct{
    char type;
    int value;
}block;

typedef struct{
    point *snakeHead;
    point *snakeTail;
    int ogHeadPos[2];
    int snakelen;
    int isDied;
}snake;
int drawBoard(block ***board,snake usersnake);

block ***init_board(int width,int height){
    srand(time(NULL));
    int firstObsRow, firstObsCol, secondObsRow,secondObsCol,firstBaitRow,firstBaitCol;
    firstObsRow = (rand() % 9) +1 ;
    firstObsCol = (rand() % 9) +1 ;
    
    do
    {
        secondObsRow = (rand() % 9) +1;
        secondObsCol = (rand() % 9) +1;
    } while (firstObsRow==secondObsRow && secondObsCol == firstBaitCol);
   
    
    do
    {
        firstBaitRow = (rand() % 9) + 1;
        firstBaitCol = (rand() % 9) + 1;
    } while ((firstBaitRow==firstObsRow && firstBaitCol == firstObsCol) || (firstBaitRow==secondObsRow && firstBaitCol == secondObsCol));
    
    block ***board = (block***)malloc(height * sizeof(block**));
    
    for(int i=0;i<height;i++){
        board[i] = (block**)malloc(width * sizeof(block*));
        for(int j=0;j<width;j++){
            board[i][j] = (block*)malloc(sizeof(block));

            if((i==firstObsRow && j == firstObsCol) || (i == secondObsRow && j == secondObsCol)){
                int obstValueRand = (rand() % 10) + 1;
                board[i][j][0].value = obstValueRand;
                board[i][j][0].type = 'o';
            }
            else if(i==firstBaitRow && j == firstBaitCol){
                board[i][j][0].value = 0;
                board[i][j][0].type = 'b';

            }
            else{
                board[i][j][0].value = 0;
                board[i][j][0].type = 'e';
            }
        }
    }
    
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(board[i][j][0].type=='o'){
                int depth = board[i][j][0].value;

                realloc(board[i][j],depth*sizeof(block));
            }
        }
    }
    
    return board;
}

int move(snake *usersnake,int *movecount){
    char moveChar;
    int lastCol,lastRow;
    int errorFlag = 0;
    do
    {
        
        if(errorFlag == 1){
            printf("\nThis is not a valid input please give w-a-s-d: ");
        }else if(errorFlag == 5){
            printf("\nSnake cannot go through his own body. Give another input: ");//
        }
        else{
        printf("\nPlease give an direction to move(w-a-s-d,case sensitive): ");
        }
        scanf("%c",&moveChar);
        if(moveChar != 'w' && moveChar != 'a' && moveChar != 's' && moveChar != 'd'){
            errorFlag=1;
        }else{
            if(usersnake->snakeTail != NULL){
                int ogheadrow = usersnake->snakeHead->row;
                int ogheadcol = usersnake->snakeHead->col;
                switch (moveChar)
                {
                case 'w':
                    ogheadrow--;
                    if((usersnake->snakeTail[0].row == ogheadrow) && (usersnake->snakeTail[0].col == ogheadcol)){
                        //user trying to go through his own body
                        errorFlag = 5;
                    }else{
                        errorFlag = 0;
                    }
                    /* code */
                    break;
                case 'a':
                    ogheadcol--;
                    if((usersnake->snakeTail[0].row == ogheadrow) && (usersnake->snakeTail[0].col == ogheadcol)){
                        //user trying to go through his own body
                        errorFlag = 5;
                    }else{
                        errorFlag = 0;
                    }

                    break;
                case 's':
                    ogheadrow++;
                    if((usersnake->snakeTail[0].row == ogheadrow) && (usersnake->snakeTail[0].col == ogheadcol)){
                        //user trying to go through his own body
                        errorFlag = 5;
                    }else{
                        errorFlag = 0;
                    }
                    break;
                case 'd':
                    ogheadcol++;
                    if((usersnake->snakeTail[0].row == ogheadrow) && (usersnake->snakeTail[0].col == ogheadcol)){
                        //user trying to go through his own body
                        errorFlag = 5;
                    }else{
                        errorFlag = 0;
                    }
                    break;
                default:
                    break;
                }
                while(getchar() != '\n');
            }
            else{
                while(getchar() != '\n');
                errorFlag=0;

            }
        }

    } while (errorFlag);
    
    switch (moveChar)
    {
    case 'w':
        /* code */
        lastRow = usersnake->snakeHead->row;
        lastCol = usersnake->snakeHead->col;
        usersnake->ogHeadPos[0] = lastRow;
        usersnake->ogHeadPos[1] = lastCol;
        usersnake->snakeHead->row--;
        *movecount = *movecount + 1;
       
        
        break;
    case 'a':
        lastRow = usersnake->snakeHead->row;
        lastCol = usersnake->snakeHead->col;
        usersnake->ogHeadPos[0] = lastRow;
        usersnake->ogHeadPos[1] = lastCol;
        usersnake->snakeHead->col--;
        *movecount = *movecount + 1;

        

        break;
    case 'd':
        lastRow = usersnake->snakeHead->row;
        lastCol = usersnake->snakeHead->col;
        usersnake->ogHeadPos[0] = lastRow;
        usersnake->ogHeadPos[1] = lastCol;
        usersnake->snakeHead->col++;
        *movecount = *movecount + 1;

        break;
    case 's':
        lastRow = usersnake->snakeHead->row;
        lastCol = usersnake->snakeHead->col;
        usersnake->ogHeadPos[0] = lastRow;
        usersnake->ogHeadPos[1] = lastCol;
        usersnake->snakeHead->row++;
        *movecount = *movecount + 1;

        break;
    default:
        break;
    }

    return 1; 
}
/*If  the  game  is  not  over,  the  play()  function  calls  the  update()  function.  
In  this  function,  the program updates the coordinates of the snake's body, considering whether the snake ate abait in the last move or not.
 Then, the function updates the bait and obstacles on the board. If the snake ate a bait in  the  last  move,  the  length  of  the  snake  is  increased 
  by one  block. Otherwise, the  rest  of  the  body  is shifted to keep the body and headconnected.
   There can be only one bait at a time on the board. This function  also  updates  the  obstacles  every 5 moves. 
    The  obstacles  appear  randomly on  the  board,  and there can be a maximum of 3 obstacles at a time. Additionally, 
    the height of obstaclescan be increased by adding new obstacle blocks on top of existing ones.If the snake encounters an obstacle 
    that is shorter than  its  body, 
 it  can  capture  the  block  by  destroying the  obstacle. This  is  done  by  deleting the  nested*/

int update(block ***board, snake *usersnake, int *movecount) {
    srand(time(NULL));
    int obstacle_update = 0;
    int obstacle_count = 0;

    int baitCount = 0;
    if ((*movecount) % 5 == 0) {
        obstacle_update = 1;
    } else {
        obstacle_update = 0;
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j][0].type == 'b') {
                baitCount++;
            }
        }
    }

    if (board[usersnake->snakeHead->row][usersnake->snakeHead->col][0].type == 'b') {
        baitCount -= 1;
        if (usersnake->snakelen == 0) {
            usersnake->snakeTail = (point *)malloc(sizeof(point));
            usersnake->snakeTail->row = usersnake->ogHeadPos[0];
            usersnake->snakeTail->col = usersnake->ogHeadPos[1];
            usersnake->snakelen++;
        } else {

            point *new_snakeTail = (point *)realloc(usersnake->snakeTail, (usersnake->snakelen + 1) * sizeof(point));
            if (new_snakeTail != NULL) {
                usersnake->snakeTail = new_snakeTail;
                usersnake->snakelen++;
            }
        }
        
        board[usersnake->snakeHead->row][usersnake->snakeHead->col][0].type = 'e';
        block *new_block = (block *)realloc(board[usersnake->snakeHead->row][usersnake->snakeHead->col], sizeof(block));
        if (new_block != NULL) {
            board[usersnake->snakeHead->row][usersnake->snakeHead->col] = new_block;
            
        }
    }

    if (usersnake->snakeTail != NULL) {
        for (int i = usersnake->snakelen-1; i >= 0; i--) {
            if (i == 0) {
                usersnake->snakeTail[i].row = usersnake->ogHeadPos[0];
                usersnake->snakeTail[i].col = usersnake->ogHeadPos[1];
            } else {
                usersnake->snakeTail[i].row = usersnake->snakeTail[i - 1].row;
                usersnake->snakeTail[i].col = usersnake->snakeTail[i - 1].col;
            }
        }
    }

    int obstPositions[3][2];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j][0].type == 'o') {
                obstPositions[obstacle_count][0] = i;
                obstPositions[obstacle_count][1] = j;
                obstacle_count++;
            }
        }
    }

    

    if (obstacle_update) {
        if (obstacle_count < 3) {
            int randX, randY;
            int isOccupied1 = 0;
            int isOccupied2 = 0;

            for (int m = 0; m < 3 - obstacle_count; m++) {
                do {
                    isOccupied1 = 0;
                    isOccupied2 = 0;
                    randX = rand() % 9;
                    randY = rand() % 9;
                    for (int i = 0; i < usersnake->snakelen; i++) {
                        if ((usersnake->snakeTail[i].row == randY) && (usersnake->snakeTail[i].col == randX)) {
                            isOccupied1 = 1;
                            break;
                        } else {
                            isOccupied1 = 0;
                        }
                    }
                    for (int j = 0; j < obstacle_count; j++) {
                        if ((obstPositions[j][0] == randY) && (obstPositions[j][1] == randX)) {
                            isOccupied2 = 1;
                            break;
                        } else {
                            isOccupied2 = 0;
                        }
                    }
                } while (isOccupied1 || isOccupied2);
                
                int randValue = rand() % 9 + 1;
                board[randY][randX][0].value = randValue;
                board[randY][randX][0].type = 'o';
                
                block *new_block = (block *)realloc(board[randY][randX], randValue * sizeof(block));
                if (new_block != NULL) {
                    board[randY][randX] = new_block;
                }
                
                obstacle_count++;
                obstPositions[2][0] = randY;
                obstPositions[2][1] = randX;
            }
        } else if (obstacle_count == 3) {
            int randObs = rand() % 3;
            int valueEx = board[obstPositions[randObs][0]][obstPositions[randObs][1]][0].value;
            
            block *new_block = (block *)realloc(board[obstPositions[randObs][0]][obstPositions[randObs][1]], (valueEx + 1) * sizeof(block));
            if (new_block != NULL) {
                board[obstPositions[randObs][0]][obstPositions[randObs][1]] = new_block;
            }
            
            board[obstPositions[randObs][0]][obstPositions[randObs][1]][0].value = valueEx + 1;
        } else {
            ;
        }
    }

    if(baitCount==0){
            int isOccipied1 = 0;
            int isOccipied2 = 0;
            int randX,randY;
            do
            {   
                isOccipied1 = 0;
                isOccipied2 = 0;
                randY = rand() % 9;
                randX = rand() % 9;

                for(int i=0;i<obstacle_count;i++){
                    if((obstPositions[i][0] ==  randY) && (obstPositions[i][1] == randX)){
                        isOccipied1 = 1;
                        break;
                    }else{
                        isOccipied1 = 0;
                    }
                }
                for(int j=0;j<usersnake->snakelen;j++){
                    if((usersnake->snakeTail[j].row==randY) && (usersnake->snakeTail[j].col == randX)){
                        isOccipied2 = 1;
                    }else{
                        isOccipied2=0;
                    }
                }

            } while (isOccipied1 || isOccipied2);


            board[randY][randX][0].type = 'b';
            board[randY][randX][0].value = 0;

            realloc(board[randY][randX],sizeof(block));
        }

    // Rest of the code...
}


    
 

int check_status(block ***board,snake *usersnake){
    /*
    1.Does the head of the snake hit its own body?
    2.Does the snake collide with the wall?
    3.Does the snake encounter an obstacle that has x number of blocks, where x is greater than the length of the snake?
    */

   if(usersnake->snakelen > 15){
    //WIN
    return 35;
   }

   /*check 1.Does the head of the snake hit its own body?*/
    int checker = 0;
    if(usersnake->snakeTail != NULL){
        for(int i=0; i<usersnake->snakelen;i++){
            if((usersnake->snakeTail[i].row == usersnake->snakeHead->row) && (usersnake->snakeTail[i].col == usersnake->snakeHead->col)){
                //IT COLLIDES WITH HIS BODY AT SOME TIME SO WE SHOULD END THE GAME,
                checker = 1;
                break;
                
            }else{
                checker = 0;
            }
        }
        if(checker){
            return 101;
            
        }else{
            
        }
    }
    checker = 0;
    /*CHECK 2Does the snake collide with the wall? */
    if ((usersnake->snakeHead->row > 9 || usersnake->snakeHead->row < 0) || (usersnake->snakeHead->col<0 || usersnake->snakeHead->col>9))
    {
        return 99;
        
    }
    
    /*CHECK 3Does the snake encounter an obstacle that has x number of blocks, where x is greater than the length of the snake? */
    int snakerow = usersnake->snakeHead->row;
    int snakecol = usersnake->snakeHead->col;
    if(board[snakerow][snakecol][0].type=='o'){
        
        if(usersnake->snakelen > board[snakerow][snakecol][0].value){
            ////buradayım
            board[snakerow][snakecol][0].type = 'e';
            board[snakerow][snakecol][0].value = 0;

            
        }else{
            return 100;
            
        }
    }

    //collideWAll return 99
    //obstaclelose return 100
    //hititsownbody return 101
    //no problem 0

    return 0;
    
}



void play(block ***board){
    /*CREATING THE SNAKE FIRST TIME*/
    int movecount =0;
    snake *usersnake = (snake*)malloc(sizeof(snake));
    usersnake->snakeHead = (point*)malloc(sizeof(point));
    usersnake->snakeHead->col = 0;
    usersnake->snakeHead->row = 0;
    usersnake->isDied = 0;
    usersnake->snakelen = 0;
    usersnake->snakeTail = NULL;

    int gamestatus;
    do
    {
        drawBoard(board,*usersnake);
        move(usersnake,&movecount);
        gamestatus = check_status(board,usersnake);
        if(gamestatus==99){
            puts("The snake has collided with the wall, game ends.");
        }else if(gamestatus==100){
            puts("The snake hit an obstacle bigger than itself, game ends.");
        }else if(gamestatus==101){
            puts("The snake has hit itself, game ends");
        }
        else if(gamestatus==35){
            puts("The snake is longer now! Game has won.");
        }
        else{
            //update();
            update(board,usersnake,&movecount);
        }


    } while (gamestatus==0);
    


}



/*move():This function takes the snake as input and applies the next move obtained from the user.,
 The next move should be obtained from the userwithin this function, and the head of the snake should be set  to  its  next  position  based 
  on  the  given  direction.  The  snake  can  turn  in  one  of  the  four  directions except the direction that goes through its own body. 
  If the user tries to make such a move, it should be ignored.*/


/*play():This is the main function for game play. 
It takes the initialized board as input and does not return anything. 
The function initializes the snake with a lengthof 1 block at the top-left of the board. 
It asks the user  for a new move  until the game  is over and draws the board using the draw_board()  function before each move. 
After each move, the current state of the game is checked using the check_status() function.
If  the  game  is  not  over  in  the  current  state,  then  the  board  and  snake  are  updated  in  the update() function.*/




int drawBoard(block ***board, snake usersnake) {
    printf("\n");
    for (int i = 0; i < 10 * 2 + 2; i++) {
        printf("-");
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (j == 0) {
                printf("|");
            }
            if (usersnake.snakeHead->col == j && usersnake.snakeHead->row == i) {
                if (usersnake.snakeHead != NULL) {
                    printf("%-2s", "O");
                }
            } else if (usersnake.snakeTail != NULL) {
                int found = 0;
                for (int k = 0; k < usersnake.snakelen; k++) {
                    if (usersnake.snakeTail[k].row == i && usersnake.snakeTail[k].col == j) {
                        printf("%-2s", "X");
                        found = 1;
                        break;
                    }
                }
                if (found == 0) {
                    if (board[i][j][0].type == 'o') {
                        printf("%-2d", board[i][j][0].value);
                    } else if (board[i][j][0].type == 'b') {
                        printf("%-2s", ".");
                    } else {
                        printf("%-2s", " ");
                    }
                }
            } else {
                if (board[i][j][0].type == 'o') {
                    printf("%-2d", board[i][j][0].value);
                } else if (board[i][j][0].type == 'b') {
                    printf("%-2s", ".");
                } else {
                    printf("%-2s", " ");
                }
            }
            if (j == 9) {
                printf("|");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < 10 * 2 + 2; i++) {
        printf("-");
    }
    printf("\n");
}



void main(){
block ***board = init_board(10,10);
play(board);
}