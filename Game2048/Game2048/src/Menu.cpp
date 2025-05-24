#include "Menu.h"
void GameSet(Game& g)
{
	StartMenu();

	char set;
	Stack undo, redo;
	int acc;
	while (1)
	{
		set = _getch();
		switch (set)
		{
		case '1': system("cls"); 
			g.name = EnterName(g, acc); 
			//initLose(g,undo); //dùng hàm này để kiểm tra tính đúng đắn khi thua
			//initVictory(g,undo); //dùng hàm này để kiểm tra tính đúng đắn khi thắng
			init(g, undo); 
			GamePlay(g, acc, undo, redo); 
			break;
		case '2': GameSetting(g); break;
		case '3': ShowTopList(); break;
		case '4':
		{
			int n;
			readResumeAcc(n);
			if (n != 0) Resume();
			break;
		}
		case 8:case 13: Game g2; GameSet(g2); break;
		}
	}
}
void StartMenu()
{
	//giao diện màn hình bắt đầu
	system("cls");
	string asciiArt =
		" .-----.   .----.      .---.    .-----.  \n"
		"/ ,-.   \\ /  ..  \\    / .  |   /  .-.  \\ \n"
		"'-'  |  |.  /  \\  .  / /|  |  |   \\_.' / \n"
		"   .'  / |  |  '  | / / |  |_  /  .-. '. \n"
		" .'  /__ '  \\  /  '/  '-'    ||  |   |  | \n"
		"|       | \\  `'  / `----|  |-' \\  '-'  / \n"
		"`-------'  `---''       `--'    `----''  \n";
	WordArt(asciiArt, 40, 3);
	cout << "\n\n\n\n\t\t\t\t\t-----------------------------------------\n";
	for (int i = 0; i < 12; i++)
	{
		cout << "\t\t\t\t\t|\t\t\t\t\t|\n";
	}
	cout << "\t\t\t\t\t-----------------------------------------\n";
	gotoXY(55, 15);
	cout << "1. NEW GAME\n";
	gotoXY(55, 18);
	cout << "2. GAME SETTING\n";
	gotoXY(55, 21);
	cout << "3. TOP 20\n";
	gotoXY(55, 24);
	int n;
	readResumeAcc(n);
	if (n != 0) TextColor(15);
	else TextColor(8);
	cout << "4. RESUME\n";
	gotoXY(47, 13);
	TextColor(11);
	cout << "Press 1, 2, 3, 4 to choose";
	ShowCur(0);
}