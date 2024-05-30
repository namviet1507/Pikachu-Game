#pragma once
#include "Struct.h"

struct Controller {
	static HWND consoleWindow;    //Con trỏ xử lí cửa sổ console
	static HANDLE consoleOutput;  //Con trỏ xử lí output console
	static void setUpConsole();               //Thiết lập cửa sổ console
	static void gotoXY(int, int);			  //Di chuyển con trỏ đến vị trí x,y
	static void hideScrollBars();             //Ẩn thanh cuộn
	static void setConsoleTitle();            //Cài đặt tiêu đề console
	static void setAndCenterWindow();         //Căn giữa và thiết lập độ phân giải màn hình console
	static int getConsoleInput();             //Lấy lệnh từ bàn phím
	static void showCursor(bool);             //Ẩn hoặc hiện con trỏ
	static void playSound(int);               //Phát âm thanh
	static void disableMouseInput();          //Vô hiệu hóa chuột trong console
};