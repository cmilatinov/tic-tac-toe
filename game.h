#include <string>
#include <vector>
#include <functional>

#include "console.h"

#define BOARD_FORMAT		"\n\t %c | %c | %c\n\t-----------\n\t %c | %c | %c\n\t-----------\n\t %c | %c | %c"
#define BOARD_SIZE			9
#define BOARD_CHAR_P1		'X'
#define BOARD_CHAR_P2		'O'
#define BOARD_CHAR_EMPTY	' '

#define MSG_WELCOME "Welcome to Tic Tac Toe! \n\nThe board is labelled with numbers 1 through 9 from top left to bottom right. \n\nPlayer 1 may start the game by inputting the number corresponding to their first move."
#define MSG_TURN "It is currently player %i's turn, please select your next move."
#define MSG_CURSOR "    > "

#define ERR_INVALID_INPUT		1
#define ERR_INVALID_INPUT_STR	"Please enter a valid integer (1-9).\n"
#define ERR_INVALID_MOVE		2
#define ERR_INVALID_MOVE_STR	"A player has already occupied that square. Please enter a valid move."

#define GAME_END_WIN			3
#define GAME_END_WIN_STR		"Player %i wins! Would you like to play again? [Y/N]"
#define GAME_END_DRAW			4
#define GAME_END_DRAW_STR		"The game ends in a draw! Would you like to play again? [Y/N]"

#define PLAYER1_TURN	0
#define PLAYER2_TURN	1


#define INPUT_START		13

using namespace std;

#pragma once
class Game {

	struct PlayerMove {
		unsigned int player;
		int move;
	};

	private:
		Console * console;

		vector<PlayerMove> moves;
		char * board;
		unsigned int playerTurn;
		bool gameEnded;

		int status;
		
		void DrawIntro();
		void DrawBoard();
		void DrawInput(int err);

		int CheckWin();

	public:
		Game();
		~Game();

		void Run();

};