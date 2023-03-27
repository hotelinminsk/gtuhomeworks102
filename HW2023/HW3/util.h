#ifndef _UTIL_H_
#define _UTIL_H_


void game_help();
int board(int boardRow,int boardCol,int *charX,int *charY,int *doorX,int *doorY);
int move(int *charX,int *charY,int boardX,int boardY,int *doorX,int *doorY);
int winCheck(int *charX,int* charY,int *doorX,int *doorY);
int game_menu();
int game_logic();

#endif /*_UTIL_H_*/