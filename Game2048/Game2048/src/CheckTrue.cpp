#include "CheckTrue.h"
void initVictory(Game& game, Stack& undo)
{
	system("cls");
	//Cấp phát bộ nhớ cho mảng map
	game.m = new int* [game.size];
	for (int i = 0; i < game.size; i++)
	{
		game.m[i] = new int[game.size];
	}
	//Khởi tạo tất cả phần tử trên map bằng 0
	for (int i = 0; i < game.size; i++)
	{
		for (int j = 0; j < game.size; j++)
		{
			game.m[i][j] = 0;
		}
	}
	//random số hàng và cột của ô thứ nhất
	int randi1 = rand() % game.size;
	int randj1 = rand() % game.size;

	//random số hàng và cột của ô thứ hai sao cho ô thứ 2 khác ô thứ nhất
	int randi2 = rand() % game.size;
	while (randi2 == randi1)
	{
		randi2 = rand() % game.size;
	}
	int randj2 = rand() % game.size;

	//random giá trị cho 2 ô 
	game.m[randi1][randj1] = 1024;
	game.m[randi2][randj2] = 1024;
	//Giờ bắt đầu chơi là hiện tại
	game.begin = clock();
	//nếu mode=1 hoặc 2 thì thêm vào stack undo
	if (game.mode == 1 || game.mode == 2) insert(undo, game);
	int n;
	readResumeAcc(n);
	n++;
	if (n >= 5) n = 5;
	saveResumeAcc(n);
}
void initLose(Game& game, Stack& undo)
{
	system("cls");
	//Cấp phát bộ nhớ cho mảng map
	game.m = new int* [game.size];
	for (int i = 0; i < game.size; i++)
	{
		game.m[i] = new int[game.size];
	}
	//Khởi tạo tất cả phần tử trên map bằng 0
	for (int i = 0; i < game.size; i++)
	{
		for (int j = 0; j < game.size; j++)
		{
			int randvalue = rand() % 5;
			if (randvalue == 0) game.m[i][j] = 2;
			else if (randvalue == 1) game.m[i][j] = 8;
			else if (randvalue == 2) game.m[i][j] = 32;
			else if (randvalue == 3) game.m[i][j] = 128;
			else if (randvalue == 4) game.m[i][j] = 512;
		}
	}
	//Giờ bắt đầu chơi là hiện tại
	game.begin = clock();
	//nếu mode=1 hoặc 2 thì thêm vào stack undo
	if (game.mode == 1 || game.mode == 2) insert(undo, game);
	int n;
	readResumeAcc(n);
	n++;
	if (n >= 5) n = 5;
	saveResumeAcc(n);
}