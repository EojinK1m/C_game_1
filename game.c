#include "common.h"
#include "game.h"
#include <time.h>

void game_play(){
	srand((unsigned int)time(NULL));
	char note;
	char jud;
	
	while(1){	
		note = game_note();
		jud = game_get_hit(note);
		game_check_jud(jud);
		
		
	}
	
}

char game_note(){
	char note = rand()%4;
	
	switch(note){
		case 0:
			fputs("UP\n", stdout);
			return UP;
		case 1:
			fputs("DOWN\n", stdout);
			return DOWN;
		case 2:
			fputs("RIGHT\n", stdout);
			return RIGHT;
		case 3:
			fputs("LEFT\n", stdout);
			return LEFT;
	}
}

char game_get_hit(char note){
	char user_hit;
	
	user_hit = getch();
	
	if(user_hit == -32){
		user_hit = getch();
		
		if(user_hit == note){
			return 1;
		}
	}
	
	return 0;
}

void game_check_jud(char jud){
	if(jud == 0)
		puts("miss!");
	else
		puts("good!");
	putch('\n');	
}



		


	
	
