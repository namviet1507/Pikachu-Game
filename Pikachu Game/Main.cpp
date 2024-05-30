#include "Struct.h"
#include "Controller.h"
#include "Game.h"
int main() {
	Controller::setUpConsole();
	Menu::printMainScreen();
	system("PAUSE");
	return 0;
}