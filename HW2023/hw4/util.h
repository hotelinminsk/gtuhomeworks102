#ifndef _UTIL_H_
#define _UTIL_H_
#include <stdio.h>
#include <stdlib.h>

/* PART 1 FUNCTIONS */

int read_receipt();

int create_receipt();

void end_receipt(float last_price,int is_student);

int menu_printer(void);

float price_return(FILE *filePtr,int choose);

char* name_return(FILE *filePtr,int choose);
int new_logic();


/* PART 2 FUNCTIONS */
int ai_select();
int win_conditions(int user_choice,int ai_choice);
int game_logic();
int game_menu();

/* END */



#endif /* _UTIL_H_ */