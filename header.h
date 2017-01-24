#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROW 20
#define COL 10
typedef struct Ship {
	int size;
	int sunk;
	int hit;
	char name[25];
	char caracter;
}ship;
typedef struct Stats {
	int shots;
	int hits;
	int misses;
}stats;
typedef struct Stats_AI_GAMES {
	int matches;
	int AI1_wins;
	int AI2_wins;
	stats AI1_total;
	stats AI2_total;
	char* overall_winner;
}AI_games;
typedef enum Direction {
	N, E, S, W
}direction;
typedef enum Shot {
	hit,miss
}shot;
void greeting();
void initialize_board(char board[][10],int rows,int columns);
void print_board(char board[][10], int rows, int columns);
int check_overlap_ship(char board[][10],int row,int column,direction d,ship s);
int check_valid_ship_placement(char board[][10], int row, int column,direction d,ship s);
void place_ships_player(char board[][10],ship fleet[]);
//void copy_board(char board[][10], char board_copy[][10]);
void get_chords(int *x, int *y,char board_attack[][10]);
void check_ships(ship fleet_defense[], char board_defense[][10]);
shot fire_player(char board_attack[][10], char board_defense[][10], int *x, int *y, ship fleet_defense[]);
direction rand_direction();
void rand_coordinates(int *x, int*y);
void place_ships_rand(char board_AI[][10], ship fleet[]);
void rand_shot(int *x, int *y, char board[][10]);
shot shot_AI(int *x, int *y, char board_offense[][10], char board_defense[][10], ship fleet_defense[]);
FILE* open_file();
int update_log(ship fleet_attacked[],stats *shooter,shot Shot,FILE* outfile,int player,int x, int y);
int check_winner(ship fleet_player[], ship fleet_AI[]);
void final_log_update(FILE* outfile,int winner,stats player,stats AI);
void AI_fighting_pit(FILE* outfile,int games);
void last_update_AI(FILE* outfile, AI_games games);