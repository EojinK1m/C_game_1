#include "common.h"
#include "game.h"
#include <time.h>

int note;
int jud;
long time_limit;

/* 

*/


void game_play(){
	srand((unsigned int)time(NULL));
	time_limit = 700;
	
	while(1){	
		game_create_note();
		
		game_check_time(-1);
		while(1){
			game_get_hit();

			game_check_time(1);
			
			game_update_screen();

					
			if(game_check_time(0) > time_limit){
				jud = MISS;
				break;
			}
			else if((jud != -1)) break;			
		}
		game_update_screen();

	}
}

void game_create_note(){
	switch(rand()%4){
		case 0:
			note = UP;
			break;
		case 1:
			note = DOWN;
			break;
		case 2:
			note = RIGHT;
			break;
		case 3:
			note = LEFT;
			break;
	}
}

void game_get_hit(){ // -
	char user_hit;
	
	if(kbhit()!=0){
		user_hit = getch();
		
		if(user_hit == -32){
			user_hit = getch();
			
			if(user_hit == note){
				jud = GOOD;
			}
		}
		else{
			jud = MISS;
		}
		
		return;
	}
	jud = -1;	
}

long game_check_time(int mode){ //mode.//      -1 = start//      -1 = end//   0 = return_time 
	static long start, end;
	
	if(mode == -1){
		start = clock();
	}
	else if(mode == 1){
		end = clock();
	}
	else if(mode == 0){
		return end-start;
	}
}

void game_print_note(){	
		switch(note){		
			case UP:
				puts("UP");
				break;
			case DOWN:
				puts("DOWN");
				break;
			case RIGHT:
				puts("RIGHT");
				break;
			case LEFT:
				puts("LEFT");
				break;
	}
}


void game_print_jud(){ //name change 
	if(jud == MISS)
		puts("miss!");
	else if(jud == GOOD)
		puts("good!");
	putch('\n');	
}


void game_update_screen(){
	system("cls");
	game_print_jud();
	game_print_note();
	game_print_limit_time();
	
}

void game_print_limit_time(){
	int i;
	long peice_limit = time_limit/10;
	long l_time = time_limit - game_check_time(0) ;
	int time_block =  l_time / peice_limit;

	if(l_time % peice_limit != 0)time_block++;
	
	for(i = 0; i < time_block; i++){
		putch('бс');
	}
	putch('\n');
}


	
	
		
		
	
	

		


	

