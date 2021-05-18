#ifndef COLOR_H
#define COLOR_H
#include <windows.h>
typedef enum{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,
LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE} COLORS;

static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;

void textcolor(int color){
    __FOREGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));
}
void backgroundcolor(int color){
    __BACKGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), __FOREGROUND + (__BACKGROUND << 4));
}
void aleaBackground(){
	int i = 1+(rand() % 15);
	backgroundcolor(i);
}
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput){
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi)){
        return cbsi.dwCursorPosition;
    }
    else{
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}
int GetconsoleCursorY(){
	COORD ponto;
	int Y;
	ponto = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
	Y = ponto.Y+1;
	return Y;
}
int GetconsoleCursorX(){
	COORD ponto;
	int X;
	ponto = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
	X = ponto.X+1;
	return X;
}
void hidecursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void printC(char string[], int color){
	textcolor(color);
	printf("%s", string);
}
#endif