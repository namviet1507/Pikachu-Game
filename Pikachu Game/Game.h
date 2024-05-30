#pragma once
#include "Struct.h"
#include "Controller.h"
#include <fstream>
#include <stdlib.h>
using namespace std;
struct Game {
	struct Point {
		int iX;
		int iY;
		int pX;
		int pY;
	};

	static char** board;						// bang chu cai
	static int life, tmp_score;					// so luot choi va diem tam thoi
	static int width;							// chieu rong bang
	static int height;							// chieu cao bang
	static int _mode;							// cap do choi Easy: 0, Normal: 1, Difficult: 2
	static int total_block;						// tong so o
	static int height_bg;						// số line của background
	static int no_suggest;						// so luot goi y
	static Point cur_block;						// Vi tri hien tai của block
	static string* background;					// chuoi luu background
	static bool isPlaying;						// kiểm tra còn dang chơi hay không
	static bool playAgain;						// kiểm tra chơi lại hoặc không chơi lại
	static bool choice_login;					// kiểm tra chọn đăng nhập hoặc không đăng nhập

	static void login();						// dang nhap
	static void signup();						// dang ky
	static void warning();						// canh bao dang nhap loi
	static void setupGame();					// thiet lap Game
	static void createBackground();				// thiet lap background
	static void getBackground(string);			// doc file txt sang background
	static int getsizeBg(string);				// lay kich thuoc cua background
	static void displayBackground(Point);		// trinh chieu background
	static void displayStatus(bool);			// trinh chieu trang thai win hoac lose 
	static void printInterface();				// in thong tin ra man hinh
	static void printBackground();				// in background
	static bool check_account_exists();			// kiem tra tai khoan ton tai khong

	// -------------

	static void setSize();						// cai dat kich thuoc bang
	static void genBoard();						// Lập bảng
	static void printBoard();					// In bảng
	static bool verify();						// Xác minh ô chữ chơi được không
	static void reset();						// Cài lại bảng nếu không thể ghép nối
	static void controlPoint();					// Trung tâm điều khiển trò chơi

	static void moveRight();					// Di chuyen qua phải
	static void moveLeft();						// Di chuyen qua trai
	static void moveUp();						// Di chuyen len tren
	static void moveDown();						// Di chuyen xuong duoi

	static void printBlock(int, int, Point);	// In ô
	static void deleteBlock(Point);				// Xóa ô
	static void selectBlock(Point&);			// In ô đã chọn

	static bool checkMatching(Point, Point, bool);				// Kiem tra xem noi hai ô duoc khong

	static void drawIline(Point, Point);						// Vẽ line I
	static void drawLline(Point, Point, Point);					// Vẽ line L
	static void drawZline(Point, Point, Point, Point);			// Vẽ line Z
	static void drawUline(Point, Point, Point, Point);			// Vẽ line U

	static void deleteIline(Point, Point);						// Xóa line I
	static void deleteLline(Point, Point, Point);				// Xóa line L
	static void deleteZline(Point, Point, Point, Point);		// Xóa line Z
	static void deleteUline(Point, Point, Point, Point);		// Xóa line U

	static bool IMatching(Point, Point, bool);					// Kiểm tra nối I
	static bool LMatching(Point, Point, bool);					// Kiểm tra nối L
	static bool ZMatching(Point, Point, bool);					// Kiểm tra nối Z
	static bool UMatching(Point, Point, bool);					// Kiểm tra nối U
	static void slideLeft(Point&, Point&);						// Chơi kiểu trượt sang trái khi xóa ô

	static void moveSuggest();					// Đưa ra gợi ý
	static void deleteBoard();					// Xóa bảng

	static void countdown(time_t, int, bool&);		// Tính thời gian
};