#include "common.h"
#include "game.h"
#include <time.h>
#include <windows.h>

int note;
int jud;
long time_limit;

void game_play(){
	srand((unsigned int)time(NULL));
	time_limit = 2000;
	
	while(1){
		game_create_note();
		
		game_check_time(-1);
		while(1){
			game_get_hit();
	

			game_check_time(1);
			
			game_update_screen(0);
				

			if(game_check_time(0) > time_limit){
				jud = MISS;
				game_update_screen(1); 
				break;
			}
			else if((jud != -1)) break;			
		}
		game_update_screen(0);

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
				if(get_time_blocks() >= 7){
					jud = PERFECT;
				}
				else{
					jud = GOOD;
				}
				
				game_update_screen(1);
				
				return;
			}
			
		}		
		jud = MISS;	
		game_update_screen(1);

		return;
	}
	if(jud != -1)	
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


void game_update_screen(int mod){ //  mod == 1, forced output!
	static long t =0; 
	
	if(t == 0){
		t = clock();
	}
	
	if(clock() - t >= 40 || mod == 1){
		system("cls");
		game_print_jud();
	
		game_print_note();
		game_print_limit_time();
		
		t = 0;
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
	static int before_jud = -1;
	
	if(jud != -1){
		before_jud = jud;
	}
	
	if(before_jud == MISS)
		puts("miss!");
	else if(before_jud == GOOD){
		puts("good!");
	}
	else if(before_jud == PERFECT){
		puts("PERFECT!!!!");
	}
	
	putch('\n');	
	

}

void game_print_limit_time(){
	int i;
	int time_blocks = get_time_blocks();
		
	for(i = 0; i < time_blocks; i++){
		printf("бс"); 
	}
	putch('\n');
}

int get_time_blocks(){
	long peice_limit = time_limit/10;
	long l_time = time_limit - game_check_time(0) ;
	int time_blocks =  l_time / peice_limit;

	if(l_time % peice_limit != 0)time_blocks++;
	
	return time_blocks;
}

