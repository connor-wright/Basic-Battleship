/*
Program: PA6 The game of battleship
Programer: Connor Wright
Class: CPTS 121 Lecture 01 Lab 04 Spring 2016
Date: 3/23/16
Description: A program that will play the game of battleship with a computer

Changelog:
3/23/16
	Created and tested
		void greeting()
		void initialize_board(char board[][10],int rows,int columns)
		void print_board(char board[][10], int rows, int columns)
		int check_overlap_ship(char board[][10], int row, int column)
		int check_valid_ship_placement(char board[][10], int row, int column, direction d,ship s)
		void place_ships_player(char board[][10]) whoo that one was fun
		void get_chords(int *x, int *y)
		shot check_hit_or_miss(int x, int y, char board_defense[][10], ship *Ship)
		shot fire_player(char board_attack[][10], char board_defense[][10], char board_defense_inital[][10], int x, int y, ship *Ship) not complete
		void copy_board(char board[][10], char board_copy[][10]);
	Defined
		ROW to 20
		COL to 10
	typedefed
		ships for each ship and a null
		directions to N,E,S,W in that order because clockwise direction
		hit miss
	Added
		char board1[20][10] = { '\0' }
		char board2[20][10] = { '\0' }
		ship Ship = null;
		shot Shot = miss;
		int x = 0;
		int y = 0;
		char board1_inital[20][10] = { '\0' }
		char board2_inital[20][10] = { '\0' }
3/27/16
	Added struct 
		typedef struct ship {
			int size;
			int sunk;
		}Ship;
4/1/16
	Just going to remake everything to work better with structs it will be messy
	Modified
		typedef struct Ship {
			int size;
			int sunk;
			int hit;
			char name[25];
			char caracter;
		}ship;
4/2/16
	Gave up on change log need to plan it out better next time
4/3/16
	Finnished!
		
*/

#include "header.h"


int main() {

	//player board 
	char board_player[20][10] = { '\0' };
	//player 2s board and inital positions
	char board_AI[20][10] = { '\0' };
	//choridnate variables
	int x = 0;
	int y = 0;
	//player=0 AI = 1
	int player_turn = 0;
	int winner = 0;
	int choice = 0;
	//stats for the player and AI
	stats player = { 0,0,0 };
	stats AI = { 0,0,0 };
	//records wether or not a shot was a hit or miss
	shot Shot = miss;
	//players ships in an array  (so neat and tidy) 
	ship fleet_player[5] = { { 5,0,0,"Carrier",'C' } ,{ 4,0,0,"Battleship",'B' } ,{ 3,0,0 ,"Cruiser",'R' } ,{ 3,0,0,"Submarine",'S' },{ 2,0,0,"Destroyer",'D' } };
	//same for the AI
	ship fleet_AI[5] = { { 5,0,0,"Carrier",'C' } ,{ 4,0,0,"Battleship",'B' } ,{ 3,0,0 ,"Cruiser",'R' } ,{ 3,0,0,"Submarine",'S' },{ 2,0,0,"Destroyer",'D' } };
	//initalizes game boards
	initialize_board(board_player, ROW, COL);
	initialize_board(board_AI, ROW, COL);
	//random number generation
	srand((unsigned)time(NULL));
	//write to file
	FILE* outfile = NULL;
	outfile = open_file();

	//unsucesful AI test
	//AI_fighting_pit(outfile, 1);
	//start of main code
	greeting();
	printf("Would you like to set up your board or should I?(1 or 2)\n");
	do {
		scanf("%d", &choice);
		if (!(choice == 1 || choice == 2)) {
			getchar();
			printf("Would you like to set up your board or should I?(1 or 2)\n");
		}
	} while (!(choice == 1 || choice == 2));
	if(choice==1)
		place_ships_player(board_player, fleet_player);
	else
		place_ships_rand(board_player, fleet_player);
	place_ships_rand(board_AI, fleet_AI);
	//deciding who goes first
	player_turn = rand() % 2;
	//main game
	while (winner == 0) {
		if (player_turn == 0) {
			//for debuging
			print_board(board_AI, ROW, COL);
			Shot=fire_player(board_player, board_AI, &x, &y, fleet_AI);
			player_turn=update_log(fleet_AI, &player, Shot, outfile, player_turn, x, y);
			winner = check_winner(fleet_player, fleet_AI);
			
		}
		else{
			Shot = shot_AI(&x, &y, board_AI, board_player, fleet_player);
			player_turn = update_log(fleet_player, &AI, Shot, outfile, player_turn, x, y);
			winner = check_winner(fleet_player, fleet_AI);
		}
	}
	final_log_update(outfile, winner, player, AI);
	fclose(outfile);
	return 0;
}