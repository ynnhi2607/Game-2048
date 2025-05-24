#include "Setting.h"
void setLevel(Game& g)
{
	gotoXY(48, 13);
	TextColor(11);
	cout << "Press 1, 2, 3, 4 to choose";
	gotoXY(40, 26);
	TextColor(11);
	cout << "Press BACKSPACE or ENTER to return SETTING";
	TextColor(15);
	gotoXY(55, 17);
	cout << "               ";
	gotoXY(55, 22);
	cout << "               ";
	gotoXY(55, 15);
	cout << "1. 4x4\n";
	gotoXY(55, 18);
	cout << "2. 6x6\n";
	gotoXY(55, 21);
	cout << "3. 10x10\n";
	gotoXY(55, 24);
	cout << "4. OTHER\n";
	char setlevel;
	while (1)
	{

		setlevel = _getch();
		switch (setlevel)
		{
		case '1':
		{
			TextColor(15);
			gotoXY(55, 15);
			cout << "1. 4x4\n";
			gotoXY(55, 18);
			cout << "2. 6x6\n";
			gotoXY(55, 21);
			cout << "3. 10x10\n";
			gotoXY(55, 24);
			cout << "4. OTHER\n";
			g.size = 4; gotoXY(55, 15); TextColor(10); cout << "1. 4x4\n";
			break;
		}
		case '2':
		{
			TextColor(15);
			gotoXY(55, 15);
			cout << "1. 4x4\n";
			gotoXY(55, 18);
			cout << "2. 6x6\n";
			gotoXY(55, 21);
			cout << "3. 10x10\n";
			gotoXY(55, 24);
			cout << "4. OTHER\n";
			g.size = 6; gotoXY(55, 18); TextColor(10); cout << "2. 6x6\n"; break;
		}
		case '3':
		{
			TextColor(15);
			gotoXY(55, 15);
			cout << "1. 4x4\n";
			gotoXY(55, 18);
			cout << "2. 6x6\n";
			gotoXY(55, 21);
			cout << "3. 10x10\n";
			gotoXY(55, 24);
			cout << "4. OTHER\n";
			g.size = 10;  gotoXY(55, 21); TextColor(10); cout << "3. 10x10\n"; break;
		}
		case '4':
		{
			TextColor(15);
			gotoXY(55, 15);
			cout << "1. 4x4\n";
			gotoXY(55, 18);
			cout << "2. 6x6\n";
			gotoXY(55, 21);
			cout << "3. 10x10\n";
			gotoXY(55, 24);
			cout << "4. OTHER\n";
			gotoXY(55, 24);
			TextColor(10);
			cout << "4. OTHER: ";
			TextColor(4);
			cin >> g.size;
			cin.ignore();
			while (g.size > 10 || g.size < 0)
			{
				TextColor(15);
				gotoXY(55, 25); cout << "Invalid! Enter again!";
				gotoXY(55, 24);
				cout << "              ";
				TextColor(10);
				gotoXY(55, 24);
				cout << "4. OTHER: ";
				TextColor(4);
				cin >> g.size;
				cin.ignore();
				gotoXY(55, 25); cout << "                     ";
			}
			break;
		}
		case 8: case 13: return; break;
		}
	}
}
void setUR(Game& g)
{
	gotoXY(49, 13);
	TextColor(11);
	cout << "Press 1, 2, 3 to choose";
	TextColor(15);
	gotoXY(55, 17);
	cout << "           ";
	gotoXY(55, 22);
	cout << "             ";
	gotoXY(55, 16);
	cout << "1. OFF UNDO & REDO\n";
	gotoXY(55, 20);
	cout << "2. ON UNDO\n";
	gotoXY(55, 24);
	cout << "3. ON UNDO & REDO\n";
	char setmode;
	while (1)
	{

		setmode = _getch();
		switch (setmode)
		{
		case '1':
			TextColor(15);
			gotoXY(55, 16);
			cout << "1. OFF UNDO & REDO\n";
			gotoXY(55, 20);
			cout << "2. ON UNDO\n";
			gotoXY(55, 24);
			cout << "3. ON UNDO & REDO\n";
			g.mode = 0; gotoXY(55, 16); TextColor(10); cout << "1. OFF UNDO & REDO\n"; break;
		case '2':
			TextColor(15);
			gotoXY(55, 16);
			cout << "1. OFF UNDO & REDO\n";
			gotoXY(55, 20);
			cout << "2. ON UNDO\n";
			gotoXY(55, 24);
			cout << "3. ON UNDO & REDO\n";
			g.mode = 1; gotoXY(55, 20); TextColor(10); cout << "2. ON UNDO\n"; break;
		case '3':
			TextColor(15);
			gotoXY(55, 16);
			cout << "1. OFF UNDO & REDO\n";
			gotoXY(55, 20);
			cout << "2. ON UNDO\n";
			gotoXY(55, 24);
			cout << "3. ON UNDO & REDO\n";
			g.mode = 2; gotoXY(55, 24); TextColor(10); cout << "3. ON UNDO & REDO\n"; break;
		case 8:case 13:return; break;
		}
	}
}
void GameSetting(Game& g)
{
	system("cls");
	TextColor(15);
	string asciiArt =
		"  ______   ________  _________  _________  _____  ____  _____   ______  \n"
		".' ____ \\ |_   __  ||  _   _  ||  _   _  ||_   _||_   \\|_   _|.' ___  | \n"
		"| (___ \\_|  | |_ \\_||_/ | | \\_||_/ | | \\_|  | |    |   \\ | | / .'   \\_| \n"
		" _.____`.   |  _| _     | |        | |      | |    | |\\ \\| | | |   ____ \n"
		"| \\____) | _| |__/ |   _| |_      _| |_    _| |_  _| |_\\   |_\\ `.___]  |\n"
		" \\______.'|________|  |_____|    |_____|  |_____||_____||____|`._____.' \n";
	WordArt(asciiArt, 25, 3);
	cout << "\n\n\n\n\n\t\t\t\t\t-----------------------------------------\n";
	for (int i = 0; i < 12; i++)
	{
		cout << "\t\t\t\t\t|\t\t\t\t\t|\n";
	}
	cout << "\t\t\t\t\t-----------------------------------------\n";
	gotoXY(50, 13);
	TextColor(11);
	cout << "Press 1, 2 to choose";
	gotoXY(41, 26);
	TextColor(11);
	cout << "Press BACKSPACE or ENTER to return MENU";
	while (1)
	{
		TextColor(15);
		gotoXY(55, 15);
		cout << "                       ";
		gotoXY(55, 16);
		cout << "                       ";
		gotoXY(55, 20);
		cout << "                       ";
		gotoXY(55, 18);
		cout << "                       ";
		gotoXY(55, 21);
		cout << "                       ";
		gotoXY(55, 24);
		cout << "                       ";
		gotoXY(55, 17);
		cout << "1. LEVEL\n";
		gotoXY(55, 22);
		cout << "2. UNDO/REDO\n";
		char set;

		set = _getch();
		switch (set)
		{
		case '1':
		{
			setLevel(g); break;
		}
		case '2':
		{
			setUR(g); break;
		}
		case 8: case 13: GameSet(g); break;
		}
	}
	
}