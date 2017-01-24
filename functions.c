#include "header.h"

//prints greeting and rules then clears the screen
void greeting() {

	printf("Hello and welcome to the game of battleship!\n");
	printf("Here are the rules\n");
	printf("Battleship is a two player game you will be player1\n");
	printf("The computer will be player 2\n");
	printf("You start the game by placing your ships\n");
	printf("Ships can only be placed horizonaly or verticaly\n");
	printf("After placing the ships either you or the computer will be chosen to go first\n");
	printf("Each of you will take turns guessing which position the oponents ships are\n");
	printf("You win if you sink all of the other players ships\n");
	printf("You will have 5 ships\n");
	printf("A Carrier(C) which takes up five spaces\n");
	printf("A Battleship(B) which takes up four spaces\n");
	printf("A Cruser(R) which takes up three spaces\n");
	printf("A Submarine(S) which takes up three spaces\n");
	printf("And a Destroyer(D) which takes up two spaces\n");
	printf("Please press enter to begin\n");
	system("pause");
	system("cls");
}

// initalizes the board with '~' because it looks like waves kinda
void initialize_board(char board[][10],int rows,int columns) {

	for (int x = 0; x < rows; x++) 
		for (int i = 0; i < columns; i++)
			board[x][i] = '~';
	
}

//displays the board rows 0-9 for wether the player has hit or missed
//rows 10-19 for the players own ships
// also displays the numbers for easy reading
void print_board(char board[][10], int rows, int columns) {

	int x = 0, i = 0;
	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for (x = 0; x < rows / 2; x++) {
		printf("%d ", x);
		for (i = 0; i < columns; i++)
			printf("%c ", board[x][i]);
		printf("\n");
	}
	printf("\n");
	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for (x = rows / 2; x < rows; x++) {
		printf("%d ", x - (rows / 2));
		for (i = 0; i < columns; i++)
			printf("%c ", board[x][i]);
		printf("\n");
	}
}

//returns 0 if there is no overlap
//returns 1 if there is an overlap
int check_overlap_ship(char board[][10], int row, int column,direction d,ship s) {
	int check = 0;
	switch (d) {
		case N:
			for (int x = row; x > row - s.size; x--) {
				if (board[x+10][column] != '~')
					check = 1;
			}
			break;
		case E:
			for (int x = column; x < column + s.size; x++) {
				if (board[row+10][x] != '~')
					check = 1;
			}
			break;
		case S:
			for (int x = row; x < row + s.size; x++) {
				if (board[x+10][column] != '~')
					check = 1;
			}
			break;
		case W:
			for (int x = column; x > column - s.size; x--) {
				if (board[row+10][x] != '~')
					check = 1;
			}
			break;
	}
	return check;
}

//returns 0 if that is not a valid place to place the ship
//returns 1 if it is a valid place to place the ship
int check_valid_ship_placement(char board[][10], int row, int column, direction d,ship s) {

	int x = 1;
	switch (d) {
	case N:
		if (row < s.size-1)
			x = 0;
		break;
	case E:
		if (column > 10 - s.size)
			x = 0;
		break;
	case S:
		if (row > 10 - s.size)
			x = 0;
		break;
	case W:
		if (column < s.size -1)
			x = 0;
		break;
	}
	return x;
}

//allows human to place ships
//makes sure human can only use valid locations
void place_ships_player(char board[][10],ship fleet[]) {
	int i = 0;
	int x = 0, y = 0;
	int place = 0;
	char direction = '\0';
	int direct = 0;
	int check = 0;
	int check_loc = 0;
	int check_placement = 0;
	int check_overlap = 0;
	for (i = 0; i < 5; i++) {
		do {
			print_board(board, ROW, COL);
			printf("Where do you want to place your %s(%d) please use x y coordinates\n", fleet[i].name,fleet[i].size);
			do {
				check_loc=scanf("%d%d", &x, &y);
				if ((!(x<10 && x>-1)) || (!(y<10 && y>-1))||check_loc==0||check_loc==1) {
					printf("Please input valid coordinates\n");
					check = 0;
					getchar();
				}
				else
					check = 1;
			} while (check != 1);
			getchar();
			check = 0;
			printf("Which direction do you want your %s(%d) to face choose\nNorth South East West (N,S,E or W)\n", fleet[i].name,fleet[i].size);
			do {
				scanf("%c", &direction);
				if ((direction == 'n' || direction == 'N') || (direction == 's' || direction == 'S') || (direction == 'e' || direction == 'E') || (direction == 'w' || direction == 'W')) {
					check = 1;
				}
				else {
					printf("please chose a proper direction\n");
					check = 0;
				}
			} while (check != 1);
			if (direction == 'n' || direction == 'N')
				direct = N;
			else if (direction == 'e' || direction == 'E')
				direct = E;
			else if (direction == 's' || direction == 'S')
				direct = S;
			else
				direct = W;
			check_placement=check_valid_ship_placement(board,y,x,direct,fleet[i]);
			if (check_placement == 0)
				printf("That is not a valid place for your %s(%d)\n", fleet[i].name,fleet[i].size);
			else
				check_overlap = check_overlap_ship(board, y, x,direct,fleet[i]);
			if (check_overlap == 1)
				printf("That placement overlaps your other ships\n");
			if (check_placement == 0 || check_overlap == 1)
				printf("Please try again and place correct coordinates\n");
			system("pause");
			system("cls");
		} while (check_placement==0||check_overlap==1);
		switch (direct) {
			case N:
				for (place = y; place > y - fleet[i].size; place--)
					board[place+10][x] = fleet[i].caracter;
				break;
			case E:
				for (place = x; place < x + fleet[i].size; place++)
					board[y+10][place] = fleet[i].caracter;
				break;
			case S:
				for (place = y; place < y + fleet[i].size; place++)
					board[place+10][x] = fleet[i].caracter;
				break;
			case W:
				for (place = x; place > x - fleet[i].size; place--)
					board[y+10][place] = fleet[i].caracter;
				break;
		}
	}
}

////copies one board to another
//void copy_board(char board[][10], char board_copy[][10]) {
//	int x = 0;
//	int i = 0;
//	for (x = 0; x < ROW; x++)
//		for (i = 0; i < COL; i++)
//			board_copy[x][i] = board[x][i];
//}

//asks the user for coordinates to fire apon
void get_chords(int *x, int *y,char board_player[][10]) {

	int check = 0;
	printf("Please select the coordinates you wish to fire apon (x y)\n");
	do {
		
		scanf("%d%d", x,y);
		if (!(*x > -1 && *x<10)||!(*y>-1 && *y < 10)) {
			printf("please input valid values\n");
			getchar();
		}
		else if (board_player[*y][*x] == 'H' || board_player[*y][*x] == 'M') {
			printf("You have already shot there\n");
		}
		else
			check = 1;
	}while (check==0);
}

//checks wether a shot is a hit or a miss 
//returns shot enum
shot check_hit_or_miss(int x, int y, char board_defense[][10], ship fleet[]) {
	
	shot Shot = miss;
	char c = '\0';
	c = board_defense[y + 10][x];
	switch (c) {
		case 'C':
			Shot = hit;
			fleet[0].hit+=1;
			break;
		case 'B':
			Shot = hit;
			fleet[1].hit+= 1;
			break;
		case 'R':
			Shot = hit;
			fleet[2].hit+= 1;
			break;
		case 'S':
			Shot = hit;
			fleet[3].hit+= 1;
			break;
		case 'D':
			Shot = hit;
			fleet[4].hit+= 1;
			break;	
		default:
			break;
	}
	return Shot;
}

//checks to see which ships are still afloat and makes the changes in the defenders fleet array
void check_ships(ship fleet_defense[],char board_defense[][10]) {

	int index_ship = 0;
	int board_index_row = 0;
	int board_index_col = 0;
	int count = 0;
	for (index_ship = 0; index_ship < 5; index_ship++) {
		count = 0;
		for (board_index_row = 0; board_index_row < ROW; board_index_row++) {
			for (board_index_col = 0; board_index_col < COL; board_index_col++) {
				if (fleet_defense[index_ship].caracter == board_defense[board_index_row][board_index_col]) {
					count+=1;
				}
			}
			
		}
		if (count ==0&&fleet_defense[index_ship].sunk!=2)
			fleet_defense[index_ship].sunk = 1;
	}

}
//registers shots and returns wether or not the shot was a hit or miss
//also edits the boards correctly
//tells player wether or not they hit
//also checks wether or not a ship has sunk
//also returs the coordinates of the shot
shot fire_player(char board_attack[][10], char board_defense[][10],int *x,int *y,ship fleet_defense[]) {
	
	int index = 0;
	shot Shot = miss;
	print_board(board_attack, ROW, COL);
	get_chords(x, y,board_attack);
	system("cls");
	Shot=check_hit_or_miss(*x, *y, board_defense, fleet_defense);
	if (Shot == hit) {
		board_defense[*y + 10][*x] = 'X';
		board_attack[*y][*x] = 'H';
	}
	else {
		board_defense[*y + 10][*x] = 'O';
		board_attack[*y][*x] = 'M';
	}
	print_board(board_attack, ROW, COL);
	if (Shot == hit)
		printf("Your shot at %d,%d was a hit!\n", *x, *y);
	else
		printf("Your shot at %d,%d was a miss\n", *x, *y);
	check_ships(fleet_defense, board_defense);
	for (index = 0; index < 5; index++) {
		if (fleet_defense[index].sunk == 1)
			printf("You sunk their %s\n", fleet_defense[index].name);
	}
	system("pause");
	system("cls");
	return Shot;
}

//generates a random direction
direction rand_direction() {
	direction x = S;
	x = rand() % 4;
	return x;
}

//generates random x and y coordinates
void rand_coordinates(int *x, int*y) {
	
	*x = rand() % 10;
	*y = rand() % 10;
}

//randomly places ship on the board
void place_ships_rand(char board[][10], ship fleet[]) {

	int check = 0;
	int index = 0;
	int place = 0;
	int y = 0, x = 0;
	direction d = S;
	for (index = 0; index < 5; index++) {
		do {
			d = rand_direction();
			rand_coordinates(&x, &y);
			if (check_valid_ship_placement(board, y, x, d, fleet[index]) == 0)
				check = 0;
			else if (check_overlap_ship(board, y, x, d, fleet[index]) == 1)
				check = 0;
			else
				check = 1;
		} while (check!=1);
		switch (d) {
		case N:
			for (place = y; place > y - fleet[index].size; place--)
				board[place + 10][x] = fleet[index].caracter;
			break;
		case E:
			for (place = x; place < x + fleet[index].size; place++)
				board[y + 10][place] = fleet[index].caracter;
			break;
		case S:
			for (place = y; place < y + fleet[index].size; place++)
				board[place + 10][x] = fleet[index].caracter;
			break;
		case W:
			for (place = x; place > x - fleet[index].size; place--)
				board[y + 10][place] = fleet[index].caracter;
			break;

		}
	}
}


//takes a random shot
//returns the x and y coords
void rand_shot(int *x, int *y, char board[][10]) {

	int check = 0;
	do {
		rand_coordinates(x, y);
		if (board[*y][*x] == 'H' || board[*y][*x] == 'M')
			check = 0;
		else
			check = 1;
	} while (check!=1);
}

//random AI shots 
//Kinda sucks, a lot
shot shot_AI(int *x,int *y,char board_offense[][10],char board_defense[][10],ship fleet_defense[]) {

	int index = 0;
	shot AI = miss;
	rand_shot(x, y, board_offense);
	if (check_hit_or_miss(*x, *y, board_defense, fleet_defense)==hit) {
		AI = hit;
		board_defense[*y + 10][*x] = 'X';
		board_offense[*y][*x] = 'H';
	}
	else {
		board_defense[*y + 10][*x] = 'O';
		board_offense[*y][*x] = 'M';
	}
	check_ships(fleet_defense, board_defense);
	for (index = 0; index < 5; index++) {
		if (fleet_defense[index].sunk == 1) {
			printf("You're %s has been sunk\n", fleet_defense[index].name);
			system("pause");
		}
	}
	system("cls");
	return AI;
}

FILE* open_file() {

	FILE*outfile = NULL;
	outfile = fopen("battleship.log","w");
	return outfile;
}

//player = 0 AI = 1
//at the end returns player variable to the other
int update_log(ship fleet_attacked[], stats *shooter, shot Shot, FILE* outfile,int player,int x,int y) {

	int index = 0;
	if (Shot == miss) {
		if (player == 0) {
			fprintf(outfile, "Player: %d,%d \"miss\"", x, y);
			player = 1;
		}
		else {
			fprintf(outfile, "AI: %d,%d \"miss\"", x, y);
			player = 0;
		}
		shooter->misses += 1;
		shooter->shots += 1;
	}
	else
	{
		if (player == 0) {

			fprintf(outfile, "Player: %d,%d \"hit\"", x, y);
			for (index = 0; fleet_attacked[index].sunk == 0 || fleet_attacked[index].sunk == 2 && index < 5; index++);
			if (fleet_attacked[index].sunk == 1) {
				fprintf(outfile, " %s has sunk", fleet_attacked[index].name);
				fleet_attacked[index].sunk = 2;
			}

			player = 1;
		}
		else {
			fprintf(outfile, "AI: %d,%d \"hit\"", x, y);
			for (index = 0; fleet_attacked[index].sunk == 0 || fleet_attacked[index].sunk == 2 && index < 5; index++);
			if (fleet_attacked[index].sunk == 1) {
				fprintf(outfile, " %s has sunk", fleet_attacked[index].name);
				fleet_attacked[index].sunk = 2;
			}
			player = 0;
		}
		shooter->hits += 1;
		shooter->shots += 1;
	}	
	fprintf(outfile, "\n");
	return player;
}

//0 if no winner
//1 if player wins
//2 if AI wins
int check_winner(ship fleet_player[], ship fleet_AI[]) {

	int index = 0;
	int count = 0;
	int check = 0;
	int check_player = 0;
	int check_AI = 0;
	for (index = 0; index < 5; index++) 
		if (fleet_player[index].sunk != 0)
			count++;
	if (count == 5)
		check_player = 1;
	for (index = 0, count = 0; index < 5; index++)
		if (fleet_AI[index].sunk != 0)
			count++;
	if (count == 5)
		check_AI = 1;
	if (check_player == 1)
		check = 2;
	else if (check_AI == 1)
		check = 1;
	return check;
}

//prints the winner and statistics
//precondition winner is not 0
void final_log_update(FILE* outfile, int winner, stats player, stats AI) {

	if (winner == 1) {
		fprintf(outfile, "The winner is Player\n\n");
	}
	else
		fprintf(outfile, "The winner is AI\n\n");

	//backslashes so hot right now
	fprintf(outfile, "\\\\\\\\\\Player Stats\\\\\\\\\\\n");
	fprintf(outfile, "Number Hits: %d\n",player.hits);
	fprintf(outfile, "Number Misses: %d\n", player.misses);
	fprintf(outfile, "Total Shots: %d\n", player.shots);
	fprintf(outfile, "Hit/Miss Ratio: %lf\n", (double)player.hits/(double)player.misses);
	fprintf(outfile, "\n", player.hits);

	fprintf(outfile, "\\\\\\\\\\AI Stats\\\\\\\\\\\\\\\\\n");
	fprintf(outfile, "Number Hits: %d\n", AI.hits);
	fprintf(outfile, "Number Misses: %d\n", AI.misses);
	fprintf(outfile, "Total Shots: %d\n", AI.shots);
	fprintf(outfile, "Hit/Miss Ratio: %lf\n", (double)AI.hits / (double)AI.misses);
	fprintf(outfile, "\n", AI.hits);
}

//everything below this i couldnt figure out so didnt add
//function meant just for the AI bowl
 int  update_log_AI(ship fleet_attacked[], stats *shooter, shot Shot,int AI_turn, int x, int y){
	int index = 0;
	if (Shot == miss) {
		shooter->misses += 1;
		shooter->shots += 1;
	}
	else
	{
		for (index = 0; fleet_attacked[index].sunk == 0 || fleet_attacked[index].sunk == 2 && index < 5; index++);
			if (fleet_attacked[index].sunk == 1) {
				fleet_attacked[index].sunk = 2;
		}
		shooter->hits += 1;
		shooter->shots += 1;
	}
	if (AI_turn == 0)
		AI_turn = 1;
	else
		AI_turn = 1;
	return AI_turn;
}
 
 void last_update_AI(FILE* outfile, AI_games games) {

	 fprintf(outfile, "games: %d\n", games.matches);
	 fprintf(outfile, "overall winner %s\n\n", games.overall_winner);

	 fprintf(outfile, "\\\\\\\\\\\\AI1 stats\\\\\\\\\\\\\n", games.overall_winner);
	 fprintf(outfile, "total shots %d\n", games.AI1_total.shots);
	 fprintf(outfile, "total hits %d\n", games.AI1_total.hits);
	 fprintf(outfile, "total misses %d\n", games.AI1_total.misses);
	 fprintf(outfile, "total hit/miss ratio %lf\n\n", (double)games.AI1_total.hits/ (double)games.AI1_total.misses);

	 fprintf(outfile, "\\\\\\\\\\\\AI2 stats\\\\\\\\\\\\\n", games.overall_winner);
	 fprintf(outfile, "total shots %d\n", games.AI2_total.shots);
	 fprintf(outfile, "total hits %d\n", games.AI2_total.hits);
	 fprintf(outfile, "total misses %d\n", games.AI2_total.misses);
	 fprintf(outfile, "total hit/miss ratio %lf\n\n", (double)games.AI2_total.hits / (double)games.AI2_total.misses);
 }

//testing AI against each other in crazy contests of endurance
//this is going to be fun
//no AI were harmed in the making of this function (maybe one or two)
void AI_fighting_pit(FILE*outfile,int games) {

	ship fleet_AI1[5]= { { 5,0,0,"Carrier",'C' } ,{ 4,0,0,"Battleship",'B' } ,{ 3,0,0 ,"Cruiser",'R' } ,{ 3,0,0,"Submarine",'S' },{ 2,0,0,"Destroyer",'D' } };
	ship fleet_AI2[5]={ { 5, 0, 0, "Carrier", 'C' }, { 4,0,0,"Battleship",'B' }, { 3,0,0 ,"Cruiser",'R' }, { 3,0,0,"Submarine",'S' }, { 2,0,0,"Destroyer",'D' } };
	char board_AI1[20][10];
	char board_AI2[20][10];
	initialize_board(board_AI1, ROW, COL);
	initialize_board(board_AI2, ROW, COL);
	stats AI1 = { 0,0,0 };
	stats AI2 = { 0,0,0 };
	shot Shot = miss;
	AI_games results = { 0,0,0,{0,0,0},{0,0,0},"" };
	int AI_turn = 0;
	int x = 0,y=0;
	int count = 0;
	int winer = 0;
	int x_seed = -1;
	int y_seed = -1;

	x = rand() % 10;
	y = rand() % 10;
	results.matches = games;
	for (count = 0; count < games; count++) {
		place_ships_rand(board_AI1, fleet_AI1);
		place_ships_rand(board_AI2, fleet_AI2);
		while (winer == 0) {
			//AI1 attack
			//method test
			Shot = shot_AI(&x, &y, board_AI1, board_AI2, fleet_AI2);
			AI_turn=update_log_AI(fleet_AI2, &AI1, Shot,AI_turn, x, y);
			winer= check_winner(fleet_AI1, fleet_AI2);
			//AI2 Attack
			if (winer == 0) {
				Shot = shot_AI_thorough(&x, &y, &x_seed, &y_seed, board_AI2, board_AI1, fleet_AI1);
				AI_turn=update_log_AI(fleet_AI1, &AI2, Shot,AI_turn, x, y);
				winer = check_winner(fleet_AI1, fleet_AI2);
			}
			
		}
		final_log_update(outfile, winer, AI1, AI2);
		//work on this firs
		//trying to impument total stuffs
		if (AI_turn == 0)
			results.AI1_wins += 1;
		else
			results.AI2_wins += 1;

		results.AI1_total.hits += AI1.hits;
		results.AI1_total.misses += AI1.misses;
		results.AI1_total.shots += AI1.shots;
		results.AI2_total.hits += AI2.hits;
		results.AI2_total.misses += AI1.misses;
		results.AI2_total.shots += AI2.shots;

		
		ship fleet_AI1[5] = { { 5,0,0,"Carrier",'C' } ,{ 4,0,0,"Battleship",'B' } ,{ 3,0,0 ,"Cruiser",'R' } ,{ 3,0,0,"Submarine",'S' },{ 2,0,0,"Destroyer",'D' } };
		ship fleet_AI2[5] = { { 5, 0, 0, "Carrier", 'C' },{ 4,0,0,"Battleship",'B' },{ 3,0,0 ,"Cruiser",'R' },{ 3,0,0,"Submarine",'S' },{ 2,0,0,"Destroyer",'D' } };
		initialize_board(board_AI1, ROW, COL);
		initialize_board(board_AI2, ROW, COL);
		stats AI1 = { 0,0,0 };
		stats AI2 = { 0,0,0 };
	}
	if (results.AI1_wins > results.AI2_wins)
		results.overall_winner = "AI1";
	else
		results.overall_winner = "AI1";
	last_update_AI(outfile, results);
}

//if there is a hit then it should find all of the hits connected to it

int search_ships(int *x,int *y ,direction d,char board_offense[][10]) {
	int check = 0;
	switch (d) {
		case N:
			if (*y - 1 >= 0) {
				if (board_offense[*y-1][*x]=='~') {
					*y = *y - 1;
					check = 1;
				}
				else if (board_offense[*y -1][*x] == 'M') {
					check=search_ships(&x, &y, W, board_offense);
				}
				else {
					*y = *y - 1;
					check = search_ships(&x, &y, N, board_offense);
				}
			}
			else
				check = search_ships(&x, &y, W, board_offense);
			break;
		case W:
			if (*x + 1 <= 9) {
				if (board_offense[*y][*x+1] == '~') {
					*x = *x + 1;
					check = 1;
				}
				else if (board_offense[*y][*x+1] == 'M') {
					check = search_ships(&x, &y, S, board_offense);
				}
				else {
					*x = *x + 1;
					check = search_ships(&x, &y, N, board_offense);
				}
			}
			else
				check = search_ships(&x, &y, S, board_offense);
			break;
		case S:
			if (*y + 1 <= 9) {
				if (board_offense[*y + 1][*x] == '~') {
					*y= *y+1;
					check = 1;
				}
				else if (board_offense[*y + 1][*x] == 'M') {
					check = search_ships(&x, &y, E, board_offense);
				}
				else {
					*y = *y + 1;
					check = search_ships(&x, &y, N, board_offense);
				}
			}
			else {
				check = search_ships(&x, &y, E, board_offense);
			}
		case E:
			if (*x -1 >= 0) {
				if (board_offense[*y ][*x-1] == '~') {
					*x = *x - 1;
					check = 1;
				}
				else if (board_offense[*y][*x - 1] == 'M') {
					check = 0;
				}
				else {
					*x = *x - 1;
					check = search_ships(&x, &y, N, board_offense);
				}
			
			}
			else {
				check = 0;
			}
	}
	return check;

}

shot shot_AI_thorough(int *x, int *y,int *x_seed,int *y_seed, char board_offense[][10], char board_defense[][10], ship fleet_defense[]) {

	int index = 0;
	shot AI = miss;
	int check = 0;
	check = search_ships(x_seed, y_seed, N, board_offense);
	if(check==0)
		rand_shot(x, y, board_offense);
	if (check_hit_or_miss(*x, *y, board_defense, fleet_defense) == hit) {
		AI = hit;
		board_defense[*y + 10][*x] = 'X';
		board_offense[*y][*x] = 'H';
		if (check == 0) {
			*x_seed = *x;
			*y_seed = *y;
		}
		
	}
	else {
		board_defense[*y + 10][*x] = 'O';
		board_offense[*y][*x] = 'M';
	}
	check_ships(fleet_defense, board_defense);
	return AI;
}