#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

#include <windows.h>

#define COLOR_WHITE		7
#define COLOR_GREEN		10
#define COLOR_LBLUE		11
#define COLOR_RED		12
#define COLOR_MAGENTA	13
#define COLOR_YELLOW	14

using namespace std;

#pragma once
class Console {

	private: 
		HANDLE hConsole;

		static string LINE_CLEAR;

	public:
		Console();
		~Console();

		int NextInt(function<void()> onError);
		char NextChar(function<void()> onError);
		
		inline void SetColor(int colorIndex) {
			SetConsoleTextAttribute(hConsole, colorIndex);
		}

		inline void SetCursorPos(int x, int y) {
			COORD point = { x, y };
			SetConsoleCursorPosition(hConsole, point);
		}

		inline void Print(const char* str) {
			cout << str;
		}

		inline void PrintFormat(const char* format, ...) {
			va_list args;
			va_start(args, format);
			vprintf(format, args);
			va_end(args);
		}

		inline void ClearLine() {
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(hConsole, &csbi);

			printf(LINE_CLEAR.c_str());
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
		}

		inline void ClearLine(int y) {
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(hConsole, &csbi);

			COORD target = { 0, y };
			SetConsoleCursorPosition(hConsole, target);
			printf(LINE_CLEAR.c_str());

			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
		}

		void ClearLines(int y, int n);

		void PrintArray(const vector<string> & arr);
};