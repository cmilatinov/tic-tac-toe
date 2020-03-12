#include "console.h"

string Console::LINE_CLEAR = string(120, ' ');

Console::Console(): 
	hConsole(GetStdHandle(STD_OUTPUT_HANDLE)) {}

Console::~Console() {}

int Console::NextInt(function<void()> onError) {
	int c;
	cin >> c;

	while (cin.fail()) {
		onError();
		cin.clear();
		cin.ignore();
		cin >> c;
	}
		
	return c;
}

char Console::NextChar(function<void()> onError) {
	char c;
	cin >> c;

	while (cin.fail()) {
		onError();
		cin.clear();
		cin.ignore();
		cin >> c;
	}

	return c;
}

void Console::ClearLines(int y, int n) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	for (int i = y; i < y + n; i++) {
		COORD target = { 0, i };
		SetConsoleCursorPosition(hConsole, target);
		printf(LINE_CLEAR.c_str());
	}

	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void Console::PrintArray(const vector<string> & arr) {
	std::for_each(arr.begin(), arr.end(), [this] (const string& n) {
		PrintFormat("%s, ", n.c_str());
	});
}
