#include<bits/stdc++.h>
#include <windows.h>
#include<conio.h>
using namespace std;
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void erase_ship(int x, int y)
{
	setcolor(0, 0);
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("     ");
}
void draw_ship(int x, int y)
{
	setcolor(0, 11);
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("<-0->");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void draw_bullet(int x, int y)
{
	COORD c = { x, y };
	setcolor(7, 0);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("o");
}
void erase_bullet(int x, int y)
{
	COORD c = { x, y };
	setcolor(0, 0);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf(" ");
}
int main()
{
	char ch = ' ';
	int x = 38, y = 20;
	bool shoot[5] = {};
	bool A=false, D=false;
	int xs[5], ys[5] = {};
	setcursor(0);
	setcolor(0, 11);
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x > 0) {
				A = true;
				D = false;
				//erase_ship(x, y);
				//draw_ship(++x, y);
			}
			if (ch == 'd' && x <= 75) {
				D = true;
				A = false;
				//erase_ship(x, y);
				//draw_ship(++x, y);
			}
			if (ch == 'w' && y > 0) {
				erase_ship(x, y);
				draw_ship(x, --y);
			}
			if (ch == 's') {
				erase_ship(x, y);
				draw_ship(x, ++y);
			}
			if (ch == ' ') {
				for (int i = 0; i < 5; i++)
				{
					if (shoot[i] == false)
					{
						shoot[i] = true;
						xs[i] = x + 2;
						ys[i] = y-1;
						break;
					}
				}
			}
			fflush(stdin);
		}
		if (A && x > 0) {
			erase_ship(x, y);
			draw_ship(--x, y);
		}
		if (D && x < 75) {
			erase_ship(x, y);
			draw_ship(++x, y);
		}
		for (int i = 0; i < 5; i++)
		{
			if (shoot[i])
			{
				erase_bullet(xs[i], ys[i]);
				draw_bullet(xs[i], --ys[i]);
				if (ys[i] <= 0)
				{
					erase_bullet(xs[i], ys[i]);
					shoot[i] = false;
				}
			}
		}
		Sleep(500);
	} while (ch != 'x');
	
	return 0;
}
