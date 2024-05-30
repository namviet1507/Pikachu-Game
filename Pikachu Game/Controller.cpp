#include "Controller.h"

HWND Controller::consoleWindow = GetConsoleWindow();
HANDLE Controller::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void Controller::setUpConsole()
{
	setAndCenterWindow();
	setConsoleTitle();
	hideScrollBars();
	disableMouseInput();
	showCursor(false);
}

void Controller::gotoXY(int x, int y) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = x;
	Position.Y = y;
	SetConsoleCursorPosition(h, Position);
}

void Controller::hideScrollBars()
{
	ShowScrollBar(consoleWindow, SB_BOTH, 0);
}

void Controller::showCursor(bool show)
{
	CONSOLE_CURSOR_INFO info = { 1, show };
	SetConsoleCursorInfo(consoleOutput, &info);
}

void Controller::setConsoleTitle()
{
	SetConsoleTitle(L"\u0050\u0049\u004b\u0041\u0043\u0048\u0055"); // PIKACHU
}

void Controller::setAndCenterWindow()
{
	RECT rectClient, rectWindow;
	GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
	int width = 1100;
	int height = 768;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}

void Controller::disableMouseInput()
{
	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

int Controller::getConsoleInput() {
	int c = _getch();
	if (c == 0 || c == 224)
	{
		switch (_getch())
		{
		case KEY_UP:				//lên
			return 2;
		case KEY_LEFT:				//trái
			return 3;
		case KEY_RIGHT:				//phải
			return 4;
		case KEY_DOWN:				//xuống
			return 5;
		default:					//nút khác
			return 0;
		}
	}
	else
	{
		if (c == KEY_ESC)                  //esc
			return 1;
		else if (c == 87 || c == 119) //W, w
			return 2;
		else if (c == 65 || c == 97)  //A, a
			return 3;
		else if (c == 68 || c == 100) //D, d
			return 4;
		else if (c == 83 || c == 115) //S, s
			return 5;
		else if (c == 13)             //Enter
			return 6;
		else if (c == 72 || c == 104) //H, h
			return 7;
		else if (c == 77 || c == 109) // M, m
			return 8;
		else
			return 0;                 //nút khác
	}
}

void Controller::playSound(int i)
{
	static vector<const wchar_t*> soundFile{ L"Sound\\MOVE.wav", L"Sound\\enterbutton.wav", L"Sound\\error.wav", L"Sound\\enter.wav", L"Sound\\win.wav",  L"Sound\\SoundGame.wav", L"Sound\\lose.wav" };
	PlaySound(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
}