#include "GamePlay.h"
void init(Game& game, Stack& undo)
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
	int randvalue = rand() % 3;
	if (randvalue == 0)
	{
		game.m[randi1][randj1] = 2;
		game.m[randi2][randj2] = 2;
	}
	else if (randvalue == 1)
	{
		game.m[randi1][randj1] = 2;
		game.m[randi2][randi2] = 4;
	}
	else if (randvalue == 2)
	{
		game.m[randi1][randj1] = 4;
		game.m[randi2][randj2] = 4;
	}
	//Giờ bắt đầu chơi là hiện tại
	game.begin = clock();
	//nếu mode=1 hoặc 2 thì thêm vào stack undo
	if(game.mode==1||game.mode==2) insert(undo, game);
	int n;
	readResumeAcc(n);
	n++;
	if (n >= 5) n = 5;
	saveResumeAcc(n);
}
string trim(const string& str)
{
	string result;
	bool Spaces = false;
	for (char ch : str)
	{
		if (ch == ' ')
		{
			if (!Spaces)
			{
				result += ' ';  // Chỉ thêm một dấu cách nếu trước đó không có dấu cách nào
				Spaces = true;
			}
		}
		else
		{
			result += ch;  // Thêm ký tự không phải dấu cách vào kết quả
			Spaces = false;
		}
	}
	//Xóa các dấu cách đầu cuối
	size_t first = result.find_first_not_of(' ');
	if (first == string::npos) return ""; // Chuỗi toàn khoảng trắng
	size_t last = result.find_last_not_of(' ');
	return result.substr(first, (last - first + 1));
}
void ExitGame(Game& g, int acc, Stack& undo, Stack& redo)
{
	gotoXY(44, 2 * g.size + 7);
	TextColor(15);
	cout << "Press Backspace or Enter to return MENU";
	clock_t end = clock();
	g.time = (float)(end - g.begin) / CLOCKS_PER_SEC + g.time;
	//lưu điểm
	SaveTopList(g);
	//Lưu resume
	if (acc != 0)
	{
		string filename = "acc" + to_string(acc) + ".bin";
		saveResume(g, filename, undo, redo);
	}
	//giải phóng vùng nhớ đã cấp phát
	deleteStack(undo);
	deleteStack(redo);
	deleteGame(g);
}
void GamePlay(Game& g, int acc, Stack& undo, Stack& redo)
{
	//biến đề checkVictory 1 lần
	bool check1times = 0;
	Print(g);
	TextColor(10);
	gotoXY(80, 19);
	cout << "Press ESC or 'e' to exit";
	gotoXY(80, 20);
	cout << "Press 'w', 'a', 's', 'd' to move";
	if (g.mode == 1)
	{
		gotoXY(80, 21);
		cout << "Press 'u' to undo";
		"'r' to redo";
	}
	else if (g.mode == 2)
	{
		gotoXY(80, 21);
		cout << "Press 'u' to undo, 'r' to redo";
	}
	gotoXY(91, 26);
	cout << "Author: Huynh Yen Nhi";
	gotoXY(91, 27);
	cout << "ID: 23120151";
	ShowCur(0);
	//Khởi tạo 1 game để lưu trạng thái trước đó của map, dùng để check xem có add số mới không
	Game g2;
	if (check1times == 0)
	{
		if (checkVictory(g))
		{
			clock_t begin = clock();
			clock_t end;
			float timerun;
			gotoXY(0, 2 * g.size + 2);
			TextColor(14);
			cout << "You win!";
			TextColor(15);
			cout << " Do you want to continue?" << endl;
			gotoXY(0, 2 * g.size + 3);
			cout << "1. yes" << setw(15) << "2. no" << endl;
			char chose;
			//biến dùng để thoát khỏi vòng lặp khi nhập vào hợp lệ
			bool checkOut = true;
			while (checkOut)
			{
				chose = _getch();
				switch (chose)
				{
					//tiếp tục chơi
				case '1':
					gotoXY(0, 2 * g.size + 2);
					cout << "                                           " << endl;
					gotoXY(0, 2 * g.size + 3);
					cout << "                                                                                        ";
					gotoXY(0, 2 * g.size + 3);
					cout << "Continue ";
					end = clock();
					timerun = (float)(end - begin) / CLOCKS_PER_SEC;
					g.time -= timerun;
					//Để không hiển thị lại thông báo thắng lần nữa, check1times=1
					check1times = 1;
					checkOut = false; break;
					//Exit Game
				case '2':
					gotoXY(0, 2 * g.size + 2);
					cout << "                                           " << endl;
					gotoXY(0, 2 * g.size + 3);
					cout << "                                          " << endl;
					deleteGame(g2);
					end = clock();
					timerun = (float)(end - begin) / CLOCKS_PER_SEC;
					g.time -= timerun;
					ExitGame(g, acc, undo, redo); checkOut = false; return;
				}
			}
		}
	}
	//Nếu gameover thì ExitGame và in ra màn hình
	if (checkOver(g)&&g.mode==0)
	{
		TextColor(4);
		gotoXY(0, 2 * g.size + 2);
		cout << "Game Over" << endl;
		ExitGame(g, acc, undo, redo);
		deleteGame(g2);
		return;
	}
	//Cấp phát bộ nhớ cho g2
	g2.m = new int* [g.size];
	for (int i = 0; i < g.size; i++)
	{
		g2.m[i] = new int[g.size];
	}
	//Khởi tạo giá trị bằng 0 cho map của g2
	for (int i = 0; i < g.size; i++)
	{
		for (int j = 0; j < g.size; j++)
		{
			g2.m[i][j] = 0;
		}
	}
	//biến lệnh di chuyển
	char move;
	while (1)
	{
		TextColor(4);
		move = _getch();
		gotoXY(0, 2 * g.size + 3);
		cout << "                                                                        ";
		switch (move)
		{
			//nếu không còn trống chỗ (checkempty == 1) và (checkupdown/checkrightleft == 1) thông báo không thể và nhập w/a/s/d lại
			//nếu còn chỗ trống dùng up/down/left/right bình thường
		case 'w':

			if (checkEmpty(g) == 1 && checkupdown(g) == 1)
			{
				gotoXY(0, 2 * g.size + 3);
				cout << "Can't up!";
				continue;
			}
			up(g);

			break;
		case 'a':
			if (checkEmpty(g) == 1 && checkrightleft(g) == 1)
			{
				gotoXY(0, 2 * g.size + 3);
				cout << "Can't left!";
				continue;
			}
			left(g);
			break;
		case 's':
			if (checkEmpty(g) == 1 && checkupdown(g) == 1)
			{
				gotoXY(0, 2 * g.size + 3);
				cout << "Can't down!";
				continue;
			}
			down(g);
			break;
		case 'd':
			if (checkEmpty(g) == 1 && checkrightleft(g) == 1)
			{
				gotoXY(0, 2 * g.size + 3);
				cout << "Can't right!";
				continue;
			}
			right(g);
			break;
		//chỉ undo khi g.mode==1 hoặc g.mode==2
		case 'u':
		{
			if (g.mode == 1 || g.mode == 2)
			{
				if (undo.size > 1)
				{
					Undo(undo, redo, g);
					Print(g);
				}
				else
				{
					gotoXY(0, 2 * g.size + 3);
					cout << "Can't undo!";
				}
				continue;
			}
			else
			{
				gotoXY(0, 2 * g.size + 3);
				cout << "Invalid!"; continue;
			}
		}
		//Chỉ redo khi g.mode==2
		case 'r':
		{
			if (g.mode == 2)
			{
				if (redo.size > 0)
				{
					Redo(undo, redo, g);
					Print(g);
				}
				else
				{
					gotoXY(0, 2 * g.size + 3);
					cout << "Can't redo!";
				}
				continue;
			}
			else
			{
				gotoXY(0, 2 * g.size + 3);
				cout << "Invalid!";
				continue;
			}
		}
		//
		case 27://esc
		case 'e':
		{
			clock_t end;
			clock_t begin = clock();
			float timerun;
			gotoXY(0, 2 * g.size + 2);
			TextColor(11);
			cout << "Do you want to Exit Game?";
			gotoXY(0, 2 * g.size + 3);
			TextColor(15);
			cout << "1. yes" << setw(15) << "2. no" << endl;
			bool checkOut=true;
			while (checkOut)
			{
				char chose = _getch();
				switch (chose)
				{
				case '1':
					gotoXY(0, 2 * g.size + 2);
					cout << "                                           " << endl;
					gotoXY(0, 2 * g.size + 3);
					cout << "                                                                                        ";
					deleteGame(g2);
					ExitGame(g, acc, undo, redo);
					end = clock();
					timerun = (float)(end - begin) / CLOCKS_PER_SEC;
					g.time -= timerun;
					checkOut = false; return; break;
				case '2':
					gotoXY(0, 2 * g.size + 2);
					cout << "                                                   " << endl;
					gotoXY(0, 2 * g.size + 3);
					cout << "                                                    " << endl;
					gotoXY(0, 2 * g.size + 2);
					cout << "Continue";
					//Cập nhật thời gian chơi, trừ thời gian lựa chọn 
					end = clock();
					timerun = (float)(end - begin) / CLOCKS_PER_SEC;
					g.time -= timerun;
					//Cập nhật thời gian chơi, trừ thời gian lựa chọn 
					checkOut = false; break;
				}

			}
			break;
		}
		//khi nhập không hợp lệ, thông báo ra màn hình và nhập lại
		default:
			gotoXY(0, 2 * g.size + 3);
			cout << "Invalid!" << endl; continue;
		}
		//Nếu đi bước mới và g.mode==2 thì xóa stack redo
		if (g.mode == 2) deleteStack(redo);
		//Nếu g(trạng thái hiện tại) khác g2(trạng thái ngay trước nó) thì add, không thì nhập lại
		if (checkSimilar(g, g2) == 0)
		{
			add(g);
		}
		else
		{
			continue;
		}
		//Nếu mode=1 hoặc 2 thì thêm vào Stack undo
		if (g.mode == 1 || g.mode == 2) insert(undo, g);
		Print(g);
		//Kiểm tra khi thắng 
		if (check1times == 0)
		{
			if (checkVictory(g))
			{
				clock_t begin = clock();
				clock_t end;
				float timerun;
				gotoXY(0, 2 * g.size + 2);
				TextColor(14);
				cout << "You win!";
				TextColor(15);
				cout << " Do you want to continue?" << endl;
				gotoXY(0, 2 * g.size + 3);
				cout << "1. yes" << setw(15) << "2. no" << endl;
				char chose;
				//biến dùng để thoát khỏi vòng lặp khi nhập vào hợp lệ
				bool checkOut = true;
				while (checkOut)
				{
					chose = _getch();
					switch (chose)
					{
						//tiếp tục chơi
					case '1':
						gotoXY(0, 2 * g.size + 2);
						cout << "                                           " << endl;
						gotoXY(0, 2 * g.size + 3);
						cout << "                                                                                        ";
						gotoXY(0, 2 * g.size + 3);
						cout << "Continue ";
						end = clock();
						timerun = (float)(end - begin) / CLOCKS_PER_SEC;
						g.time -= timerun;
						//Để không hiển thị lại thông báo thắng lần nữa, check1times=1
						check1times = 1; 
						checkOut = false; break;
						//Exit Game
					case '2':
						gotoXY(0, 2 * g.size + 2);
						cout << "                                           " << endl;
						gotoXY(0, 2 * g.size + 3);
						cout << "                                          " << endl;
						deleteGame(g2);
						end = clock();
						timerun = (float)(end - begin) / CLOCKS_PER_SEC;
						g.time -= timerun;
						ExitGame(g, acc, undo, redo); checkOut = false; return;
					}
				}
			}
		}
		//Thông báo khi game kết thúc
		if (checkOver(g))
		{
			clock_t begin = clock();
			clock_t end;
			float timerun;
			if (g.mode == 0)
			{
				TextColor(4);
				gotoXY(0, 2 * g.size + 2);
				cout << "Game Over" << endl;
				deleteGame(g2);
				ExitGame(g, acc, undo, redo);
				return;
			}
			//g.mode!=0 thì thông báo và hỏi xem có dùng undo để chơi lại không
			else
			{
				gotoXY(0, 2 * g.size + 2);
				TextColor(4);
				cout << "You lose!";
				TextColor(15);
				cout << " Do you want to continue by undo?" << endl;
				gotoXY(0, 2 * g.size + 3);
				cout << "1. yes" << setw(15) << "2. no" << endl;
				//biến dùng để thoát khỏi vòng lặp khi nhập vào hợp lệ
				bool checkOut = true;
				while (checkOut)
				{
					char chose = _getch();
					switch (chose)
					{
					case '1':
						gotoXY(0, 2 * g.size + 2);
						cout << "                                           " << endl;
						gotoXY(0, 2 * g.size + 3);
						cout << "                                                                                        ";
						gotoXY(0, 2 * g.size + 3);
						cout << "Continue ";
						//Cập nhật thời gian chơi, trừ thời gian lựa chọn 
						end = clock();
						timerun = (float)(end - begin) / CLOCKS_PER_SEC;
						g.time -= timerun;
						 checkOut = false; break;
					case '2':
						gotoXY(0, 2 * g.size + 2);
						cout << "                                                   " << endl;
						gotoXY(0, 2 * g.size + 3);
						cout << "                                                    " << endl;
						TextColor(4);
						gotoXY(0, 2 * g.size + 2);
						cout << "Game Over" << endl;
						//Cập nhật thời gian chơi, trừ thời gian lựa chọn 
						end = clock();
						timerun = (float)(end - begin) / CLOCKS_PER_SEC;
						g.time -= timerun;
						deleteGame(g2);
						ExitGame(g, acc, undo, redo);
						checkOut = false; return;
					}
				}
			}
		}
		//gán trạng thái hiện tại cho g2
		for (int i = 0; i < g.size; i++)
		{
			for (int j = 0; j < g.size; j++)
			{
				g2.m[i][j] = g.m[i][j];
			}
		}
	}
}
void add(Game& g)
{
	int randi, randj;
	while (1)
	{
		randi = rand() % g.size;
		randj = rand() % g.size;
		if (g.m[randi][randj] == 0)
		{
			int n = rand() % 2;
			if (n == 0) g.m[randi][randj] = 2;
			else g.m[randi][randj] = 4;
			break;
		}
	}
}
void Print(Game& g)
{
	gotoXY(0, 0);
	TextColor(15);
	for (int i = 0; i < g.size; i++)
	{
		cout << "------";
	}
	cout << endl;

	for (int i = 0; i < g.size; i++)
	{
		cout << "|";
		for (int j = 0; j < g.size; j++)
		{
			if (g.m[i][j] == 0) cout << setw(5) << " " << "|";
			else
			{
				SetColor(g.m[i][j]);
				cout << setw(5) << g.m[i][j];
				TextColor(15);
				cout << "|";
			}
		}
		cout << endl;
		for (int i = 0; i < g.size; i++)
		{
			cout << "------";
		}
		cout << endl;
	}
	gotoXY(0, 2 * g.size + 2);
	cout << "                                         ";
	gotoXY(85, 4);
	TextColor(15);
	cout << "Name: ";
	TextColor(11);
	cout << g.name << endl;
	TextColor(15);
	gotoXY(85, 5);
	cout << "                                  ";
	gotoXY(85, 5);
	cout << "Score: ";
	TextColor(10);
	cout << g.score << endl;
	gotoXY(85, 3);
	TextColor(15);
	cout << "                                   ";
	gotoXY(85, 3);
	cout << "High Score: ";
	TextColor(6); cout << HighScore(g) << endl;
	TextColor(15);
	gotoXY(85, 2);
	cout << "Mode: ";
	if (g.mode == 0) cout << "off undo&redo";
	else if (g.mode == 1) cout << "on undo";
	else if (g.mode == 2) cout << "on undo&redo";
	ShowCur(0);
}
//Hàm này mặc định lưu resume khi new game.
string EnterName(Game g, int& acc)
{
	acc = 0;
	string asciiArt =
		" ____  _____  ________  ____      ____      ______       _       ____    ____  ________ \n"
		"|_   \\|_   _||_   __  ||_  _|    |_  _|   .' ___  |     / \\     |_   \\  /   _||_   __  |\n"
		"  |   \\ | |    | |_ \\_|  \\ \\  /\\  / /    / .'   \\_|    / _ \\      |   \\/   |    | |_ \\_|\n"
		"  | |\\ \\| |    |  _| _    \\ \\/  \\/ /     | |   ____   / ___ \\     | |\\  /| |    |  _| _ \n"
		" _| |_\\   |_  _| |__/ |    \\  /\\  /      \\ `.___]  |_ / /   \\ \\_  _| |_\\/| |_  _| |__/ |\n"
		"|_____\\|\\____||________|     \\/  \\/        `._____.'|____| |____||_____||_____||________|\n";
	WordArt(asciiArt, 10, 3);
	string name;
	cout << "\n\n\n\n\t\t\t\t\t-----------------------------------------\n";
	for (int i = 0; i < 11; i++)
	{
		cout << "\t\t\t\t\t|\t\t\t\t\t|\n";
	}
	cout << "\t\t\t\t\t-----------------------------------------\n";
	int n;
	Stack l;
	ReadTopList(l);
	readResumeAcc(n);
	if (n == 5)
	{
		int y = 14;
		gotoXY(50, 12);
		TextColor(11);
		cout << "Choose acc to delete:" << endl;
		TextColor(15);
		for (int i = 0; i < 5; i++)
		{
			Game game;
			string filename = "acc" + to_string(i+1) + ".bin";
			Stack undo, redo;
			ifstream in(filename, ios::binary);
			if (fileExists(filename) && !isFileEmpty(filename))
			{
				readResume(game, filename, undo, redo);
				TextColor(15);
				gotoXY(55, y);
				cout << i + 1 << ". " << game.name << endl;
			}
			else
			{
				TextColor(8);
				gotoXY(55, y);
				cout << i + 1 << ". ";
			}
			y += 2;
		}
		gotoXY(55, 25);
		bool check = true;
		while (check)
		{
			gotoXY(48, 25);
			cout << "                                                  ";
			gotoXY(48, 26);
			cout << "                                                 ";
			char chooseAcc = _getch();
			string filename = "acc" + string(1, chooseAcc) + ".bin";
			if (chooseAcc == 27 || chooseAcc == 'e' || chooseAcc == 8) GameSet(g);
			if (!isdigit(chooseAcc)) continue;
			if (stoi(string(1, chooseAcc)) <= 5&&!isFileEmpty(filename))
			{
				gotoXY(48, 25);
				TextColor(14);
				cout << "Do you want to delete acc " << chooseAcc << "?";
				TextColor(15);
				gotoXY(48, 26);
				cout << setw(7) << "1. yes" << setw(15) << "2. no" << endl;
				bool checkChoose = true;
				while (checkChoose)
				{
					char yn = _getch();
					if (yn == '1') 
					{
						acc = stoi(string(1, chooseAcc));
						//xóa file
						ofstream out(filename, ios::binary);
						out.close();
						//giảm số tài khoản hiện có
						readResumeAcc(n);
						n = n - 1;
						saveResumeAcc(n);
						check = false; 
						checkChoose = false; 
					}
					else if (yn == '2') checkChoose = false;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			string filename = "acc" + to_string(i + 1) + ".bin";
			if (!fileExists(filename) || isFileEmpty(filename))
			{
				acc = i + 1;
				break;
			}
		}
	}
	system("cls");
	WordArt(asciiArt, 10, 2);
	gotoXY(25, 19);
	TextColor(14);
	cout << "NAMING RULES";
	TextColor(15);
	gotoXY(25, 21);
	cout << "1. No conflict with C++ functions: Avoid names like main, printf, remove, etc.";
	gotoXY(25, 22);
	cout << "2. Max 15 characters: Names must be 15 characters or fewer.";
	gotoXY(25, 23);
	cout << "3. Non-empty: Names cannot be empty.";
	gotoXY(25, 24);
	cout << "4. Starts with a letter: The first character must be a letter (a-z or A-Z).";
	gotoXY(25, 25);
	cout << "5. Alphanumeric only: Use only letters (a-z, A-Z) and numbers (0-9).";
	TextColor(11);
	gotoXY(55, 11);
	cout << "Enter Your Name: ";
	TextColor(15);
	getline(cin, name);
	//Chuẩn hóa tên nhập vào
	name = trim(name);
	while (isNameDuplicate(name, l,acc) || !isNameValid(name))
	{
		while (isNameDuplicate(name, l,acc))
		{
			gotoXY(55, 11);
			cout << "                                                                                                                             ";
			gotoXY(50, 11);
			TextColor(4);
			cout << "Name is already taken!";
			TextColor(15);
			gotoXY(50, 13);
			cout << "                                                                                                 ";
			TextColor(11);
			gotoXY(50, 13);
			cout << "Please enter again: ";
			TextColor(15);
			getline(cin, name);
		}
		while (!isNameValid(name))
		{
			gotoXY(55, 11);
			cout << "                                                                                                 ";
			gotoXY(50, 11);
			cout << "                            ";
			gotoXY(50, 11);
			TextColor(4);
			cout << "Name is invalid!";
			TextColor(15);
			gotoXY(50, 13);
			cout << "                                                                                                 ";
			gotoXY(50, 13);
			TextColor(11);
			cout << "Please enter again: ";
			TextColor(15);
			getline(cin, name);
		}
	}
	return name;
}