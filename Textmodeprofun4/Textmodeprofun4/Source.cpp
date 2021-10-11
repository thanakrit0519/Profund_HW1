#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
using namespace std;

#define scount 80
#define screen_x 80
#define screen_y 25
HANDLE rHnd;
DWORD fdwMode;
HANDLE wHnd;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD bufferSize = { screen_x,screen_y };
COORD characterPos = { 0,0 };
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
COORD star[scount];

int setMode()
{
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
		ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
int setConsole(int x, int y)
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
}
void clear_buffer()
{
	for (int y = 0; y < screen_y; ++y) {
		for (int x = 0; x < screen_x; ++x) {
			if (consoleBuffer[x + screen_x * y].Char.AsciiChar == '*')
			{
				consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
				consoleBuffer[x + screen_x * y].Attributes = 7;
			}
		}
	}
}
void clear_buffer_ship()
{
	for (int y = 0; y < screen_y; ++y) {
		for (int x = 0; x < screen_x; ++x) {
			if (consoleBuffer[x + screen_x * y].Char.AsciiChar != '*')
			{
				consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
				consoleBuffer[x + screen_x * y].Attributes = 7;
			}
		}
	}
}
void fill_buffer_to_console()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos,
		&windowSize);
}
void init_star()
{
	int i = 0;
	while (i< scount)
	{
		short x = rand() % screen_x;
		short y = rand() % screen_y;
		if (consoleBuffer[x + screen_x * y].Char.AsciiChar != '*')
		{
			star[i] = { x,y };
			consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar = '*';
			consoleBuffer[star[i].X + screen_x * star[i].Y].Attributes = 7;
			fill_buffer_to_console();
			i++;
		}
	}
}
void star_fall()
{
	int i;
	for (i = 0; i < scount; i++) {
		if (star[i].Y >= screen_y - 1) {
			short x = rand() % screen_x;
			while (consoleBuffer[x + screen_x * 1].Char.AsciiChar == '*')
			{
				x = rand() % screen_x;
			}
			star[i] = { x,1 };
			
		}
		else {
			short y = star[i].Y + 1;
			star[i] = { star[i].X, y };
			
		}
	}
}

void fill_star_to_buffer()
{
	for (int i = 0; i < scount; i++)
	{
		consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar = '*';
		consoleBuffer[star[i].X + screen_x * star[i].Y].Attributes = 7;
	}
	
}
int hit = 0;
bool play = true;
void Hit()
{
	for (int j = 0; j < 80; j++)
	{
		if ((consoleBuffer[star[j].X + screen_x * (star[j].Y + 1)].Char.AsciiChar == '<' || consoleBuffer[star[j].X + screen_x * (star[j].Y + 1)].Char.AsciiChar == '-' || consoleBuffer[star[j].X + screen_x * (star[j].Y + 1)].Char.AsciiChar == 'O' || consoleBuffer[star[j].X + screen_x * (star[j].Y + 1)].Char.AsciiChar == '>') )//|| (consoleBuffer[star[j].X + screen_x * (star[j].Y - 1)].Char.AsciiChar == '<' || consoleBuffer[star[j].X + screen_x * (star[j].Y - 1)].Char.AsciiChar == '-' || consoleBuffer[star[j].X + screen_x * (star[j].Y - 1)].Char.AsciiChar == 'O' || consoleBuffer[star[j].X + screen_x * (star[j].Y - 1)].Char.AsciiChar == '>'))
		{
			consoleBuffer[star[j].X + screen_x * star[j].Y].Char.AsciiChar = ' ';
			consoleBuffer[star[j].X + screen_x * star[j].Y].Attributes = 7;
			while (1)
			{
				short x = rand() % screen_x;
				if (consoleBuffer[x + screen_x].Char.AsciiChar != '*')
				{
					star[j] = { x,1 };
					/*consoleBuffer[star[j].X + screen_x * star[j].Y].Char.AsciiChar = '*';
					consoleBuffer[star[j].X + screen_x * star[j].Y].Attributes = 7;*/
					hit++;
					Beep(700, 100);
					break;
				}
			}
			if (hit == 300)
			{
				play = false;
			}
		}
	}
}
int main()
{
	setcursor(0);
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	setMode();
	srand(time(NULL));
	setConsole(screen_x, screen_y);
	int color = 7;
	//init_star();

	while (play)
	{
		star_fall();
		clear_buffer();
		fill_star_to_buffer();
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i) {

				if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						play = false;
					}
					if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'c')
					{
						color = (rand() % 226);
					}
				}
				else if (eventBuffer[i].EventType == MOUSE_EVENT)
				{
					int posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					int posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
						color = (rand() % 226);
					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED || !(eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED)) {
						if (posx > 75)
						{
							posx = 75;
						}
						clear_buffer_ship();
						consoleBuffer[posx + screen_x * posy].Char.AsciiChar = '<';
						consoleBuffer[posx + screen_x * posy].Attributes = color;
						consoleBuffer[posx + 1 + screen_x * posy].Char.AsciiChar = '-';
						consoleBuffer[posx + 1 + screen_x * posy].Attributes = color;
						consoleBuffer[posx + 2 + screen_x * posy].Char.AsciiChar = 'O';
						consoleBuffer[posx + 2 + screen_x * posy].Attributes = color;
						consoleBuffer[posx + 3 + screen_x * posy].Char.AsciiChar = '-';
						consoleBuffer[posx + 3 + screen_x * posy].Attributes = color;
						consoleBuffer[posx + 4 + screen_x * posy].Char.AsciiChar = '>';
						consoleBuffer[posx + 4 + screen_x * posy].Attributes = color;
						Hit();
					}
				}
			}
			delete[] eventBuffer;
		}
		Hit();
		fill_buffer_to_console();
		Sleep(150);
	}
		return 0;
	}
