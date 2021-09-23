#include<bits/stdc++.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
using namespace std;
vector<pair<int, int>> Bullet;
int score = 0;
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y); printf(" <-0-> ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); printf("o");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void draw_star(int x, int y)
{
	gotoxy(x, y); printf("*");
}
void clear_star(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void draw_score()
{
	setcolor(2, 0);
	gotoxy(60, 1);
	printf("Score : %d", score);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
int main()
{
	setcursor(0);
	srand(time(NULL));
	int star = 0;
	draw_score();
	while (star < 20)
	{
		int xs = (rand() % 61) + 10;
		int ys = (rand() % 4) + 2;
		if (cursor(xs, ys) != '*')
		{
			draw_star(xs, ys);
			star++;
		}
	}
	char ch = '.';
	int x = 38, y = 20;
	int bx, by, i;
	int bullet = 0;
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x > 0) { draw_ship(--x, y); }
			if (ch == 'd' && x < 74) { draw_ship(++x, y); }
			if (ch == 'w' && y > 0) { draw_ship(x, --y); }
			if (ch == 's' && y < 25) { draw_ship(x, ++y); }
			if (ch == ' ')
			{
				Bullet.push_back(make_pair(x + 3, y - 1));
			}
			fflush(stdin);
		}
		for (int i = 0; i < Bullet.size(); i++)
		{
			if (Bullet[i].second <= 2)
			{
				clear_bullet(Bullet[i].first, Bullet[i].second);
				Bullet.erase(Bullet.begin() + i);
				i--;
			}
			else
			{
				if (cursor(Bullet[i].first, Bullet[i].second - 1) == '*')
				{
					clear_bullet(Bullet[i].first, Bullet[i].second);
					clear_star(Bullet[i].first, Bullet[i].second - 1);
					Beep(700, 100);
					score++;
					draw_score();
					Bullet.erase(Bullet.begin() + i);
					i--;
					star--;
					while (star != 20)
					{
						int xs = (rand() % 61) + 10;
						int ys = (rand() % 4) + 2;
						if (cursor(xs, ys) != '*' && cursor(xs, ys) != 'o')
						{
							draw_star(xs, ys);
							star++;
						}
					}
				}
				else
				{
					clear_bullet(Bullet[i].first, Bullet[i].second);
					draw_bullet(Bullet[i].first, --Bullet[i].second);
				}
			}
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}