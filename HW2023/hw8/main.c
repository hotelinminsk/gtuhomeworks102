#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
typedef struct{  /*the DEFINING OF BOARD STRUCT*/
    int is_win;
    int  board[3][3];
}board;
//menu 
/* 
    1-play game as a user
    2- finish the game with pc
    3- show the best score
    4- exit


*/
int isBoardWin(board *uBoard,int *movecount);

int is_bestScore(int moveCount){/*FUNCTION TO CHECK IF GIVEN MOVECOUNT IS BEST SCORE OR NOT
IF BEST SCORE PRINT IT IN THE BEST_SCORE.TXT*/
    //(Formula of the score= 1000 –10 * number of moves)
    int lastScore = 0;
    int negativeMoves = -10 * moveCount;
    int score = 1000 + negativeMoves;
    
    FILE *fp = NULL;
    fp = fopen("best_score.txt","r");
    fscanf(fp,"%d",&lastScore);
    fclose(fp);
    fp = fopen("best_score.txt","w");
    if(lastScore==0){
        //it is best score
        fprintf(fp,"%d\n",score);
        fclose(fp);
        return 1;

    }
    else if(score>lastScore){
        fprintf(fp,"%d\n",score);
        fclose(fp);
        return 1;
    }else{
        fclose(fp);
        return 0;
    }

}

void boardtotxt(board *oW){
    FILE *bFile = fopen("board.txt","a");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(oW->board[i][j] == 0){
                fprintf(bFile,"_ ");
                
            }else{
                fprintf(bFile,"%d ",oW->board[i][j]);
                
            }
        }                

        fprintf(bFile,"\n");
    }

    fprintf(bFile,"\n");

    fclose(bFile);
}

void boardPrinter(board *oW){/*A FUNCTION TO PRINT OUT BOARD TO TERMINAL AND PRINT IT IN BOARD.TXT AS WELL */
   
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(oW->board[i][j] == 0){
                printf("_ ");
            }else{
                printf("%d ",oW->board[i][j]);
            }
        }                
        printf("\n");

    }



}

int is_MoveLegal(board *uBoard,int go_pos[2]){ // FUNCTION TO CHECK IF MOVE IS LEGAL OR NOT 
/*TAKING BOARD AND A INTEGER ARRAY AS AN ARGUMENTS AND CHECKS IF GIVEN POSITION VALUES ON BOARD IS 0 OR NOT*/
    if((go_pos[0]>2 || go_pos[0]<0) || (go_pos[1]>2 || go_pos[1]<0)){
        return 0;
        //move is not legal
    }
    else if(uBoard->board[go_pos[0]][go_pos[1]] == 0){
        
        //move is legal
        return 1;
    }
    else{
        return 0;
        //move is not legal
    }
}


int isBoardWin(board *uBoard,int *movecount){//A FUNCTION TO CHECK THE SENDED BOARD IS WIN OR NOT
    int row=0;
    int col=0;
    int newRow = 0;
    int is_win = 0;
    for(int i=1;i<9;i++){//WE START FROM 1 AND GO TO 8 
        if(uBoard->board[row][col++] == i){
            is_win=1;
        }else{
            is_win = 0;
            break;
        }
        if(newRow == 0 &&(i==3 || i == 6)){ // IF I VALUES 3 AND 6 WE JUMP OVER 1 ROW, AND SET THE ROW +1 AND COL TO 0
            newRow = 1;
        }
        if(newRow==1){
            row++;
            col = 0;
            newRow = 0;
        } 
    }

    uBoard->is_win = is_win;
    return is_win;


}

int usermove(board *uBoard,int *movecount){ /* USER MOVE ALGORITHM*/
    char input[4];
    int errorFlag=0;
    do
    {
        if(errorFlag){
            printf("%s is an illegal move! Make a legal move!\n",input);
        }else{
            puts("Please give a move");
        }
        printf(">");
        scanf("%s",input);
        int is_pos =0;
        int position; 
        char wMove;
        sscanf(input,"%d-%c%*[^\n]\n",&position,&wMove);//FOR TAKING INPUTS AS LIKE 4-L WE HAVE TO PARSE THE STRING 
        int positionArray[2];
        int ogPos[2];
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(position == uBoard->board[i][j]){//WE FIND THE STONE USER WANNA PLAY
                    positionArray[0] = i; //PUTTING THE X AND Y VALUES OF STONE USER CHOOSED IN TO POSITION ARRAY
                    positionArray[1] = j;
                    ogPos[0] = i;
                    ogPos[1] = j;
                    break;
                }
            }
        }

        switch (wMove) //WITH MOVE WE CHANGING THE VALUES OF POSITION ARRAYS X OR Y VALUE
        {
        case 'L':
            /* code */
            positionArray[1]--;
            break;
        case 'R':
            positionArray[1]++;
            break;
        case 'U':
            positionArray[0]--;
            break;
        case 'D':
            positionArray[0]++;
            break;
        default:
            errorFlag = 1;
            break;
        }


        if(is_MoveLegal(uBoard,positionArray)){ // CHECKING THE MOVE LEGAL OR NOT
            // position array is now _ position and ogPos is our number we wanna change the position
            puts("Move is legal");
            *movecount = *movecount + 1;
            int num = uBoard->board[ogPos[0]][ogPos[1]];
            uBoard->board[positionArray[0]][positionArray[1]] = num;
            uBoard->board[ogPos[0]][ogPos[1]] = 0;            
            errorFlag= 0;
        }else{
            puts("Move is not legal");

            errorFlag = 1;
        };
        

    } while (errorFlag);
    
}


int menu(){ /*MENU FUNCTION TO RETURN USERS CHOICE*/
    int choice =0;
    int errorFlag = 0;
    int movecount = 0;
    int lastStone = -1;
    int lastMove = -1;
    board newboard;
    newboard.is_win = 0;
    
    int seed = time(NULL);

    do /*A DO WHILE LOOP FOR TAKING ONLY VALID INPUTS*/
    {   
        if(errorFlag){
            puts("Please give valid input!");
        }else{
            puts("Please select an option: ");
        }
        puts("1. Play game as a user\n2. Finish the game with PC\n3. Show the best score\n4. Exit");
        printf(">");
        scanf("%d",&choice);
        if(choice != 1 && choice != 2 && choice != 3 && choice != 4){
            errorFlag = 1;
        }
    } while (errorFlag);
    
    return choice;

    
}

int *stonesCloseZero(board *uBoard,int *elementCount){ /* FUNCTION TO RETURN STONES WHICH ARE CLOSE TO ZERO*/
    int zerosPosition[2];
    int flag=0;
    int *closeToZero = NULL;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(uBoard->board[i][j] == 0){
                zerosPosition[0] = i;
                zerosPosition[1] = j;
                flag = 1;
                break;
            }
        }
        if(flag){
            break;
        }
    }
    int zerorow = zerosPosition[0];
    int zerocol = zerosPosition[1];
    if(zerorow == 0){
        switch (zerocol)
        {
        case 0:
            closeToZero = (int*)malloc(2 * sizeof(int));
            // col +1  row same 
            // col same row +1 
            closeToZero[0] = uBoard->board[zerorow][zerocol+1];
            closeToZero[1] = uBoard->board[zerorow+1][zerocol];
            *elementCount = 2;
            break;
        case 1:
            closeToZero = (int*)malloc(3*sizeof(int));
            //col same row+1
            //row same col - 1 
            // row same col +1
            closeToZero[0] = uBoard->board[zerorow+1][zerocol];
            closeToZero[1] = uBoard->board[zerorow][zerocol-1];
            closeToZero[2] = uBoard->board[zerorow][zerocol+1];
            *elementCount = 3;
            break;
        case 2:
            closeToZero = (int*)malloc(2 * sizeof(int));

            //row same col -1
            //col same row +1
            closeToZero[0] = uBoard->board[zerorow][zerocol-1];
            closeToZero[1] = uBoard->board[zerorow+1][zerocol];
            *elementCount = 2;
            break;
        default:
            break;
        }
    }
    else if(zerorow == 1){
        switch (zerocol)                                                                      
        {
        case 0:
            closeToZero = (int*)malloc(3*sizeof(int));

            //col same row-1
            //col same row +1 
            //row same col+1
            closeToZero[0] = uBoard->board[zerorow-1][zerocol];
            closeToZero[1] = uBoard->board[zerorow+1][zerocol];
            closeToZero[2] = uBoard->board[zerorow][zerocol+1];
            *elementCount = 3;
            break;
        case 1:
            closeToZero = (int*)malloc(4*sizeof(int));

            //col same row +1 
            //col same row -1
            //row same col +1
            //row same col - 1
            closeToZero[0] = uBoard->board[zerorow+1][zerocol];
            closeToZero[1] = uBoard->board[zerorow-1][zerocol];
            closeToZero[2] = uBoard->board[zerorow][zerocol+1];
            closeToZero[3] = uBoard->board[zerorow][zerocol-1];
            *elementCount = 4;
            break;
        case 2:
            closeToZero = (int*)malloc(3*sizeof(int));

            //row same col -1
            //col same row - 1
            //col same row +1
            closeToZero[0] = uBoard->board[zerorow][zerocol-1];
            closeToZero[1] = uBoard->board[zerorow-1][zerocol];
            closeToZero[2] = uBoard->board[zerorow+1][zerocol];
            *elementCount = 3;
            break;
        default:
            break;
        }
    }else if(zerorow == 2){
        switch (zerocol)
        {
        case 0:
            closeToZero = (int*)malloc(2 * sizeof(int));

            //col same row-1
            //row same col +1
            closeToZero[0] = uBoard->board[zerorow-1][zerocol];
            closeToZero[1] = uBoard->board[zerorow][zerocol+1];
            *elementCount = 2;
            break;
        case 1:
            closeToZero = (int*)malloc(3*sizeof(int));
            //col same row-1
            //row same col+1
            //row same col-1
            closeToZero[0] = uBoard->board[zerorow-1][zerocol];
            closeToZero[1] = uBoard->board[zerorow][zerocol+1];
            closeToZero[2] = uBoard->board[zerorow][zerocol-1];
            *elementCount = 3;
            break;
        case 2:
            closeToZero = (int*)malloc(2 * sizeof(int));

            //row same col-1
            //col same row -1
            closeToZero[0] = uBoard->board[zerorow][zerocol-1];
            closeToZero[1] = uBoard->board[zerorow-1][zerocol];
            *elementCount = 2;
            break;
        default:
            break;
        }
    }
    return closeToZero;
}


int randomMoveAi(board *uBoard,int *movecount,int *lastStone,int *lastMove){ //RANDOM MOVE FUNCTION
    //boardPrinter(uBoard);
    if(isBoardWin(uBoard,movecount)){   /*TAKING THE LAST PLAYED STONE AND LAST MOVE TO NOT LETTING PROGRAM TO PLAY SAME MOVES AGAIN AND AGAIN*/
        boardPrinter(uBoard);           /*THERE THE SAME MOVES IS LIKE  2-R AND 2-L  I DONT LET IT DO THIS*/
        puts("Computer has won the game!");
        printf("With %d moves.",*movecount);
        return 1;
    }
    int *stones = NULL;
    int elementCount = 0;
    stones = stonesCloseZero(uBoard,&elementCount); /*CALLING THE FUNCTION TO RETURN AN ARRAY OF STONES WHICH ARE CLOSE TO 0 */
    int moves[4] = {1,2,3,4}; /* POSSIBLE MOVES */
    int firststonePos[2];
    int gostonePos[2];
    int randomMove;
    int randomStone;
    char moveChar;

    do
    {
        randomStone = stones[rand() % elementCount];

//randomStone == *lastStone
    } while (randomStone == *lastStone);
    int flag=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(uBoard->board[i][j] == randomStone){
                firststonePos[0] = i;
                firststonePos[1] = j;
                flag = 1;
                break;
            }
        }

        if(flag){
            break;
        }
    }
    int errorFlag = 0;
    do
    {   randomMove = moves[rand() % 4];
        switch (randomMove)
        {
        case 1: //U
        gostonePos[0] = firststonePos[0] -1;
        gostonePos[1] = firststonePos[1];
        moveChar = 'U'; 
        break;
        case 2://D
        gostonePos[0] = firststonePos[0] +1;
        gostonePos[1] = firststonePos[1];
        moveChar = 'D';
        break;
        case 3://R
        gostonePos[1] = firststonePos[1] +1;
        gostonePos[0] = firststonePos[0];
        moveChar = 'R';
        break;
        case 4://L
        gostonePos[1] = firststonePos[1] - 1;
        gostonePos[0] = firststonePos[0];
        moveChar = 'L';
        break; 
        default:
            break;
        }

        if(uBoard->board[gostonePos[0]][gostonePos[1]] != 0){
            errorFlag = 1;
        }else{
            errorFlag = 0;
        }
        //|| ( randomStone == *lastStone && randomMove == *lastMove)
    } while (errorFlag);
    
    if(is_MoveLegal(uBoard,gostonePos)){
        
        if(randomMove == 1){
            *lastMove = 2; 
        }else if(randomMove==2){
            *lastMove = 1;
        }else if(randomMove == 3){
            *lastMove = 4;
        }else if(randomMove == 4){
            *lastMove = 3;
        }
        
        *movecount = *movecount +1;
        boardPrinter(uBoard);
        *lastStone = randomStone;
        printf("\nComputer made the move %d-%c.\n",randomStone,moveChar);
        printf("\nMOVECOUNT = %d\n",*movecount);
        uBoard->board[firststonePos[0]][firststonePos[1]] = 0;
        uBoard->board[gostonePos[0]][gostonePos[1]] = randomStone;
    }
    free(stones);
    if(isBoardWin(uBoard,movecount)){
        boardPrinter(uBoard);
        puts("Computer has won the game!");
        printf("Move Count = %d",*movecount);
        return 1;
    }else{
     randomMoveAi(uBoard,movecount,lastStone,lastMove);
    }
}

int count_inv(int arr[3][3]){ //THE FUNCTION FOR COUNTING INVERSIONS OF CREATED BOARD TO CHECK IF IT IS SOLVABLE OR NOT
    int inversions = 0;
    int copyArray[9];
    int indexCount=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            copyArray[indexCount++] = arr[i][j];
        }
    }

    for(int i=0;i<9;i++){
        for(int j=i+1;j<9;j++){
            if(copyArray[i] > copyArray[j] && copyArray[i] != 0 && copyArray[j] != 0){
                inversions++;
            }
        }
    }
    return inversions;
}
int boardCreator(int board[3][3]){
    srand(time(NULL));
    int numbers[9] = {1,2,3,4,5,6,7,8,0}; //NOW IT IS NOT USED BUT IN THE FIRST ALGORITHM I WAS USING THIS ARRAY
    int firstRownums[3] = {1,2,3};
    int secondRownums[3] = {4,5,6};
    int thirdRownums[3] = {7,8,0};


    for (int i = 0; i < 3; i++) {  //FIRST I MAKE ALL THE ELEMENTS OF BOARD ARRAY -1 TO NOT LETTING ALGORITHM PUT VALUES ON ALLOCATED POSITIONS
        for (int j = 0; j < 3; j++) {
            board[i][j] = -1;
        }
    }

    int indexCount = 0;
    int lastNum;
    int num;
    for(int i=0;i<3;i++){ /*WHEN I CREATE THE BOARD FULLY RANDOM WHICH I DO AT THE BEGGINING, THE RANDOM MOVE FUNCTION COULDNT SOLVE IT IN 300K MOVES, SO I TRIED TO MAKE*/
        if(i==0){           /*BOARD MORE SOLVABLE WITH THIS VERSION*/
            for(int j=0;j<3;j++){
                if(board[i][j] == -1){
                    do
                    {
                        int pos = rand() % 3;
                        num = firstRownums[pos];  /*AFTER THAT I SIMPLY CHOOSE FROM ROWS NUMBER RANDOMLY AND PUT THEM IN BOARD*/
                        firstRownums[pos] = -1;
                    } while (num == - 1);                    
                    lastNum = num;
                    board[i][j] = num;

                }
            }
        }
        if(i==1){
            for(int j=0;j<3;j++){
                if(board[i][j] == -1){
                    do
                    {
                        int pos = rand() % 3;
                        num = secondRownums[pos];
                        secondRownums[pos] = -1;
                    } while (num == - 1);                    
                    lastNum = num;
                    board[i][j] = num;

                }
            }
        }
         if(i==2){
            for(int j=0;j<3;j++){
                if(board[i][j] == -1){
                    do
                    {
                        int pos = rand() % 3;
                        num = thirdRownums[pos];
                        thirdRownums[pos] = -1;
                    } while (num == - 1);                    
                    lastNum = num;
                    board[i][j] = num;

                }
            }
        }
        
    }
    
    /*HERE IS THE FULLY RANDOM BOARD BULDING ALGORITHM*/
    /*
    while (indexCount < 9) {
        int randCol = rand() % 3;
        int randRow = rand() % 3;
        if (board[randRow][randCol] == -1) {
            board[randRow][randCol] = numbers[indexCount++];
        }
    }
    int inversions = count_inv(board);
    while(inversions % 2 != 0){
        indexCount = 0;
        for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = -1;
        }
        }
        while (indexCount<9)
        {
            int randcol = rand() % 3;
            int randrow = rand() % 3;
            if(board[randrow][randcol] == -1){
                board[randrow][randcol] = numbers[indexCount++];
            }
        }
        
        inversions = count_inv(board);
    }
    */
}

void main(){
    int menuChoice;
    int bestScore;
    int movecount = 0;
    int lastStone = -1;
    int lastMove = -1;
    board newboard;
    boardCreator(newboard.board);


    do
    {
         menuChoice = menu();
    //play game as user
        //createboard
        //call game ai
    //2ai
    //3 show best score
    //4exit


    /*I ONLY USE BOARDTOTXT ON USERMOVES BECAUSE COMPUTER MOVES MORE THAN 100K AND IT IS NOT SO READABLE*/
    if(menuChoice==1){
        //boardcreator
        movecount = 0;
        boardPrinter(&newboard);    
        do
        {
            usermove(&newboard,&movecount);
            boardPrinter(&newboard);
            boardtotxt(&newboard);
            isBoardWin(&newboard,&movecount);
        } while (newboard.is_win == 0);
        
        puts("Board is win!");
        int bested = is_bestScore(movecount);
        int lastScore = 1000 - movecount *10;
        if(bested){
            puts("------------------------");
            puts("Thats a new best score!");
            printf("Your score is = %d\n",lastScore);
            printf("Your move count is = %d\n",movecount);
            puts("------------------------");

        }else{
            puts("------------------------");
            printf("You have won the game!\n");
            printf("With total of %d moves!\n",movecount);
            printf("\nYour score is : %d",lastScore);
            puts("------------------------");

        }

    }else if(menuChoice==2){
        movecount = 0;
        
        randomMoveAi(&newboard,&movecount,&lastStone,&lastMove);
    }else if(menuChoice==3){
        //show best score
        FILE *fp = fopen("best_score.txt","r");
        fscanf(fp,"%d",&bestScore);

        puts("--------------------------");
        printf("The best score is %d right now.\n",bestScore);
        puts("--------------------------");
        
    }else{
        exit(1);
    }
    } while (1);
    
}