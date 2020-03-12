#include "game.h"

Game::Game():
	console(new Console()), 
	board(new char[BOARD_SIZE]),
	playerTurn(0),
	gameEnded(false),
	status(0) {
	memset(board, BOARD_CHAR_EMPTY, BOARD_SIZE);
	moves.clear();
}

Game::~Game() {
	delete console;
	delete board;
}

void Game::DrawIntro() {
	console->SetCursorPos(0, 0);
	console->SetColor(COLOR_WHITE);
	console->Print(MSG_WELCOME);
}

void Game::DrawBoard() {
	console->SetCursorPos(0, 6);
	console->SetColor(COLOR_WHITE);
	console->PrintFormat(BOARD_FORMAT,
		board[0], board[1], board[2],
		board[3], board[4], board[5],
		board[6], board[7], board[8]);
}

void Game::DrawInput(int status) {
	this->status = status;

	console->ClearLines(INPUT_START, 17);

	console->SetCursorPos(0, INPUT_START);
	vector<string> strMoves;
	transform(moves.begin(), moves.end(), 
		back_inserter(strMoves), 
		[](const PlayerMove& move) { return "P" + to_string(move.player + 1) + " => " + to_string(move.move); });
	console->SetColor(COLOR_YELLOW);
	console->Print("Moves: ");
	console->PrintArray(strMoves);
	
	console->SetCursorPos(0, INPUT_START + 2);
	switch (status) {
		case ERR_INVALID_INPUT:
			console->SetColor(COLOR_RED);
			console->Print(ERR_INVALID_INPUT_STR);
			break;
		case ERR_INVALID_MOVE:
			console->SetColor(COLOR_RED);
			console->Print(ERR_INVALID_MOVE_STR);
			break;
		case GAME_END_WIN:
			console->SetColor(COLOR_GREEN);
			console->PrintFormat(GAME_END_WIN_STR, playerTurn + 1);
			break;
		case GAME_END_DRAW:
			console->SetColor(COLOR_LBLUE);
			console->Print(GAME_END_DRAW_STR);
			break;
	}

	if (status != GAME_END_WIN && status != GAME_END_DRAW) {
		console->SetCursorPos(0, INPUT_START + 4);
		console->SetColor(COLOR_WHITE);
		console->PrintFormat(MSG_TURN, playerTurn + 1);
	}

	console->SetCursorPos(0, INPUT_START + 6);
	console->SetColor(COLOR_WHITE);
	console->Print(MSG_CURSOR);
}

void Game::Run() {

	// Draw game
	DrawIntro();
	DrawBoard();
	DrawInput(false);
	
	while(true) {

		// If game has ended
		if (gameEnded) {

			// Check replay
			char answer = console->NextChar([] {});

			// Replay
			if (answer == 'Y' || answer == 'y') {
				memset(board, BOARD_CHAR_EMPTY, BOARD_SIZE);
				moves.clear();
				gameEnded = false;
				playerTurn = PLAYER1_TURN;
				DrawBoard();
				DrawInput(false);

			// Exit
			} else if (answer == 'N' || answer == 'n')
				return;

			// Ask again
			else {
				DrawInput(status);
				continue;
			}
		}
		
		// Get move input from user
		int move = console->NextInt([this] {
			DrawInput(ERR_INVALID_INPUT);
		});

		// Invalid input
		if (move <= 0 || move > BOARD_SIZE) {
			DrawInput(ERR_INVALID_INPUT);
			continue;
		}

		// Invalid move
		if (board[move - 1] != BOARD_CHAR_EMPTY) {
			DrawInput(ERR_INVALID_MOVE);
			continue;
		}

		// Make move
		moves.push_back({ playerTurn, move });
		board[move - 1] = playerTurn ? BOARD_CHAR_P2 : BOARD_CHAR_P1;

		// Check win status
		int status = CheckWin();
		
		// Next player turn if game not ended
		if (status == 0)
			playerTurn = ~playerTurn & 0x1;

		// Game ended
		else
			gameEnded = true;

		// Redraw
		DrawBoard();
		DrawInput(status);

	}
}

int Game::CheckWin() {

	// Player char
	char playerChar = playerTurn == PLAYER1_TURN ? BOARD_CHAR_P1 : BOARD_CHAR_P2;

	// Win conditions
	static const int winConditions[8][3] = {
		{0, 1, 2}, {3, 4, 5}, {6, 7, 8},
		{0, 3, 6}, {1, 4, 7}, {2, 5, 8},
		{0, 4, 8}, {2, 4, 6}
	};

	// Win check
	for (int i = 0; i < 8; i++) {
		if (board[winConditions[i][0]] == playerChar &&
			board[winConditions[i][1]] == playerChar &&
			board[winConditions[i][2]] == playerChar) {
			return GAME_END_WIN;
		}
	}

	// Game not ended check
	for (int i = 0; i < BOARD_SIZE; i++)
		if (board[i] == BOARD_CHAR_EMPTY)
			return 0;

	// Draw
	return GAME_END_DRAW;
}