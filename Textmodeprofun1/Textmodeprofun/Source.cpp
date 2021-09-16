#include<bits/stdc++.h>
#include <windows.h>
#include<conio.h>

void erase_ship(int x,int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("     ");
	COORD c1 = { x, y+1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c1);
	printf("     ");
	COORD c2 = { x, y -1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c2);
	printf("     ");
}
void draw_ship(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("<-0->");
}
int main()
{
	char ch = ' ';
	int x = 38, y = 20;
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a'&&x>0) {
				erase_ship(x, y);
				draw_ship(--x, y); 
			}
			if (ch == 'd'&&x<=75) {
				erase_ship(x, y);
				draw_ship(++x, y); 
			}
			if (ch == 'w' && y > 0) {
				erase_ship(x, y);
				draw_ship(x, y--); 
			}
			if (ch == 's' ) { 
				erase_ship(x, y);
				draw_ship(x, y++); 
			}
			fflush(stdin);
		}
		Sleep(50);
	} while (ch != 'x');
	return 0;
}