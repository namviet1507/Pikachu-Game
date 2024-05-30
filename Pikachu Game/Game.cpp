#include "Game.h"
#include "Struct.h"
#include "Controller.h"

int Game::width;
int Game::height;
int Game::_mode;
int Game::tmp_score;
int Game::life;
int Game::total_block;
int Game::height_bg;
int Game::no_suggest;
char** Game::board;
bool Game::isPlaying; //true la con block, false la het
bool Game::playAgain; //true la choi lai
bool overTime = false;
Game::Point Game::cur_block{ 0, 0, 1, 1 };
Player a;
string* Game::background;
bool Game::choice_login;
void Game::setupGame() {
	Game::life = 3;
	Game::choice_login = false;
	Game::_mode = Menu::printLevel();
	if (Game::_mode == 0) {
		a.mode = "EASY";
	}
	else if (Game::_mode == 1) {
		a.mode = "NORMAL";
	}
	else if (Game::_mode == 2) {
		a.mode = "DIFFICULT";
	}
	else {
		Menu::goBack();
		return;
	}
	system("cls");
	Controller::gotoXY(0, 0);
	Menu::printLogo();
	int choice[2] = { 0,0 }, curChoice = 0;
	while (true) {
		choice[curChoice] = 1;
		if (choice[0]) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(40, 20 + i);
				cout << "           ";
			}
			Controller::gotoXY(42, 21);
			cout << "LOG IN";
			Controller::gotoXY(20, 24);
			Menu::SetColor(WHITE, GREEN);
			cout << "Your score will be updated if in this round your score is higher than the previous round";
		}
		else {
			Controller::gotoXY(40, 21);
			Menu::SetColor(WHITE, WHITE);
			cout << "           ";
			Menu::SetColor(WHITE, YELLOW);
			Menu::printRectangle(40, 20, 9, 2);
			Menu::SetColor(WHITE, PURPLE);
			Controller::gotoXY(42, 21);
			cout << "LOG IN";
			Controller::gotoXY(20, 24);
			Menu::SetColor(WHITE, WHITE);
			cout << "                                                                                            ";
		}
		if (choice[1]) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(62, 20 + i);
				cout << "           ";
			}
			Controller::gotoXY(64, 21);
			cout << "SIGN UP";
			Controller::gotoXY(45, 24);
			Menu::SetColor(WHITE, GREEN);
			cout << "Create a new account";
			Controller::gotoXY(20, 25);
			Menu::SetColor(WHITE, LIGHT_RED);
			cout << "If you do not enter any information, the system will default to unknown ";
			Controller::gotoXY(30, 26);
			cout << "and cannot use this data to log in for the next game.";
		}
		else {
			Controller::gotoXY(62, 21);
			Menu::SetColor(WHITE, WHITE);
			cout << "           ";
			Menu::SetColor(WHITE, YELLOW);
			Menu::printRectangle(62, 20, 9, 2);
			Menu::SetColor(WHITE, PURPLE);
			Controller::gotoXY(64, 21);
			cout << "SIGN UP";
			Menu::SetColor(WHITE, WHITE);
			Controller::gotoXY(20, 25);
			cout << "                                                                           ";
			Controller::gotoXY(30, 26);
			cout << "                                                            ";
		}
		int temp, key;
		if (temp = _getch()) {
			if (temp != 224 && temp)
			{
				if (temp == KEY_ENTER) {
					system("cls");
					system("color 70");
					if (curChoice == 0) {
						Controller::playSound(ENTER_SOUND);
						Controller::gotoXY(0, 0);
						Menu::printLogo();
						Game::login();
						break;
					}
					else {
						Controller::playSound(ENTER_SOUND);
						Controller::gotoXY(0, 0);
						Menu::printLogo();
						Game::signup();
						break;
					}
				}
			}
			else {
				key = _getch();
				Controller::playSound(MOVE_SOUND);
				switch (key)
				{
				case KEY_LEFT:
					choice[curChoice] = 0;
					if (curChoice > 0) curChoice--;
					else curChoice = 1;
					break;
				case KEY_RIGHT:
					choice[curChoice] = 0;
					if (curChoice < 1) curChoice++;
					else curChoice = 0;
				default:
					break;
				}
			}
		}
	}
	if (a.playerName == "") a.playerName = "unknown";
	if (a.playerID == "") a.playerID = "unknown";
	if (a.className == "") a.className = "unknown";
	Controller::showCursor(false);
	// -----------
	Game::setSize();
	Game::genBoard();
	Game::printBoard();
	Game::createBackground();
	Game::printInterface();
	Game::controlPoint();
}

void Game::printInterface() {
	Controller::gotoXY(2, 10);
	Menu::SetColor(WHITE, BLUE);
	cout << "NAME: " << a.playerName;
	Controller::gotoXY(2, 12);
	cout << "ID: " << a.playerID;
	Controller::gotoXY(2, 14);
	cout << "Class: " << a.className;
	Controller::gotoXY(2, 2);
	Menu::SetColor(WHITE, PURPLE);
	cout << "NO_Suggestion: " << Game::no_suggest;
	Menu::SetColor(WHITE, BLUE);
	Controller::gotoXY(30, 2);
	cout << "                             ";
	Controller::gotoXY(30, 2);
	cout << "Moves: ";
	Controller::gotoXY(55, 2);
	cout << "                               ";
	Controller::gotoXY(55, 2);
	cout << "Scores: ";
	Menu::SetColor(WHITE, BLACK);
	cout << tmp_score;
	Menu::SetColor(WHITE, BLUE);
	cout << " BTC";
	Controller::gotoXY(80, 2);
	cout << "Life: ";
	Menu::SetColor(WHITE, PURPLE);
	cout << life;
	Menu::SetColor(WHITE, BLACK);
	Menu::printRectangle(18, 25, 20, 2);
	Menu::SetColor(WHITE, RED);
	Controller::gotoXY(20, 26);
	cout << "Enter ESC:  Quit" << endl;
	Menu::SetColor(WHITE, BLACK);
	Menu::printRectangle(48, 25, 17, 2);
	Menu::SetColor(WHITE, GREEN);
	Controller::gotoXY(50, 26);
	cout << "Enter H:  Help" << endl;
	Menu::SetColor(WHITE, BLACK);
	Menu::printRectangle(78, 25, 28, 2);
	Menu::SetColor(WHITE, PURPLE);
	Controller::gotoXY(80, 26);
	cout << "Enter M:  Move Suggestion" << endl;
}

int Game::getsizeBg(string fileName) {
	fstream file;
	file.open(fileName.c_str(), ios::in);
	int height = 0;
	while (!file.eof()) {
		string tmp;
		getline(file, tmp);
		height++;
	}
	file.close();
	return height;
}

void Game::getBackground(string fileName) {
	Game::height_bg = Game::getsizeBg(fileName);
	Game::background = new string[Game::height_bg];
	fstream file;
	file.open(fileName.c_str(), ios::in);
	int i = 0;
	while (!file.eof()) {
		getline(file, background[i]);
		i++;
	}
	file.close();
}

void Game::createBackground() {
	if (a.mode == "EASY") {
		Game::getBackground("readFile\\easy.txt");
	}
	else if (a.mode == "NORMAL") {
		Game::getBackground("readFile\\normal.txt");
	}
	else {
		Game::getBackground("readFile\\difficult.txt");
	}
}

void Game::displayBackground(Point block) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			Controller::gotoXY(block.pX + j, block.pY + i);
			cout << background[block.pY + i - 5][block.pX + j - (120 / 2 - (Game::width * 10) / 2)];
		}
	}
}

void Game::displayStatus(bool win) {
	a.score = Game::tmp_score;
	Menu::writeLeaderBoard(a);
	system("cls");
	system("color 1");
	if (win) {
		int cnt = 20;
		Controller::playSound(WIN_SOUND);
		Menu::SetColor(BLACK, BRIGHT_WHITE);
		Controller::gotoXY(28, 2);
		cout << "NAME: " << a.playerName;
		Controller::gotoXY(55, 2);
		cout << "ID: " << a.playerID;
		Controller::gotoXY(84, 2);
		cout << "CLASS: " << a.className;
		Controller::gotoXY(55, 4);
		cout << "SCORE: " << Game::tmp_score;
		while (cnt--) {
			Menu::SetColor(BLACK, rand() % 14 + 2);
			Controller::gotoXY(12, 8);
			cout << "  ___    ___ ________  ___  ___          ___       __   ___  ________           ___       ";
			Menu::SetColor(BLACK, rand() % 14 + 2);
			Controller::gotoXY(12, 9);
			cout << " |\\  \\  /  /|\\   __  \\|\\  \\|\\  \\        |\\  \\     |\\  \\|\\  \\|\\   ___  \\        |\\  \\      ";
			Menu::SetColor(BLACK, rand() % 14 + 2);
			Controller::gotoXY(12, 10);
			cout << " \\ \\  \\/  / | \\  \\|\\  \\ \\  \\\\\\  \\       \\ \\  \\    \\ \\  \\ \\  \\ \\  \\\\ \\  \\       \\ \\  \\     ";
			Menu::SetColor(BLACK, rand() % 14 + 2);
			Controller::gotoXY(12, 11);
			cout << "  \\ \\    / / \\ \\  \\\\\\  \\ \\  \\\\\\  \\       \\ \\  \\  __\\ \\  \\ \\  \\ \\  \\\\ \\  \\       \\ \\  \\    ";
			Menu::SetColor(BLACK, rand() % 14 + 2);
			Controller::gotoXY(12, 12);
			cout << "   \\/  /  /   \\ \\  \\\\\\  \\ \\  \\\\\\  \\       \\ \\  \\|\\__\\_\\  \\ \\  \\ \\  \\\\ \\  \\       \\ \\__\\   ";
			Menu::SetColor(BLACK, rand() % 14 + 2);
			Controller::gotoXY(12, 13);
			cout << " __/  / /      \\ \\_______\\ \\_______\\       \\ \\____________\\ \\__\\ \\__\\\\ \\__\\       \\|__|   ";
			Menu::SetColor(BLACK, rand() % 14 + 2);
			Controller::gotoXY(12, 14);
			cout << "|\\___/ /        \\|_______|\\|_______|        \\|____________|\\|__|\\|__| \\|__|           ___ ";
			Menu::SetColor(BLACK, rand() % 14 + 2);
			Controller::gotoXY(12, 15);
			cout << "\\|___|/                                                                              |\\__\\";
			Menu::SetColor(BLACK, rand() % 14 + 2);
			Controller::gotoXY(97, 16);
			cout << "\\|__|";
			Sleep(350);
		}
		Menu::SetColor(BLACK, BRIGHT_WHITE);
		Menu::printRectangle(33, 17, 45, 8);
		Controller::gotoXY(44, 18);
		cout << "DO YOU WANT TO CONTINUE ?";
		int choice[2] = { 0,0 }, curChoice = 0;
		while (true) {
			choice[curChoice] = 1;
			if (choice[0]) {
				Menu::SetColor(GREEN, BRIGHT_WHITE);
				for (int i = 0; i < 3; i++) {
					Controller::gotoXY(40, 20 + i);
					cout << "           ";
				}
				Controller::gotoXY(44, 21);
				cout << "YES";
			}
			else {
				Controller::gotoXY(40, 21);
				Menu::SetColor(BLACK, BLACK);
				cout << "           ";
				Menu::SetColor(BLACK, LIGHT_YELLOW);
				Menu::printRectangle(40, 20, 9, 2);
				Menu::SetColor(BLACK, LIGHT_YELLOW);
				Controller::gotoXY(44, 21);
				cout << "YES";
			}
			if (choice[1]) {
				Menu::SetColor(GREEN, BRIGHT_WHITE);
				for (int i = 0; i < 3; i++) {
					Controller::gotoXY(62, 20 + i);
					cout << "           ";
				}
				Controller::gotoXY(66, 21);
				cout << "NO";
			}
			else {
				Controller::gotoXY(62, 21);
				Menu::SetColor(BLACK, BLACK);
				cout << "           ";
				Menu::SetColor(BLACK, LIGHT_YELLOW);
				Menu::printRectangle(62, 20, 9, 2);
				Menu::SetColor(BLACK, LIGHT_YELLOW);
				Controller::gotoXY(66, 21);
				cout << "NO";
			}
			int temp, key;
			if (temp = _getch()) {
				if (temp != 224 && temp)
				{
					if (temp == KEY_ENTER) {
						system("cls");
						system("color 70");
						if (curChoice == 0) {
							if (Game::_mode < 2) {
								Game::_mode += 1;
								if (Game::_mode == 1) {
									a.mode = "NORMAL";
								}
								else {
									a.mode = "DIFFICULT";
								}
							}
							if (Game::check_account_exists())
								Game::choice_login = true;
							Game::createBackground();
							Game::setSize();
							Game::genBoard();
							Game::cur_block.iX = 0;
							Game::cur_block.iY = 0;
							Game::printBoard();
							Game::printInterface();
							Game::controlPoint();
						}
						else {
							Menu::printMainScreen();
						}
					}
				}
				else {
					key = _getch();
					Controller::playSound(MOVE_SOUND);
					switch (key)
					{
					case KEY_LEFT:
						choice[curChoice] = 0;
						if (curChoice > 0) curChoice--;
						else curChoice = 1;
						break;
					case KEY_RIGHT:
						choice[curChoice] = 0;
						if (curChoice < 1) curChoice++;
						else curChoice = 0;
					default:
						break;
					}
				}
			}
		}
	}
	else {
		Controller::playSound(LOSE_SOUND);
		Menu::SetColor(BLACK, LIGHT_RED);
		Controller::gotoXY(50, 7);
		cout << R"(
	 ________  ___      ___ _______   ________          ________  ________  _____ ______   _______      
	|\   __  \|\  \    /  /|\  ___ \ |\   __  \        |\   ____\|\   __  \|\   _ \  _   \|\  ___ \     
	\ \  \|\  \ \  \  /  / | \   __/|\ \  \|\  \       \ \  \___|\ \  \|\  \ \  \\\__\ \  \ \   __/|    
	 \ \  \\\  \ \  \/  / / \ \  \_|/_\ \   _  _\       \ \  \  __\ \   __  \ \  \\|__| \  \ \  \_|/__  
	  \ \  \\\  \ \    / /   \ \  \_|\ \ \  \\  \|       \ \  \|\  \ \  \ \  \ \  \    \ \  \ \  \_|\ \ 
	   \ \_______\ \__/ /     \ \_______\ \__\\ _\        \ \_______\ \__\ \__\ \__\    \ \__\ \_______\
	    \|_______|\|__|/       \|_______|\|__|\|__|        \|_______|\|__|\|__|\|__|     \|__|\|_______|

		)";

		Menu::SetColor(BLACK, BRIGHT_WHITE);
		Menu::printRectangle(33, 17, 45, 8);
		Controller::gotoXY(44, 18);
		cout << "DO YOU WANT TO PLAY AGAIN ?";
		int choice[2] = { 0,0 }, curChoice = 0;
		while (true) {
			choice[curChoice] = 1;
			if (choice[0]) {
				Menu::SetColor(GREEN, BRIGHT_WHITE);
				for (int i = 0; i < 3; i++) {
					Controller::gotoXY(40, 20 + i);
					cout << "           ";
				}
				Controller::gotoXY(44, 21);
				cout << "YES";
			}
			else {
				Controller::gotoXY(40, 21);
				Menu::SetColor(BLACK, BLACK);
				cout << "           ";
				Menu::SetColor(BLACK, LIGHT_YELLOW);
				Menu::printRectangle(40, 20, 9, 2);
				Menu::SetColor(BLACK, LIGHT_YELLOW);
				Controller::gotoXY(44, 21);
				cout << "YES";
			}
			if (choice[1]) {
				Menu::SetColor(GREEN, BRIGHT_WHITE);
				for (int i = 0; i < 3; i++) {
					Controller::gotoXY(62, 20 + i);
					cout << "           ";
				}
				Controller::gotoXY(66, 21);
				cout << "NO";
			}
			else {
				Controller::gotoXY(62, 21);
				Menu::SetColor(BLACK, BLACK);
				cout << "           ";
				Menu::SetColor(BLACK, LIGHT_YELLOW);
				Menu::printRectangle(62, 20, 9, 2);
				Menu::SetColor(BLACK, LIGHT_YELLOW);
				Controller::gotoXY(66, 21);
				cout << "NO";
			}
			int temp, key;
			if (temp = _getch()) {
				if (temp != 224 && temp)
				{
					if (temp == KEY_ENTER) {
						system("cls");
						system("color 70");
						if (curChoice == 0) {
							Game::isPlaying = true;
							Game::playAgain = true;
							Game::reset();
							break;
						}
						else {
							Menu::printMainScreen();
						}
					}
				}
				else {
					key = _getch();
					Controller::playSound(MOVE_SOUND);
					switch (key)
					{
					case KEY_LEFT:
						choice[curChoice] = 0;
						if (curChoice > 0) curChoice--;
						else curChoice = 1;
						break;
					case KEY_RIGHT:
						choice[curChoice] = 0;
						if (curChoice < 1) curChoice++;
						else curChoice = 0;
					default:
						break;
					}
				}
			}
		}
	}
}

void Game::setSize() {
	if (Game::_mode == 0) {
		Game::height = 4;
		Game::width = 7;
	}
	else if (Game::_mode == 1) {
		Game::height = 4;
		Game::width = 8;
	}
	else if (Game::_mode == 2) {
		Game::height = 5;
		Game::width = 8;
	}
}

void Game::genBoard() {
	Game::playAgain = false;
	Game::total_block = Game::height * Game::width;
	srand((unsigned int)time(NULL));

	Game::board = new char* [Game::height];
	for (int i = 0; i < Game::height; i++)
		Game::board[i] = new char[Game::width];

	int n = (Game::height * Game::width) / 2;

	string chars = "";
	for (int i = 0; i < n; i++) {
		char chr = char(rand() % 26 + 65);
		chars += chr;
	}
	chars += chars;

	for (int i = 0; i < Game::height; i++) {
		for (int j = 0; j < Game::width; j++) {
			int t = rand() % chars.size();

			Game::board[i][j] = chars[t];
			chars.erase(t, 1);
		}
	}

}

bool Game::check_account_exists() {
	fstream fin;
	fin.open("rank.txt", ios::in);
	Player tmp;
	while (!fin.eof()) {
		getline(fin, tmp.playerName);
		getline(fin, tmp.playerID);
		getline(fin, tmp.className);
		fin >> tmp.mode >> tmp.score;
		fin.ignore();
		if (tmp.playerName == a.playerName && tmp.playerID == a.playerID && tmp.className == a.className && tmp.mode == a.mode) {
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}

void Game::login() {
	a.playerName = "";
	a.playerID = "";
	a.className = "";
	Controller::gotoXY(53, 18);
	cout << "                        ";
	Controller::gotoXY(50, 20);
	cout << "                        ";
	Controller::gotoXY(60, 22);
	cout << "                        ";
	Menu::SetColor(WHITE, RED);
	Controller::gotoXY(28, 16);
	cout << "Please enter your name shortly, under 10 characters!";
	Menu::SetColor(WHITE, LIGHT_BLUE);
	Controller::showCursor(true);
	while (a.playerName == "") {
		Controller::gotoXY(35, 18);
		cout << "Enter your name:  ";
		getline(cin, a.playerName);
		if (a.playerName == "") {
			Game::warning();
		}
	}
	while (a.playerID == "") {
		Controller::gotoXY(35, 20);
		cout << "Enter your ID:  ";
		getline(cin, a.playerID);
		if (a.playerID == "") {
			Game::warning();
		}
	}
	while (a.className == "") {
		Controller::gotoXY(35, 22);
		cout << "Enter your class's name:  ";
		getline(cin, a.className);
		if (a.className == "") {
			Game::warning();
		}
	}
	if (Game::check_account_exists()) {
		Controller::gotoXY(40, 24);
		Menu::SetColor(WHITE, GREEN);
		cout << "Successful Login";
		Game::choice_login = true;
		Controller::playSound(ENTER_SOUND);
		Sleep(2000);
	}
	if (Game::choice_login == false) {
		Controller::gotoXY(40, 24);
		Menu::SetColor(WHITE, RED);
		cout << "Account does not exist. Try again please !";
		Controller::playSound(ERROR_SOUND);
		Controller::gotoXY(40, 26);
		Menu::SetColor(WHITE, GREEN);
		cout << "Enter S to sign up";
		Controller::gotoXY(40, 27);
		Menu::SetColor(WHITE, YELLOW);
		cout << "Press any key to try again";
		int c = _getch();
		if (c == 83 || c == 115) {
			Controller::playSound(ENTER_SOUND);
			Controller::gotoXY(40, 24);
			Menu::SetColor(WHITE, WHITE);
			cout << "                                           ";
			Controller::gotoXY(40, 26);
			cout << "                              ";
			Controller::gotoXY(40, 27);
			cout << "                              ";
			Controller::gotoXY(53, 18);
			cout << "                        ";
			Controller::gotoXY(50, 20);
			cout << "                        ";
			Controller::gotoXY(60, 22);
			cout << "                        ";
			Game::signup();
		}
		else {
			Controller::playSound(ENTER_SOUND);
			Controller::gotoXY(40, 24);
			Menu::SetColor(WHITE, WHITE);
			cout << "                                           ";
			Controller::gotoXY(40, 26);
			cout << "                              ";
			Controller::gotoXY(40, 27);
			cout << "                              ";
			Game::login();
		}
	}
}

void Game::warning() {
	Controller::showCursor(false);
	Controller::playSound(ERROR_SOUND);
	Controller::gotoXY(35, 25);
	Menu::SetColor(WHITE, RED);
	cout << "Please enter at least 1 character";
	Sleep(1000);
	Menu::SetColor(WHITE, WHITE);
	Controller::gotoXY(35, 25);
	cout << "                                   ";
	Menu::SetColor(WHITE, LIGHT_BLUE);
	Controller::showCursor(true);
}

void Game::signup() {
	Menu::SetColor(WHITE, RED);
	Controller::gotoXY(28, 16);
	cout << "Please enter your name shortly, under 10 characters!";
	Menu::SetColor(WHITE, LIGHT_BLUE);
	Controller::gotoXY(35, 18);
	cout << "Enter your name:  ";
	getline(cin, a.playerName);
	Controller::gotoXY(35, 20);
	cout << "Enter your ID:  ";
	getline(cin, a.playerID);
	Controller::gotoXY(35, 22);
	cout << "Enter your class's name:  ";
	getline(cin, a.className);
}

void Game::printBoard() {
	Game::no_suggest = 3;
	Game::tmp_score = 0;
	Game::life = 3;
	Game::isPlaying = true;
	system("cls");
	//120 30
	// 10
	Game::cur_block.pX = 120 / 2 - (Game::width * 10) / 2;
	Game::cur_block.pY = 5;
	int x = Game::cur_block.pX - 1;
	int y = Game::cur_block.pY - 1;
	Menu::SetColor(WHITE, BLACK);

	for (int i = 0; i < Game::height; i++) {
		Controller::gotoXY(x, y);
		for (int j = 0; j < Game::width; j++) {
			Controller::gotoXY(x++, y);
			putchar(32);
			for (int k = 0; k < 9; k++) {
				Controller::gotoXY(x++, y);
				putchar(196);
			}
		}
		y++;
		x = Game::cur_block.pX - 1;

		for (int j = 0; j < Game::width; j++) {
			Controller::gotoXY(x++, y);
			putchar(179);
			for (int k = 0; k < 9; k++) {
				Controller::gotoXY(x++, y);
				putchar(32);
			}
		}
		putchar(179);
		y++;
		x = Game::cur_block.pX - 1;

		for (int j = 0; j < Game::width; j++) {
			Controller::gotoXY(x++, y);
			putchar(179);
			for (int k = 0; k < 9; k++) {
				Controller::gotoXY(x++, y);
				if (k == 4) {
					Menu::SetColor(WHITE, rand() % 7);
					putchar(Game::board[i][j]);
					Menu::SetColor(WHITE, BLACK);
				}
				else putchar(32);
			}
		}
		putchar(179);
		y++;
		x = Game::cur_block.pX - 1;

		for (int j = 0; j < Game::width; j++) {
			Controller::gotoXY(x++, y);
			putchar(179);
			for (int i = 0; i < 9; i++) {
				Controller::gotoXY(x++, y);
				putchar(32);
			}
		}
		putchar(179);
		y++;
		x = Game::cur_block.pX - 1;
		Sleep(100);
	}
	for (int j = 0; j < Game::width; j++) {
		Controller::gotoXY(x++, y);
		putchar(32);
		for (int k = 0; k < 9; k++) {
			Controller::gotoXY(x++, y);
			putchar(196);
		}
	}
	Menu::SetColor(WHITE, RED);
	Controller::gotoXY(102, 2);
	cout << "TIME: ";
}

bool Game::verify() {
	Game::Point firtBlock{ 0, 0 , -1, -1 };
	Game::Point secondBlock{ 0, 0, -1, -1 };
	char chr_test = Game::board[0][0];
	for (int i = 0; i < Game::height; i++) {
		for (int j = 0; j < Game::width; j++) {
			chr_test = Game::board[i][j];

			if (chr_test != _DELETE) {
				firtBlock.iX = j;
				firtBlock.iY = i;

				for (int u = i; u < Game::height; u++) {
					for (int v = 0; v < Game::width; v++) {
						if (u == i && v <= j) continue;

						chr_test = Game::board[u][v];

						if (chr_test != _DELETE) {
							secondBlock.iX = v;
							secondBlock.iY = u;

							if (Game::checkMatching(firtBlock, secondBlock, false)) {
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

void Game::printBackground() {
	Menu::SetColor(WHITE, GREEN);
	for (int i = 0; i < Game::height_bg; i++) {
		Controller::gotoXY(120 / 2 - (Game::width * 10) / 2, 5 + i);
		cout << Game::background[i] << endl;
		Sleep(150);
	}
}

void Game::reset() {
	if (Game::isPlaying == false) {
		a.score = Game::tmp_score;
		Game::displayStatus(true);
	}
	else {
		if (playAgain == false) {
			Controller::playSound(ERROR_SOUND);
			Controller::gotoXY(40, 3);
			Menu::SetColor(WHITE, RED);
			cout << "There are no more ways left!";
			Sleep(1500);

			Controller::gotoXY(40, 3);
			Menu::SetColor(WHITE, RED);
			cout << "                            ";

			srand((unsigned int)time(NULL));

			string chars = "";
			int n = 0;
			Game::Point temp{ 0, 0, 0, 0 };

			for (int i = 0; i < Game::height; i++) {
				for (int j = 0; j < Game::width; j++) {
					if (Game::board[i][j] != _DELETE) {
						chars += Game::board[i][j];
						n++;
					}
				}
			}

			Game::total_block = n;


			for (int i = 0; i < Game::height; i++) {
				for (int j = 0; j < Game::width; j++) {
					if (Game::board[i][j] != _DELETE) {
						int t = rand() % chars.size();

						Game::board[i][j] = chars[t];
						chars.erase(t, 1);

						temp.iX = j;
						temp.iY = i;
						temp.pX = (120 / 2 - (Game::width * 10) / 2) + j * 10;
						temp.pY = 5 + i * 4;

						Game::printBlock(WHITE, rand() % 7, temp);
					}
				}
			}


		}
		else {
			Game::deleteBoard();
			Game::genBoard();
			Game::cur_block.iX = 0;
			Game::cur_block.iY = 0;
			Game::printBoard();
			Game::printInterface();
			Game::controlPoint();
		}
	}
}

void Game::controlPoint() {
	Game::Point pre_block{ 1, 1 };

	Game::Point block_first{ -1, -1, -1, -1 };
	Game::Point block_second{ -1, -1, -1, -1 };

	bool isSelected = false;

	Game::printBlock(BRIGHT_WHITE, rand() % 7, Game::cur_block);
	int timeLeft = 0;
	time_t originalTime = time(0);
	if (Game::_mode == 0)
		timeLeft = 90;			// 90 giay
	else if (Game::_mode == 1)
		timeLeft = 150;			// 150 giay
	else if (Game::_mode == 2)
		timeLeft = 180;			// 180 giay

	while (Game::verify() == false) {
		Game::reset();
	}
	while (true) {
		Game::countdown(originalTime, timeLeft, overTime);
		if (overTime) {
			Controller::playSound(ERROR_SOUND);
			Controller::gotoXY(60, 3);
			Menu::SetColor(WHITE, RED);
			cout << "TIME OUT";
			Sleep(2000);
			Game::displayStatus(false);
		}
		if (_kbhit()) {
			pre_block = Game::cur_block;

			switch (Controller::getConsoleInput()) {
			case 1:
				Game::isPlaying = false;
				Game::displayStatus(false);
			case 2:
				Game::moveUp();
				break;
			case 3:
				Game::moveLeft();
				break;
			case 4:
				Game::moveRight();
				break;
			case 5:
				Game::moveDown();
				break;
			case 6:
				Controller::playSound(ENTER_SOUND);
				if (isSelected) {
					Game::selectBlock(block_second);
					Sleep(100);
					if (Game::board[block_second.iY][block_second.iX] == _DELETE ||
						(block_second.iX == block_first.iX && block_second.iY == block_first.iY)) {
						Controller::playSound(ERROR_SOUND);
					}
					else {
						if (Game::checkMatching(block_first, block_second, true)) {
							Game::printBlock(GREEN, BRIGHT_WHITE, block_first);
							Game::printBlock(GREEN, BRIGHT_WHITE, block_second);
							Controller::playSound(MATCH_SOUND);
							Sleep(200);

							if (Game::_mode == 2)
								Game::slideLeft(block_first, block_second);

							Game::deleteBlock(block_first);
							Game::deleteBlock(block_second);
							Game::total_block -= 2;
							if (Game::total_block == 0) {
								Game::printBackground();
								Game::isPlaying = false;
							}
							while (Game::verify() == false) {
								Sleep(2000);
								Game::reset();
							}
						}
						else {
							Game::printBlock(RED, BRIGHT_WHITE, block_first);
							Game::printBlock(RED, BRIGHT_WHITE, block_second);
							Controller::playSound(ERROR_SOUND);
							Game::life -= 1;
							Game::printInterface();
							Controller::gotoXY(37, 2);
							Menu::SetColor(WHITE, RED);
							cout << "Wrong";
							Sleep(200);
							if (Game::life == 0) {
								Controller::gotoXY(50, 3);
								Menu::SetColor(WHITE, RED);
								Controller::playSound(ERROR_SOUND);
								cout << "Your turn is over";
								Sleep(1000);
								Controller::gotoXY(50, 3);
								Menu::SetColor(WHITE, WHITE);
								cout << "                  ";
								Game::displayStatus(false);
							}
						}

						Game::printBlock(WHITE, RED, block_first);
						block_first.iX = -1;
						block_first.iY = -1;
						block_first.pX = -1;
						block_first.pY = -1;

						block_second.iX = -1;
						block_second.iY = -1;
						block_second.pX = -1;
						block_second.pY = -1;
						isSelected = false;
					}
				}
				else {
					Game::selectBlock(block_first);

					if (Game::board[block_first.iY][block_first.iX] == _DELETE) {
						Game::printBlock(BRIGHT_WHITE, BRIGHT_WHITE, block_first);
						block_first.iX = -1;
						block_first.iY = -1;
						block_first.pX = -1;
						block_first.pY = -1;
						Controller::playSound(ERROR_SOUND);
					}
					else {
						Controller::playSound(ENTER_SOUND);
						isSelected = true;
					}
				}
				break;
			case 7:
				Menu::helpScreen();
				break;
			case 8:
				Controller::playSound(ENTER_SOUND);
				if (Game::tmp_score >= 2) {
					if (Game::no_suggest > 0) {
						Game::no_suggest--;
						Game::moveSuggest();
						Game::tmp_score -= 2;
						Game::printInterface();
					}
					else {
						Controller::gotoXY(40, 3);
						Menu::SetColor(WHITE, RED);
						Controller::playSound(ERROR_SOUND);
						cout << "You have run out of suggestions";
						Sleep(1000);
						Controller::gotoXY(40, 3);
						Menu::SetColor(WHITE, WHITE);
						cout << "                                 ";
					}
				}
				else {
					Controller::gotoXY(40, 3);
					Menu::SetColor(WHITE, RED);
					Controller::playSound(ERROR_SOUND);
					cout << "You don't have enough points to use suggestion";
					Sleep(1000);
					Controller::gotoXY(40, 3);
					Menu::SetColor(WHITE, WHITE);
					cout << "                                                ";
				}
				break;
			default:
				Controller::playSound(ERROR_SOUND);
				break;
			}

			if (pre_block.iX == block_first.iX && pre_block.iY == block_first.iY) {
				Game::printBlock(BRIGHT_WHITE, rand() % 7, block_first);
			}
			else {
				if (isalpha(Game::board[pre_block.iY][pre_block.iX])) {
					Game::printBlock(WHITE, rand() % 7, pre_block);
				}
				else Game::printBlock(WHITE, RED, pre_block);
			}
			if (Game::cur_block.iX == block_first.iX && Game::cur_block.iY == block_first.iY) {
				Game::printBlock(RED, BLACK, block_first);
			}
			else {
				Game::printBlock(BRIGHT_WHITE, RED, Game::cur_block);
				if (Game::board[Game::cur_block.iY][Game::cur_block.iX] == _DELETE) {
					//Menu::SetColor(BRIGHT_WHITE, GREEN);
					Game::displayBackground(cur_block);
				}
			}
		}
	}

}

int dx[4] = { 0, -1, 1, 0 };
int dy[4] = { -1, 0, 0, 1 };

void Game::moveRight() {
	if (Game::cur_block.iX == Game::width - 1) {
		Game::cur_block.iX = 0;
		Game::cur_block.pX -= (Game::width - 1) * 10;
	}
	else {
		Game::cur_block.iX++;
		Game::cur_block.pX += 10;
	}
}

void Game::moveLeft() {
	if (Game::cur_block.iX == 0) {
		Game::cur_block.iX = Game::width - 1;
		Game::cur_block.pX += (Game::width - 1) * 10;
	}
	else {
		Game::cur_block.iX--;
		Game::cur_block.pX -= 10;
	}
}

void Game::moveUp() {
	if (Game::cur_block.iY == 0) {
		Game::cur_block.iY = Game::height - 1;
		Game::cur_block.pY += (Game::height - 1) * 4;
	}
	else {
		Game::cur_block.iY--;
		Game::cur_block.pY -= 4;
	}
}

void Game::moveDown() {
	if (Game::cur_block.iY == Game::height - 1) {
		Game::cur_block.iY = 0;
		Game::cur_block.pY -= (Game::height - 1) * 4;
	}
	else {
		Game::cur_block.iY++;
		Game::cur_block.pY += 4;
	}
}

void Game::printBlock(int background, int color, Point block) {
	Menu::SetColor(background, color);
	Controller::gotoXY(block.pX, block.pY);
	cout << "         ";
	Controller::gotoXY(block.pX, block.pY + 1);
	cout << "    " << Game::board[block.iY][block.iX] << "    ";
	Controller::gotoXY(block.pX, block.pY + 2);
	cout << "         ";
	if (Game::board[block.iY][block.iX] == _DELETE) {
		Game::displayBackground(block);
	}
}

void Game::deleteBlock(Point block) {
	Game::board[block.iY][block.iX] = _DELETE;
	Game::printBlock(WHITE, WHITE, block);
	for (int i = 0; i < 4; i++) {
		int iX = block.iX + dx[i];
		int iY = block.iY + dy[i];
		int pX = block.pX + dx[i] * 10;
		int pY = block.pY + dy[i] * 4;
		if (iX == -1) {
			for (int j = 0; j < 3; j++) {
				Controller::gotoXY(block.pX - 1, block.pY + j);
				putchar(32);
			}
		}
		else if (iX == Game::width) {
			for (int j = 0; j < 3; j++) {
				Controller::gotoXY(block.pX + 9, block.pY + j);
				putchar(32);
			}
		}
		if (iY == -1) {
			for (int j = 0; j < 11; j++) {
				Controller::gotoXY(block.pX - 1 + j, block.pY - 1);
				putchar(32);
			}
		}
		else if (iY == Game::height) {
			for (int j = 0; j < 11; j++) {
				Controller::gotoXY(block.pX - 1 + j, block.pY + 3);
				putchar(32);
			}
		}
		if (iX >= 0 && iX < Game::width && iY >= 0 && iY < Game::height && Game::board[iY][iX] == _DELETE) {
			if (iX < block.iX) {
				for (int j = 0; j < 3; j++) {
					Controller::gotoXY(block.pX - 1, block.pY + j);
					putchar(32);
				}
			}
			if (iX > block.iX) {
				for (int j = 0; j < 3; j++) {
					Controller::gotoXY(block.pX + 9, block.pY + j);
					putchar(32);
				}
			}
			if (iY < block.iY) {
				for (int j = 0; j < 11; j++) {
					Controller::gotoXY(block.pX - 1 + j, block.pY - 1);
					putchar(32);
				}
			}
			if (iY > block.iY) {
				for (int j = 0; j < 11; j++) {
					Controller::gotoXY(block.pX - 1 + j, block.pY + 3);
					putchar(32);
				}
			}
		}
	}
	Menu::SetColor(WHITE, RED);
	Game::displayBackground(block);
}

void Game::selectBlock(Point& block) {
	block.iX = Game::cur_block.iX;
	block.iY = Game::cur_block.iY;

	block.pX = Game::cur_block.pX;
	block.pY = Game::cur_block.pY;

	if (Game::board[block.iY][block.iX] != _DELETE)
		Game::printBlock(BRIGHT_WHITE, rand() % 7, block);
}

bool Game::checkMatching(Point ptr1, Point ptr2, bool isPublic) {
	if (Game::board[ptr1.iY][ptr1.iX] == Game::board[ptr2.iY][ptr2.iX]) {
		bool I_case = Game::IMatching(ptr1, ptr2, isPublic);
		if (I_case) {
			if (isPublic) {
				Game::tmp_score += 1;
				Controller::gotoXY(100, 10);
				Menu::SetColor(WHITE, BLACK);
				Game::printInterface();
				Controller::gotoXY(37, 2);
				Menu::SetColor(WHITE, GREEN);
				cout << "I Matching";
			}
			return true;
		}
		bool L_case = Game::LMatching(ptr1, ptr2, isPublic);
		if (L_case) {
			if (isPublic) {
				Game::tmp_score += 2;
				Controller::gotoXY(100, 10);
				Menu::SetColor(WHITE, BLACK);
				Game::printInterface();
				Controller::gotoXY(37, 2);
				Menu::SetColor(WHITE, GREEN);
				cout << "L Matching";
			}
			return true;
		}
		bool Z_case = Game::ZMatching(ptr1, ptr2, isPublic);
		if (Z_case) {
			if (isPublic) {
				Game::tmp_score += 3;
				Controller::gotoXY(100, 10);
				Menu::SetColor(WHITE, BLACK);
				Game::printInterface();
				Controller::gotoXY(37, 2);
				Menu::SetColor(WHITE, GREEN);
				cout << "Z Matching";
			}
			return true;
		}
		bool U_case = Game::UMatching(ptr1, ptr2, isPublic);
		if (U_case) {
			if (isPublic) {
				Game::tmp_score += 4;
				Controller::gotoXY(100, 10);
				Menu::SetColor(WHITE, BLACK);
				Game::printInterface();
				Controller::gotoXY(37, 2);
				Menu::SetColor(WHITE, GREEN);
				cout << "U Matching";
			}
			return true;
		}
	}
	if (isPublic) {
		Game::tmp_score -= 2;
	}

	return false;
}

void Game::slideLeft(Point& firstBlock, Point& secondBlock) {
	Menu::SetColor(WHITE, BLACK);
	for (int i = 0; i < 9; i++) {
		Controller::gotoXY(firstBlock.pX + i, firstBlock.pY - 1);
		putchar(196);
		Controller::gotoXY(firstBlock.pX + i, firstBlock.pY + 3);
		putchar(196);
	}
	for (int i = 0; i < 3; i++) {
		Controller::gotoXY(firstBlock.pX - 1, firstBlock.pY + i);
		putchar(179);
		Controller::gotoXY(firstBlock.pX + 9, firstBlock.pY + i);
		putchar(179);
	}
	// -------
	for (int i = 0; i < 9; i++) {
		Controller::gotoXY(secondBlock.pX + i, secondBlock.pY - 1);
		putchar(196);
		Controller::gotoXY(secondBlock.pX + i, secondBlock.pY + 3);
		putchar(196);
	}
	for (int i = 0; i < 3; i++) {
		Controller::gotoXY(secondBlock.pX - 1, secondBlock.pY + i);
		putchar(179);
		Controller::gotoXY(secondBlock.pX + 9, secondBlock.pY + i);
		putchar(179);
	}

	if (firstBlock.iY != secondBlock.iY) {
		int n;
		for (n = 0; n < Game::width; n++) {
			if (Game::board[firstBlock.iY][n] == _DELETE) break;
		}
		for (int i = firstBlock.iX; i < n - 1; i++) {
			Game::board[firstBlock.iY][i] = Game::board[firstBlock.iY][i + 1];
			Game::printBlock(WHITE, rand() % 7, firstBlock);
			firstBlock.iX++;
			firstBlock.pX += 10;
		}
		// ---------
		for (n = 0; n < Game::width; n++) {
			if (Game::board[secondBlock.iY][n] == _DELETE) break;
		}
		for (int i = secondBlock.iX; i < n - 1; i++) {
			Game::board[secondBlock.iY][i] = Game::board[secondBlock.iY][i + 1];
			Game::printBlock(WHITE, rand() % 7, secondBlock);
			secondBlock.iX++;
			secondBlock.pX += 10;
		}
	}
	else {
		if (firstBlock.iX > secondBlock.iX) swap(firstBlock, secondBlock);
		int n;
		for (n = secondBlock.iX; n < Game::width; n++) {
			if (Game::board[secondBlock.iY][n] == _DELETE) break;
		}
		for (int i = secondBlock.iX; i < n - 1; i++) {
			Game::board[secondBlock.iY][i] = Game::board[secondBlock.iY][i + 1];
			Game::printBlock(WHITE, rand() % 7, secondBlock);
			secondBlock.iX++;
			secondBlock.pX += 10;
		}
		Game::board[secondBlock.iY][secondBlock.iX] = _DELETE;
		// -------
		for (n = 0; n < Game::width; n++) {
			if (Game::board[firstBlock.iY][n] == _DELETE) break;
		}
		for (int i = firstBlock.iX; i < n - 1; i++) {
			Game::board[firstBlock.iY][i] = Game::board[firstBlock.iY][i + 1];
			Game::printBlock(WHITE, rand() % 7, firstBlock);
			firstBlock.iX++;
			firstBlock.pX += 10;
		}
	}
}

void Game::deleteBoard() {
	for (int i = 0; i < Game::height; i++)
		delete[] Game::board[i];
	delete[] Game::board;
}

void Game::moveSuggest() {
	Game::Point firstBlock{ 0, 0 , -1, -1 };
	Game::Point secondBlock{ 0, 0, -1, -1 };
	char chr_test = Game::board[0][0];
	for (int i = 0; i < Game::height; i++) {
		for (int j = 0; j < Game::width; j++) {
			chr_test = Game::board[i][j];

			if (chr_test != _DELETE) {
				firstBlock.iX = j;
				firstBlock.iY = i;

				for (int u = i; u < Game::height; u++) {
					for (int v = 0; v < Game::width; v++) {
						if (u == i && v <= j) continue;

						chr_test = Game::board[u][v];

						if (chr_test != _DELETE) {
							secondBlock.iX = v;
							secondBlock.iY = u;

							if (Game::checkMatching(firstBlock, secondBlock, false)) {
								int x = 120 / 2 - (Game::width * 10) / 2;
								int y = 5;

								firstBlock.pX = x + firstBlock.iX * 10;
								firstBlock.pY = y + firstBlock.iY * 4;

								secondBlock.pX = x + secondBlock.iX * 10;
								secondBlock.pY = y + secondBlock.iY * 4;

								Game::printBlock(LIGHT_PURPLE, BLACK, firstBlock);
								Game::printBlock(LIGHT_PURPLE, BLACK, secondBlock);

								Sleep(500);

								Game::printBlock(WHITE, rand() % 7, firstBlock);
								Game::printBlock(WHITE, rand() % 7, secondBlock);

								return;
							}
						}
					}
				}
			}
		}
	}
	return;
}

void Game::drawIline(Point first_block, Point second_block) {
	if (first_block.iX + first_block.iY * Game::width > second_block.iX + second_block.iY * Game::width) {
		Point temp = first_block;
		first_block = second_block;
		second_block = temp;
	}

	Menu::SetColor(GREEN, WHITE);
	if (first_block.iY == second_block.iY) {
		int x1 = first_block.pX + 5;
		int x2 = second_block.pX + 4;
		int y = first_block.pY + 1;
		while (x1 < x2) {
			Controller::gotoXY(x1++, y);
			putchar(196);
		}
	}
	else {
		int y1 = first_block.pY + 2;
		int y2 = second_block.pY + 1;
		int x = first_block.pX + 4;
		while (y1 < y2) {
			Controller::gotoXY(x, y1++);
			putchar(179);
		}
	}
}

void Game::drawLline(Point first_block, Point second_block, Point Lcorner) {
	Menu::SetColor(RED, WHITE);
	Game::drawIline(first_block, Lcorner);
	Game::drawIline(Lcorner, second_block);
	Controller::gotoXY(Lcorner.pX + 4, Lcorner.pY + 1);
	if (Lcorner.iY < first_block.iY || Lcorner.iY < second_block.iY) {
		if (Lcorner.iX < first_block.iX || Lcorner.iX < second_block.iX)
			putchar(218);
		else if (Lcorner.iX > first_block.iX || Lcorner.iX > second_block.iX)
			putchar(191);
	}
	else if (Lcorner.iY > first_block.iY || Lcorner.iY > second_block.iY) {
		if (Lcorner.iX < first_block.iX || Lcorner.iX < second_block.iX)
			putchar(192);
		else if (Lcorner.iX > first_block.iX || Lcorner.iX > second_block.iX)
			putchar(217);
	}
}

void Game::drawZline(Point first_block, Point second_block, Point Lcorner1, Point Lcorner2) {
	Menu::SetColor(RED, WHITE);
	Game::drawIline(first_block, Lcorner1);
	Game::drawIline(Lcorner1, Lcorner2);
	Game::drawIline(Lcorner2, second_block);

	Controller::gotoXY(Lcorner1.pX + 4, Lcorner1.pY + 1);
	if (Lcorner1.iY < first_block.iY || Lcorner1.iY < Lcorner2.iY) {
		if (Lcorner1.iX < first_block.iX || Lcorner1.iX < Lcorner2.iX)
			putchar(218);
		else if (Lcorner1.iX > first_block.iX || Lcorner1.iX > Lcorner2.iX)
			putchar(191);
	}
	else if (Lcorner1.iY > first_block.iY || Lcorner1.iY > Lcorner2.iY) {
		if (Lcorner1.iX < first_block.iX || Lcorner1.iX < Lcorner2.iX)
			putchar(192);
		else if (Lcorner1.iX > first_block.iX || Lcorner1.iX > Lcorner2.iX)
			putchar(217);
	}
	Controller::gotoXY(Lcorner2.pX + 4, Lcorner2.pY + 1);
	if (Lcorner2.iY < Lcorner1.iY || Lcorner2.iY < second_block.iY) {
		if (Lcorner2.iX < Lcorner1.iX || Lcorner2.iX < second_block.iX)
			putchar(218);
		else if (Lcorner2.iX > Lcorner1.iX || Lcorner2.iX > second_block.iX)
			putchar(191);
	}
	else if (Lcorner2.iY > Lcorner1.iY || Lcorner2.iY > second_block.iY) {
		if (Lcorner2.iX < Lcorner1.iX || Lcorner2.iX < second_block.iX)
			putchar(192);
		else if (Lcorner2.iX > Lcorner1.iX || Lcorner2.iX > second_block.iX)
			putchar(217);
	}
}

void Game::drawUline(Point first_block, Point second_block, Point Lcorner1, Point Lcorner2) {
	Menu::SetColor(RED, WHITE);
	Game::drawIline(first_block, Lcorner1);
	Game::drawIline(Lcorner1, Lcorner2);
	Game::drawIline(Lcorner2, second_block);

	Controller::gotoXY(Lcorner1.pX + 4, Lcorner1.pY + 1);
	if (Lcorner1.iY < first_block.iY || Lcorner1.iY < Lcorner2.iY) {
		if (Lcorner1.iX < first_block.iX || Lcorner1.iX < Lcorner2.iX)
			putchar(218);
		else if (Lcorner1.iX > first_block.iX || Lcorner1.iX > Lcorner2.iX)
			putchar(191);
	}
	else if (Lcorner1.iY > first_block.iY || Lcorner1.iY > Lcorner2.iY) {
		if (Lcorner1.iX < first_block.iX || Lcorner1.iX < Lcorner2.iX)
			putchar(192);
		else if (Lcorner1.iX > first_block.iX || Lcorner1.iX > Lcorner2.iX)
			putchar(217);
	}

	Controller::gotoXY(Lcorner2.pX + 4, Lcorner2.pY + 1);
	if (Lcorner2.iY < Lcorner1.iY || Lcorner2.iY < second_block.iY) {
		if (Lcorner2.iX < Lcorner1.iX || Lcorner2.iX < second_block.iX)
			putchar(218);
		else if (Lcorner2.iX > Lcorner1.iX || Lcorner2.iX > second_block.iX)
			putchar(191);
	}
	else if (Lcorner2.iY > Lcorner1.iY || Lcorner2.iY > second_block.iY) {
		if (Lcorner2.iX < Lcorner1.iX || Lcorner2.iX < second_block.iX)
			putchar(192);
		else if (Lcorner2.iX > Lcorner1.iX || Lcorner2.iX > second_block.iX)
			putchar(217);
	}
}

void Game::deleteIline(Point first_block, Point second_block) {
	if (first_block.iX + first_block.iY * Game::width > second_block.iX + second_block.iY * Game::width) {
		Point temp = first_block;
		first_block = second_block;
		second_block = temp;
	}
	Menu::SetColor(WHITE, RED);
	if (first_block.iY == second_block.iY) {
		int x1 = first_block.pX + 5;
		int x2 = second_block.pX + 4;
		int y = first_block.pY + 1;
		int count = 6;
		while (x1 < x2) {
			Controller::gotoXY(x1++, y);
			/*if (count == 10) {
				putchar(179);
				count = 0;
			}
			else {
				//putchar(32);
				cout << background[y - 5][x1 - (120 / 2 - Game::width * 10 / 2)];
			}
			count++;
			*/
			cout << background[y - 5][x1 - 1 - (120 / 2 - Game::width * 10 / 2)];
		}
	}
	else {
		int y1 = first_block.pY + 2;
		int y2 = second_block.pY + 1;
		int x = first_block.pX + 4;
		int count = 3;
		while (y1 < y2) {
			Controller::gotoXY(x, y1++);
			/*if (count == 4) {
				putchar(196);
				count = 0;
			}
			else {
				//putchar(32);
				cout << background[y1 - 5][x - (120 / 2 - Game::width * 10 / 2)];
			}
			count++;
			*/
			cout << background[y1 - 6][x - (120 / 2 - Game::width * 10 / 2)];
		}
	}
}

void Game::deleteLline(Point first_block, Point second_block, Point Lcorner) {
	Menu::SetColor(WHITE, WHITE);
	Game::deleteIline(first_block, Lcorner);
	Game::deleteIline(Lcorner, second_block);
	Controller::gotoXY(Lcorner.pX + 4, Lcorner.pY + 1);
	//putchar(32);
	cout << background[Lcorner.pY - 4][Lcorner.pX + 4 - (120 / 2 - Game::width * 10 / 2)];
}

void Game::deleteZline(Point first_block, Point second_block, Point Lcorner1, Point Lcorner2) {
	Menu::SetColor(WHITE, WHITE);
	Game::deleteIline(first_block, Lcorner1);
	Game::deleteIline(Lcorner1, Lcorner2);
	Game::deleteIline(Lcorner2, second_block);

	Controller::gotoXY(Lcorner1.pX + 4, Lcorner1.pY + 1);
	//putchar(32);
	cout << background[Lcorner1.pY - 4][Lcorner1.pX + 4 - (120 / 2 - Game::width * 10 / 2)];
	Controller::gotoXY(Lcorner2.pX + 4, Lcorner2.pY + 1);
	//putchar(32);
	cout << background[Lcorner2.pY - 4][Lcorner2.pX + 4 - (120 / 2 - Game::width * 10 / 2)];
}

void Game::deleteUline(Point first_block, Point second_block, Point Lcorner1, Point Lcorner2) {
	Menu::SetColor(WHITE, BLACK);
	Game::deleteIline(first_block, Lcorner1);
	Game::deleteIline(Lcorner1, Lcorner2);
	Game::deleteIline(Lcorner2, second_block);

	Controller::gotoXY(Lcorner1.pX + 4, Lcorner1.pY + 1);
	//putchar(32);
	cout << background[Lcorner1.pY - 4][Lcorner1.pX + 4 - (120 / 2 - Game::width * 10 / 2)];
	Controller::gotoXY(Lcorner2.pX + 4, Lcorner2.pY + 1);
	//putchar(32);
	cout << background[Lcorner2.pY - 4][Lcorner2.pX + 4 - (120 / 2 - Game::width * 10 / 2)];
}

bool Game::IMatching(Point ptr1, Point ptr2, bool isPublic) {
	if (ptr1.iX != ptr2.iX && ptr1.iY != ptr2.iY) return false;
	if (ptr1.iX + ptr1.iY * Game::width > ptr2.iX + ptr2.iY * Game::width) {
		Point temp = ptr1;
		ptr1 = ptr2;
		ptr2 = temp;
	}
	if (ptr1.iX == ptr2.iX) {
		int _y1 = ptr1.iY;
		while (true) {
			_y1++;
			if (_y1 == ptr2.iY) break;
			if (Game::board[_y1][ptr1.iX] != _DELETE) return false;
		}
		if (isPublic) {
			Game::drawIline(ptr1, ptr2);
			Sleep(300);
			Game::deleteIline(ptr1, ptr2);
		}
		return true;
	}
	else {
		int _x1 = ptr1.iX;
		while (true) {
			_x1++;
			if (_x1 == ptr2.iX) break;
			if (Game::board[ptr1.iY][_x1] != _DELETE) return false;
		}
		if (isPublic) {
			Game::drawIline(ptr1, ptr2);
			Sleep(300);
			Game::deleteIline(ptr1, ptr2);
		}
		return true;
	}
}

bool Game::LMatching(Point ptr1, Point ptr2, bool isPublic) {
	Game::Point ptr3{ ptr1.iX, ptr2.iY , ptr1.pX, ptr2.pY };
	Game::Point ptr4{ ptr2.iX, ptr1.iY , ptr2.pX, ptr1.pY };
	bool case1 = false;
	bool case2 = false;
	if (Game::board[ptr3.iY][ptr3.iX] == _DELETE) {
		case1 = Game::IMatching(ptr1, ptr3, false) && Game::IMatching(ptr3, ptr2, false);
	}
	if (Game::board[ptr4.iY][ptr4.iX] == _DELETE) {
		case2 = Game::IMatching(ptr1, ptr4, false) && Game::IMatching(ptr4, ptr2, false);
	}
	if (isPublic && case1) {
		Game::drawLline(ptr1, ptr2, ptr3);
		Sleep(300);
		Game::deleteLline(ptr1, ptr2, ptr3);
	}
	else if (isPublic && case2) {
		Game::drawLline(ptr1, ptr2, ptr4);
		Sleep(300);
		Game::deleteLline(ptr1, ptr2, ptr4);
	}

	return case1 || case2;
}

bool Game::ZMatching(Point ptr1, Point ptr2, bool isPublic) {
	if (ptr1.iX == ptr2.iX || ptr1.iY == ptr2.iY) return false;

	if (ptr1.iX + ptr1.iY * Game::width > ptr2.iX + ptr2.iY * Game::width) {
		Point temp = ptr1;
		ptr1 = ptr2;
		ptr2 = temp;
	}

	Game::Point check_pt1 = ptr1;
	Game::Point check_pt2 = ptr2;

	if (ptr1.iX < ptr2.iX) {
		while (check_pt1.iX < ptr2.iX - 1) {
			if (check_pt1.iX == Game::width) break;
			check_pt1.iX++;
			check_pt1.pX += 10;
			check_pt2.iX = check_pt1.iX;
			check_pt2.pX = check_pt1.pX;
			if (Game::board[check_pt1.iY][check_pt1.iX] != _DELETE) break;
			if (Game::board[check_pt2.iY][check_pt2.iX] != _DELETE) continue;
			if (Game::IMatching(check_pt1, check_pt2, false) && Game::IMatching(check_pt2, ptr2, false)) {
				if (isPublic) {
					Game::drawZline(ptr1, ptr2, check_pt1, check_pt2);
					Sleep(300);
					Game::deleteZline(ptr1, ptr2, check_pt1, check_pt2);
				}
				return true;
			}
		}
	}
	else {
		check_pt1 = ptr1;
		check_pt2 = ptr2;
		while (check_pt1.iX > ptr2.iX + 1) {
			if (check_pt1.iX == 0) break;
			check_pt1.iX--;
			check_pt1.pX -= 10;
			check_pt2.iX = check_pt1.iX;
			check_pt2.pX = check_pt1.pX;
			if (Game::board[check_pt1.iY][check_pt1.iX] != _DELETE) break;
			if (Game::board[check_pt2.iY][check_pt2.iX] != _DELETE) continue;
			if (Game::IMatching(check_pt1, check_pt2, false) && Game::IMatching(check_pt2, ptr2, false)) {
				if (isPublic) {
					Game::drawZline(ptr1, ptr2, check_pt1, check_pt2);
					Sleep(300);
					Game::deleteZline(ptr1, ptr2, check_pt1, check_pt2);
				}
				return true;
			}
		}
	}
	check_pt1 = ptr1;
	check_pt2 = ptr2;
	while (check_pt1.iY < ptr2.iY - 1) {
		if (check_pt1.iY == Game::height - 1) break;
		check_pt1.iY++;
		check_pt1.pY += 4;
		check_pt2.iY = check_pt1.iY;
		check_pt2.pY = check_pt1.pY;
		if (Game::board[check_pt1.iY][check_pt1.iX] != _DELETE) break;
		if (Game::board[check_pt2.iY][check_pt2.iX] != _DELETE) continue;
		if (Game::IMatching(check_pt1, check_pt2, false) && Game::IMatching(check_pt2, ptr2, false)) {
			if (isPublic) {
				Game::drawZline(ptr1, ptr2, check_pt1, check_pt2);
				Sleep(300);
				Game::deleteZline(ptr1, ptr2, check_pt1, check_pt2);
			}
			return true;
		}
	}

	return false;
}

bool Game::UMatching(Point ptr1, Point ptr2, bool isPublic) {
	if (ptr1.iX == ptr2.iX && (ptr1.iX == 0 || ptr1.iX == Game::width - 1)) {
		Sleep(300);
		return true;
	}
	if (ptr1.iY == ptr2.iY && (ptr1.iY == 0 || ptr1.iY == Game::height - 1)) {
		Sleep(300);
		return true;
	}

	if (ptr1.iX + ptr1.iY * Game::width > ptr2.iX + ptr2.iY * Game::width) {
		Game::Point temp = ptr1;
		ptr1 = ptr2;
		ptr2 = temp;
	}

	// di qua trai
	bool check = true;
	Game::Point check_pt1 = ptr1;
	Game::Point check_pt2 = ptr2;
	if (check_pt1.iX > ptr2.iX) {
		check_pt1.iX = ptr2.iX;
		check_pt1.pX = ptr2.pX;
		if (Game::IMatching(check_pt1, ptr1, false) == false || Game::board[check_pt1.iY][check_pt1.iX] != _DELETE)
			check = false;
	}
	if (check) {
		while (check_pt1.iX != 0) {
			check_pt1.iX--;
			check_pt1.pX -= 10;
			check_pt2.iX = check_pt1.iX;
			check_pt2.pX = check_pt1.pX;
			if (Game::board[check_pt1.iY][check_pt1.iX] != _DELETE || Game::board[check_pt2.iY][check_pt2.iX] != _DELETE) {
				check = false;
				break;
			}
			if (Game::IMatching(check_pt1, check_pt2, false) && Game::IMatching(check_pt2, ptr2, false)) {
				if (isPublic) {
					Game::drawUline(ptr1, ptr2, check_pt1, check_pt2);
					Sleep(300);
					Game::deleteUline(ptr1, ptr2, check_pt1, check_pt2);
				}
				return true;
			}
		}
		if (check_pt1.iX == 0 && check) {
			check_pt1.iY = ptr2.iY;
			if (check_pt1.iX == ptr2.iX && check_pt1.iY == ptr2.iY) {
				Sleep(300);
				return true;
			}
			if (Game::board[check_pt1.iY][check_pt1.iX] == _DELETE && Game::IMatching(check_pt1, ptr2, false)) {
				Sleep(300);
				return true;
			}
		}
	}

	// di qua phai
	check = true;
	check_pt1 = ptr1;
	check_pt2 = ptr2;
	if (check_pt1.iX < ptr2.iX) {
		check_pt1.iX = ptr2.iX;
		check_pt1.pX = ptr2.pX;
		if (Game::IMatching(check_pt1, ptr1, false) == false || Game::board[check_pt1.iY][check_pt1.iX] != _DELETE)
			check = false;
	}
	if (check) {
		while (check_pt1.iX != Game::width - 1) {
			check_pt1.iX++;
			check_pt1.pX += 10;
			check_pt2.iX = check_pt1.iX;
			check_pt2.pX = check_pt1.pX;
			if (Game::board[check_pt1.iY][check_pt1.iX] != _DELETE || Game::board[check_pt2.iY][check_pt2.iX] != _DELETE) {
				check = false;
				break;
			}
			if (Game::IMatching(check_pt1, check_pt2, false) && Game::IMatching(check_pt2, ptr2, false)) {
				if (isPublic) {
					Game::drawUline(ptr1, ptr2, check_pt1, check_pt2);
					Sleep(300);
					Game::deleteUline(ptr1, ptr2, check_pt1, check_pt2);
				}
				return true;
			}
		}
		if (check_pt1.iX == Game::width - 1 && check) {
			check_pt1.iY = ptr2.iY;
			if (check_pt1.iX == ptr2.iX && check_pt1.iY == ptr2.iY) {
				Sleep(300);
				return true;
			}
			if (Game::board[check_pt1.iY][check_pt1.iX] == _DELETE && Game::IMatching(check_pt1, ptr2, false)) {
				Sleep(300);
				return true;
			}
		}
	}

	// di len tren
	Controller::gotoXY(2, 2);

	check = true;
	check_pt1 = ptr1;
	check_pt2 = ptr2;
	if (check_pt1.iY > ptr2.iY) {
		check_pt1.iY = ptr2.iY;
		check_pt1.pY = ptr2.pY;
		if (Game::IMatching(check_pt1, ptr1, false) == false || Game::board[check_pt1.iY][check_pt1.iX] != _DELETE)
			check = false;
	}
	if (check) {
		while (check_pt1.iY != 0) {
			check_pt1.iY--;
			check_pt1.pY -= 4;
			check_pt2.iY = check_pt1.iY;
			check_pt2.pY = check_pt1.pY;

			if (Game::board[check_pt1.iY][check_pt1.iX] != _DELETE || Game::board[check_pt2.iY][check_pt2.iX] != _DELETE) {
				check = false;
				break;
			}

			if (Game::IMatching(check_pt1, check_pt2, false) && Game::IMatching(check_pt2, ptr2, false)) {
				if (isPublic) {
					Game::drawUline(ptr1, ptr2, check_pt1, check_pt2);
					Sleep(300);
					Game::deleteUline(ptr1, ptr2, check_pt1, check_pt2);
				}
				return true;
			}
		}
		if (check_pt1.iY == 0 && check) {
			check_pt1.iX = ptr2.iX;
			if (check_pt1.iX == ptr2.iX && check_pt1.iY == ptr2.iY) {
				Sleep(300);
				return true;
			}
			if (Game::board[check_pt1.iY][check_pt1.iX] == _DELETE && Game::IMatching(check_pt1, ptr2, false)) {
				Sleep(300);
				return true;
			}
		}
	}

	// di xuong duoi
	check = true;
	check_pt1 = ptr1;
	check_pt2 = ptr2;
	if (check_pt1.iY < ptr2.iY) {
		check_pt1.iY = ptr2.iY;
		check_pt1.pY = ptr2.pY;
		if (Game::IMatching(check_pt1, ptr1, false) == false || Game::board[check_pt1.iY][check_pt1.iX] != _DELETE)
			check = false;
	}
	if (check) {
		while (check_pt1.iY != Game::height - 1) {
			check_pt1.iY++;
			check_pt1.pY += 4;
			check_pt2.iY = check_pt1.iY;
			check_pt2.pY = check_pt1.pY;
			if (Game::board[check_pt1.iY][check_pt1.iX] != _DELETE || Game::board[check_pt2.iY][check_pt2.iX] != _DELETE) {
				check = false;
				break;
			}
			if (Game::IMatching(check_pt1, check_pt2, false) && Game::IMatching(check_pt2, ptr2, false)) {
				if (isPublic) {
					Game::drawUline(ptr1, ptr2, check_pt1, check_pt2);
					Sleep(300);
					Game::deleteUline(ptr1, ptr2, check_pt1, check_pt2);
				}
				return true;
			}
		}
		if (check_pt1.iY == Game::height - 1 && check) {
			check_pt1.iX = ptr2.iX;
			if (check_pt1.iX == ptr2.iX && check_pt1.iY == ptr2.iY) {
				Sleep(300);
				return true;
			}
			if (Game::board[check_pt1.iY][check_pt1.iX] == _DELETE && Game::IMatching(check_pt1, ptr2, false)) {
				Sleep(300);
				return true;
			}
		}
	}

	return false;
}

void Game::countdown(time_t originalTime, int timeLeft, bool& overTime) {
	time_t nowTime = time(0);
	timeLeft -= (int)difftime(nowTime, originalTime);
	if (timeLeft == 0)
		overTime = true;
	Controller::gotoXY(108, 2);
	Menu::SetColor(WHITE, RED);
	cout << setw(3) << setfill(' ') << timeLeft << "s";
}