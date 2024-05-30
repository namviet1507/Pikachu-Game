#include "Struct.h"
#include "Game.h"
#include "Controller.h"
#pragma comment(lib, "winmm.lib")

void Menu::SetColor(int background_color, int text_color) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int color_code = background_color * 16 + text_color;
	SetConsoleTextAttribute(h, color_code);
}

void Menu::printRectangle(int left, int top, int width, int height)
{
	Controller::gotoXY(left, top);
	putchar(218);
	for (int i = 0; i < width; i++) {
		putchar(196);
	}
	putchar(191);
	int i = 0;
	for (; i < height; i++)
	{
		Controller::gotoXY(left, top + i + 1);
		putchar(179);
		Controller::gotoXY(left + width + 1, top + i + 1);
		putchar(179);
	}

	Controller::gotoXY(left, top + i);
	putchar(192);
	for (i = 0; i < width; i++)
		putchar(196);
	putchar(217);
}

void Menu::printLogoPikachu() {
	Menu::SetColor(WHITE, GREEN);
	Controller::gotoXY(27, 2);
	cout << " ________  ___  ___  __    ________  ________  ___  ___  ___  ___     " << endl;
	Controller::gotoXY(27, 3);
	Menu::SetColor(WHITE, GREEN);
	cout << "|\\   __  \\|\\  \\|\\  \\|\\  \\ |\\   __  \\|\\   ____\\|\\  \\|\\  \\|\\  \\|\\  \\    " << endl;
	Controller::gotoXY(27, 4);
	Menu::SetColor(WHITE, LIGHT_GREEN);
	cout << "\\ \\  \\|\\  \\ \\  \\ \\  \\/  /|\\ \\  \\|\\  \\ \\  \\___|\\ \\  \\\\\\  \\ \\  \\\\\\  \\   " << endl;
	Controller::gotoXY(27, 5);
	Menu::SetColor(WHITE, LIGHT_GREEN);
	cout << " \\ \\   ____\\ \\  \\ \\   __\\_ \\ \\   __  \\ \\  \\    \\ \\   __  \\ \\  \\\\\\  \\  " << endl;
	Controller::gotoXY(27, 6);
	Menu::SetColor(WHITE, RED);
	cout << "  \\ \\  \\___|\\ \\  \\ \\  \\\\ \\  \\ \\  \\ \\  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\\\\\  \\ " << endl;
	Controller::gotoXY(27, 7);
	Menu::SetColor(WHITE, RED);
	cout << "   \\ \\__\\    \\ \\__\\ \\__\\\\ \\__\\ \\__\\ \\__\\ \\_______\\ \\__\\ \\__\\ \\_______\\" << endl;
	Controller::gotoXY(27, 8);
	Menu::SetColor(WHITE, LIGHT_RED);
	cout << "    \\|__|     \\|__|\\|__| \\|__|\\|__|\\|__|\\|_______|\\|__|\\|__|\\|_______|  " << endl;
}

int check = 1;
void Menu::printLogo() {
	system("color 70");
	Menu::SetColor(WHITE, BLUE);
	Menu::SetColor(WHITE, BLUE);
	Controller::gotoXY(45, 0);
	cout << "Bui Nam Viet - Truong Hoang Lam" << endl;
	Controller::gotoXY(50, 1);
	cout << "23127516 - 23127402" << endl;
	Controller::gotoXY(20, 9);
	Menu::SetColor(WHITE, PURPLE);
	cout << R"(

		  _____  _  _  ___   __  __    _  _____  ___  _  _  ___  _  _   ___    ___    _    __  __  ___ 
		 |_   _|| || || __| |  \/  |  /_\|_   _|/ __|| || ||_ _|| \| | / __|  / __|  /_\  |  \/  || __|
		   | |  | __ || _|  | |\/| | / _ \ | | | (__ | __ | | | | .` || (_ | | (_ | / _ \ | |\/| || _| 
		   |_|  |_||_||___| |_|  |_|/_/ \_\|_|  \___||_||_||___||_|\_| \___|  \___|/_/ \_\|_|  |_||___|

	)";
	if (check) {
		check = 0;
		int cnt = 15;
		while (cnt--) {
			Menu::SetColor(WHITE, rand() % 6);
			Controller::gotoXY(27, 2);
			cout << " ________  ___  ___  __    ________  ________  ___  ___  ___  ___     " << endl;
			Controller::gotoXY(27, 3);
			Menu::SetColor(WHITE, rand() % 6);
			cout << "|\\   __  \\|\\  \\|\\  \\|\\  \\ |\\   __  \\|\\   ____\\|\\  \\|\\  \\|\\  \\|\\  \\    " << endl;
			Controller::gotoXY(27, 4);
			Menu::SetColor(WHITE, rand() % 6);
			cout << "\\ \\  \\|\\  \\ \\  \\ \\  \\/  /|\\ \\  \\|\\  \\ \\  \\___|\\ \\  \\\\\\  \\ \\  \\\\\\  \\   " << endl;
			Controller::gotoXY(27, 5);
			Menu::SetColor(WHITE, rand() % 6);
			cout << " \\ \\   ____\\ \\  \\ \\   __\\_ \\ \\   __  \\ \\  \\    \\ \\   __  \\ \\  \\\\\\  \\  " << endl;
			Controller::gotoXY(27, 6);
			Menu::SetColor(WHITE, rand() % 6);
			cout << "  \\ \\  \\___|\\ \\  \\ \\  \\\\ \\  \\ \\  \\ \\  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\\\\\  \\ " << endl;
			Controller::gotoXY(27, 7);
			Menu::SetColor(WHITE, rand() % 6);
			cout << "   \\ \\__\\    \\ \\__\\ \\__\\\\ \\__\\ \\__\\ \\__\\ \\_______\\ \\__\\ \\__\\ \\_______\\" << endl;
			Controller::gotoXY(27, 8);
			Menu::SetColor(WHITE, rand() % 6);
			cout << "    \\|__|     \\|__|\\|__| \\|__|\\|__|\\|__|\\|_______|\\|__|\\|__|\\|_______|  " << endl;
			Sleep(125);
		}
	}
	else {
		Menu::printLogoPikachu();
	}
}

int Menu::printLevel() {
	system("cls");
	Menu::printLogo();
	int choice[4] = { 0,0,0,0 }, curChoice = 0;
	while (true) {
		choice[curChoice] = 1;
		if (choice[0]) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 16 + i);
				cout << "              ";
			}
			Controller::gotoXY(55, 17);
			cout << "EASY";
		}
		else {
			Controller::gotoXY(50, 17);
			Menu::SetColor(WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 16, 12, 2);
			Menu::SetColor(WHITE, GREEN);
			//Controller::gotoXY(48, 17);
			//putchar(175);
			Controller::gotoXY(55, 17);
			cout << "EASY";
		}
		if (choice[1]) {
			Menu::SetColor(GREEN, LIGHT_YELLOW);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 19 + i);
				cout << "              ";
			}
			Controller::gotoXY(54, 20);
			cout << "NORMAL";
		}
		else {
			Controller::gotoXY(50, 20);
			Menu::SetColor(WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 19, 12, 2);
			Menu::SetColor(WHITE, GREEN);
			//Controller::gotoXY(48, 20);
			//putchar(175);
			Controller::gotoXY(54, 20);
			cout << "NORMAL";
		}

		if (choice[2]) {
			Menu::SetColor(GREEN, LIGHT_PURPLE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 22 + i);
				cout << "              ";
			}
			Controller::gotoXY(52, 23);
			cout << "DIFFICULT";
		}
		else {
			Controller::gotoXY(50, 23);
			Menu::SetColor(WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 22, 12, 2);
			Menu::SetColor(WHITE, GREEN);
			//Controller::gotoXY(48, 23);
			//putchar(175);
			Controller::gotoXY(52, 23);
			cout << "DIFFICULT";
		}
		if (choice[3]) {
			Menu::SetColor(GREEN, LIGHT_RED);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 25 + i);
				cout << "              ";
			}
			Controller::gotoXY(55, 26);
			cout << "BACK";
		}
		else {
			Controller::gotoXY(50, 26);
			Menu::SetColor(WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 25, 12, 2);
			Menu::SetColor(WHITE, GREEN);
			//Controller::gotoXY(48, 26);
			//putchar(175);
			Controller::gotoXY(55, 26);
			cout << "BACK";
		}

		int temp, key;
		if (temp = _getch()) {
			if (temp != 224 && temp)
			{
				if (temp == KEY_ENTER) {
					Controller::playSound(ENTER_SOUND);
					return curChoice;
				}
			}
			else {
				key = _getch();
				Controller::playSound(MOVE_SOUND);
				switch (key)
				{
				case KEY_UP:
					Controller::playSound(MOVE_SOUND);
					choice[curChoice] = 0;
					if (curChoice > 0) curChoice--;
					else curChoice = 3;
					break;
				case KEY_DOWN:
					Controller::playSound(MOVE_SOUND);
					choice[curChoice] = 0;
					if (curChoice < 3) curChoice++;
					else curChoice = 0;
				default:
					break;
				}
			}
		}
	}
}

void Menu::helpScreen() {
	Controller::showCursor(false);
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	system("cls");
	int left = 5, top = 2, width = 90, height = 23;
	int line1 = 6, line2 = 19, line3 = 20, line4 = 15;
	Menu::printRectangle(left, top, width, height);
	Controller::gotoXY(left + 1, line1);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	Controller::gotoXY(left + 1, line2);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	Controller::gotoXY(left + 1, line4);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	for (int i = 1; i < height; i++)
	{
		Controller::gotoXY(line3, top + i);
		putchar(179);
	}
	Controller::gotoXY(line3, line1);
	putchar(197);
	Controller::gotoXY(line3, line2);
	putchar(197);

	Menu::SetColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(left + 3, top + 2);
	cout << "Moves:";
	Controller::gotoXY(left + 20, top + 1);
	putchar(249); cout << "Up:    W, up arrow";
	Controller::gotoXY(left + 52, top + 1);
	putchar(249); cout << "Down:  S, down arrow";
	Controller::gotoXY(left + 20, top + 3);
	putchar(249); cout << "Left:  A, left arrow";
	Controller::gotoXY(left + 52, top + 3);
	putchar(249); cout << "Right: D, right arrow";


	Controller::gotoXY(left + 3, top + 8);
	cout << "Rules:";
	Controller::gotoXY(left + 17, top + 5);
	int left1 = left + 17;
	putchar(249); cout << " The Matching Game (commonly known as the Pikachu Puzzle Game)";
	Controller::gotoXY(left1, top + 6);
	cout << " includes a board of multiple cells, each of which presents a figure.";
	Controller::gotoXY(left1, top + 8);
	putchar(249); cout << " The player finds and matches a pair of cells that contain the same";
	Controller::gotoXY(left1, top + 9);
	cout << " figure and connect each other in some particular pattern by Enter button.";
	Controller::gotoXY(left1, top + 11);
	putchar(249); cout << " A legal match will make the two cells disappear. The game ends when";
	Controller::gotoXY(left1, top + 12);
	cout << " all matching pairs are found.";

	Controller::gotoXY(left + 3, top + 15);
	cout << "Scoring:";
	Menu::SetColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left1 + 10, top + 14);
	putchar(249); cout << " I Matching: +1 BTC";
	Menu::SetColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left1 + 40, top + 14);
	putchar(249); cout << " L Matching: +2 BTC";
	Menu::SetColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left1 + 10, top + 15);
	putchar(249); cout << " Z Matching: +3 BTC";
	Controller::gotoXY(left1 + 40, top + 15);
	putchar(249); cout << " U Matching: +4 BTC";
	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(left1 + 10, top + 16);
	putchar(249); cout << " Not Matched: -2 BTC";
	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(left1 + 40, top + 16);
	putchar(249); cout << " Move suggestion: -2 BTC";

	Menu::SetColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(left + 3, top + 20);
	cout << "Developers:";
	Controller::gotoXY(left + 31, top + 19);
	cout << "Dev 1: Bui Nam Viet (23127516)";
	Controller::gotoXY(left + 31, top + 21);
	cout << "Dev 2: Truong Hoang Lam (23127402)";

	Menu::SetColor(BRIGHT_WHITE, BLACK);
	printRectangle(45, 27, 8, 2);
	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(43, 28);
	putchar(175);
	Controller::gotoXY(48, 28);
	cout << "Back";
	Controller::gotoXY(56, 28);
	putchar(174);
	while (Controller::getConsoleInput() != 6)
	{
		Controller::playSound(ERROR_SOUND);
	}
	if (Game::isPlaying) {
		system("color 70");
		Game::genBoard();
		Game::cur_block.iX = 0;
		Game::cur_block.iY = 0;
		Game::printBoard();
		Game::printInterface();
		Game::controlPoint();
	}
	else {
		Controller::playSound(ENTER_SOUND);
		Menu::printMainScreen();
	}
}

void Menu::readLeaderBoard() {
	system("cls");
	system("color 1");
	Menu::SetColor(BLACK, LIGHT_AQUA);
	cout << R"(
 ___       _______   ________  ________  _______   ________  ________  ________  ________  ________  ________     
|\  \     |\  ___ \ |\   __  \|\   ___ \|\  ___ \ |\   __  \|\   __  \|\   __  \|\   __  \|\   __  \|\   ___ \    
\ \  \    \ \   __/|\ \  \|\  \ \  \_|\ \ \   __/|\ \  \|\  \ \  \|\ /\ \  \|\  \ \  \|\  \ \  \|\  \ \  \_|\ \   
 \ \  \    \ \  \_|/_\ \   __  \ \  \ \\ \ \  \_|/_\ \   _  _\ \   __  \ \  \\\  \ \   __  \ \   _  _\ \  \ \\ \  
  \ \  \____\ \  \_|\ \ \  \ \  \ \  \_\\ \ \  \_|\ \ \  \\  \\ \  \|\  \ \  \\\  \ \  \ \  \ \  \\  \\ \  \_\\ \ 
   \ \_______\ \_______\ \__\ \__\ \_______\ \_______\ \__\\ _\\ \_______\ \_______\ \__\ \__\ \__\\ _\\ \_______\
    \|_______|\|_______|\|__|\|__|\|_______|\|_______|\|__|\|__|\|_______|\|_______|\|__|\|__|\|__|\|__|\|_______|
	)";
	Menu::SetColor(BLACK, BRIGHT_WHITE);
	Menu::printRectangle(15, 10, 85, 16);

	Menu::SetColor(BLACK, YELLOW);
	Controller::gotoXY(18, 11);
	cout << "STT";
	Menu::SetColor(BLACK, BRIGHT_WHITE);
	for (int i = 1; i < 16; i++)
	{
		Controller::gotoXY(23, 10 + i);
		putchar(179);
	}
	for (int i = 16; i < 23; i++)
	{
		Controller::gotoXY(i, 12);
		putchar(196);
	}
	Menu::SetColor(BLACK, YELLOW);
	Controller::gotoXY(30, 11);
	cout << "NAME";
	Menu::SetColor(BLACK, BRIGHT_WHITE);
	for (int i = 1; i < 16; i++)
	{
		Controller::gotoXY(40, 10 + i);
		putchar(179);
	}
	for (int i = 23; i < 40; i++)
	{
		Controller::gotoXY(i, 12);
		putchar(196);
	}
	Menu::SetColor(BLACK, YELLOW);
	Controller::gotoXY(47, 11);
	cout << "ID";
	Menu::SetColor(BLACK, WHITE);
	for (int i = 1; i < 16; i++)
	{
		Controller::gotoXY(55, 10 + i);
		putchar(179);
	}
	for (int i = 40; i < 55; i++)
	{
		Controller::gotoXY(i, 12);
		putchar(196);
	}
	Menu::SetColor(BLACK, YELLOW);
	Controller::gotoXY(61, 11);
	cout << "Class";
	Menu::SetColor(BLACK, WHITE);
	for (int i = 1; i < 16; i++)
	{
		Controller::gotoXY(72, 10 + i);
		putchar(179);
	}
	for (int i = 55; i < 72; i++)
	{
		Controller::gotoXY(i, 12);
		putchar(196);
	}
	Menu::SetColor(BLACK, YELLOW);
	Controller::gotoXY(78, 11);
	cout << "Mode";
	Menu::SetColor(BLACK, WHITE);
	for (int i = 1; i < 16; i++)
	{
		Controller::gotoXY(88, 10 + i);
		putchar(179);
	}
	for (int i = 72; i < 88; i++)
	{
		Controller::gotoXY(i, 12);
		putchar(196);
	}
	Menu::SetColor(BLACK, YELLOW);
	Controller::gotoXY(92, 11);
	cout << "Score";
	Menu::SetColor(BLACK, WHITE);
	for (int i = 88; i < 101; i++)
	{
		Controller::gotoXY(i, 12);
		putchar(196);
	}
	Player rank[100];
	int y = 13;
	int lines = 8;
	int n = 0;
	string tmp;
	fstream ifs;
	ifs.open("readFile\\rank.txt", ios::in);
	while (!ifs.eof()) {
		getline(ifs, rank[n].playerName);
		getline(ifs, rank[n].playerID);
		getline(ifs, rank[n].className);
		getline(ifs, rank[n].mode);
		ifs >> rank[n].score;
		ifs.ignore();
		n++;
	}
	ifs.close();
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (rank[j].score > rank[i].score) {
				swap(rank[i], rank[j]);
			}
			else if (rank[j].score == rank[i].score) {
				if (rank[j].mode == "DIFFICULT" && rank[i].mode != "DIFFICULT") {
					swap(rank[i], rank[j]);
				}
			}
		}
	}
	for (int i = 1; i < lines; i++) {
		Controller::gotoXY(19, y);
		cout << i;
		if (!rank[i - 1].mode.empty()) {
			Controller::gotoXY(28, y);
			cout << rank[i - 1].playerName;
			Controller::gotoXY(45, y);
			cout << rank[i - 1].playerID;
			Controller::gotoXY(60, y);
			cout << rank[i - 1].className;
			Controller::gotoXY(77, y);
			cout << rank[i - 1].mode;
			Controller::gotoXY(94, y);
			cout << rank[i - 1].score;
		}
		y += 2;
	}
	Menu::SetColor(BLACK, AQUA);
	Menu::printRectangle(55, 27, 10, 2);
	Menu::SetColor(BLACK, LIGHT_AQUA);
	Controller::gotoXY(53, 28);
	putchar(175);
	Controller::gotoXY(59, 28);
	cout << "BACK";
	Controller::gotoXY(68, 28);
	putchar(174);
	while (Controller::getConsoleInput() != 6) {
		Controller::playSound(ERROR_SOUND);
	}
	Controller::playSound(ENTER_SOUND);
	Menu::goBack();
}

void Menu::writeLeaderBoard(Player a) {
	fstream ofs;
	ofs.open("readFile\\rank.txt", ios::in | ios::out);
	if (Game::choice_login) {
		Player tmp;
		while (!ofs.eof()) {
			getline(ofs, tmp.playerName);
			getline(ofs, tmp.playerID);
			getline(ofs, tmp.className);
			ofs >> tmp.mode;
			ofs.get();
			auto pos = ofs.tellp();
			ofs >> tmp.score;
			ofs.ignore();
			if (tmp.playerName == a.playerName && tmp.playerID == a.playerID && tmp.className == a.className && tmp.mode == a.mode) {
				tmp.score = max(tmp.score, Game::tmp_score);
				ofs.seekp(pos, ios::beg);
				ofs << tmp.score;
				break;
			}
		}
	}
	else {
		ofs.seekp(0, ios::end);
		ofs << a.playerName << '\n' << a.playerID << '\n' << a.className << '\n' << a.mode << '\n' << a.score << '\n';
	}
	ofs.close();
	Game::choice_login = false;
}

void Menu::goBack() {
	Menu::printMainScreen();
}

void Menu::printMainScreen() {
	system("cls");
	Controller::playSound(BACKGROUND_SOUND);
	Menu::printLogo();
	int choice[4] = { 0,0,0,0 }, temp, key, curChoice = 0;
	while (true) {
		choice[curChoice] = 1;
		if (choice[0]) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 16 + i);
				cout << "              ";
			}
			Controller::gotoXY(55, 17);
			cout << "PLAY";
		}
		else {
			Controller::gotoXY(50, 17);
			Menu::SetColor(WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 16, 12, 2);
			Menu::SetColor(WHITE, GREEN);
			//Controller::gotoXY(48, 17);
			//putchar(175);
			Controller::gotoXY(55, 17);
			cout << "PLAY";
		}
		if (choice[1]) {
			Menu::SetColor(GREEN, LIGHT_YELLOW);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 19 + i);
				cout << "              ";
			}
			Controller::gotoXY(51, 20);
			cout << "LEADERBOARD";
		}
		else {
			Controller::gotoXY(50, 20);
			Menu::SetColor(WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 19, 12, 2);
			Menu::SetColor(WHITE, GREEN);
			//Controller::gotoXY(48, 20);
			//putchar(175);
			Controller::gotoXY(51, 20);
			cout << "LEADERBOARD";
		}

		if (choice[2]) {
			Menu::SetColor(GREEN, LIGHT_PURPLE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 22 + i);
				cout << "              ";
			}
			Controller::gotoXY(55, 23);
			cout << "HELP";
		}
		else {
			Controller::gotoXY(50, 23);
			Menu::SetColor(WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 22, 12, 2);
			Menu::SetColor(WHITE, GREEN);
			//Controller::gotoXY(48, 23);
			//putchar(175);
			Controller::gotoXY(55, 23);
			cout << "HELP";
		}
		if (choice[3]) {
			Menu::SetColor(GREEN, LIGHT_RED);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 25 + i);
				cout << "              ";
			}
			Controller::gotoXY(55, 26);
			cout << "EXIT";
		}
		else {
			Controller::gotoXY(50, 26);
			Menu::SetColor(WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 25, 12, 2);
			Menu::SetColor(WHITE, GREEN);
			//Controller::gotoXY(48, 26);
			//putchar(175);
			Controller::gotoXY(55, 26);
			cout << "EXIT";
		}

		if (temp = _getch()) {
			if (temp != 224 && temp)
			{
				if (temp == KEY_ENTER) {
					Controller::playSound(ENTER_SOUND);
					system("cls");
					if (curChoice == 0) {
						Game::setupGame();
					}
					else if (curChoice == 1) {
						Menu::readLeaderBoard();
					}
					else if (curChoice == 2) {
						Menu::helpScreen();
					}
					else {
						Menu::SetColor(BLACK, BRIGHT_WHITE);
						system("cls");
						exit(0);
					}
					//return curChoice;
				}
			}
			else {
				key = _getch();
				switch (key)
				{
				case KEY_UP:
					Controller::playSound(MOVE_SOUND);
					choice[curChoice] = 0;
					if (curChoice > 0) curChoice--;
					else curChoice = 3;
					break;
				case KEY_DOWN:
					Controller::playSound(MOVE_SOUND);
					choice[curChoice] = 0;
					if (curChoice < 3) curChoice++;
					else curChoice = 0;
				default:
					break;
				}
			}
		}
	}
}

