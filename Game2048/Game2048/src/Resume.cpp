#include "Resume.h"
void serializeGame(ofstream& out, const Game& game)
{
	out.write(reinterpret_cast<const char*>(&game.size), sizeof(game.size));
	out.write(reinterpret_cast<const char*>(&game.score), sizeof(game.score));
	out.write(reinterpret_cast<const char*>(&game.mode), sizeof(game.mode));

	size_t nameLength = game.name.size();
	out.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
	out.write(game.name.c_str(), nameLength);

	out.write(reinterpret_cast<const char*>(&game.time), sizeof(game.time));
	for (int i = 0; i < game.size; ++i)
	{
		out.write(reinterpret_cast<const char*>(game.m[i]), game.size * sizeof(int));
	}
}
void deserializeGame(ifstream& in, Game& game)
{
	in.read(reinterpret_cast<char*>(&game.size), sizeof(game.size));
	in.read(reinterpret_cast<char*>(&game.score), sizeof(game.score));
	in.read(reinterpret_cast<char*>(&game.mode), sizeof(game.mode));

	size_t nameLength;
	in.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
	game.name.resize(nameLength);
	in.read(&game.name[0], nameLength);

	in.read(reinterpret_cast<char*>(&game.time), sizeof(game.time));
	
	game.m = new int* [game.size];
	for (int i = 0; i < game.size; ++i) {
		game.m[i] = new int[game.size];
		in.read(reinterpret_cast<char*>(game.m[i]), game.size * sizeof(int));
	}
}
void saveResumeAcc(int n)
{
	ofstream output("numacc.bin", ios::binary);
	output.write(reinterpret_cast<const char*>(&n), sizeof(n));

	output.close();
}
void readResumeAcc(int& n)
{
	ofstream output("numacc.bin", ios::binary | ios::app);
	output.close();
	ifstream input("numacc.bin", ios::binary);
	input.seekg(0, ios::end);
	if (input.tellg() == 0)
	{
		n = 0;
		input.close();
		return;
	}
	input.seekg(0, ios::beg);
	input.read(reinterpret_cast<char*>(&n), sizeof(n));
	input.close();
}
void saveResume(Game g, string file, Stack undo, Stack redo)
{
	ofstream output(file, ios::binary);
	if (!output)
	{
		cout << "Can't open file!" << endl;
		return;
	}
	output.write(reinterpret_cast<const char*>(&g.size), sizeof(g.size));
	output.write(reinterpret_cast<const char*>(&g.score), sizeof(g.score));
	output.write(reinterpret_cast<const char*>(&g.mode), sizeof(g.mode));
	size_t sizeofname = g.name.size();
	output.write(reinterpret_cast<const char*>(&sizeofname), sizeof(sizeofname));
	output.write(g.name.c_str(), sizeofname);
	output.write(reinterpret_cast<const char*>(&g.time), sizeof(g.time));
	for (int i = 0; i < g.size; ++i) {
		output.write(reinterpret_cast<const char*>(g.m[i]), sizeof(int) * g.size);
	}
	if (g.mode == 1 || g.mode == 2)
	{
		output.write(reinterpret_cast<const char*>(&undo.size), sizeof(undo.size));
		if (undo.head != NULL)
		{
			Node* t = undo.head;
			while (t != NULL)
			{
				serializeGame(output, t->game);
				t = t->next;
			}
		}
	}
	if (g.mode == 2)
	{
		output.write(reinterpret_cast<const char*>(&redo.size), sizeof(redo.size));
		if (redo.head != NULL)
		{
			Node* t = redo.head;
			while (t != NULL)
			{
				serializeGame(output, t->game);
				t = t->next;
			}
		}
	}
	gotoXY(50, g.size * 2 + 6);
	TextColor(3);
	cout << "Save resume succcessfully!";
	output.close();
}
void readResume(Game& g, string file, Stack& undo, Stack& redo)
{
	ifstream input(file, ios::binary);
	if (!input)
	{
		cout << "Can't open file!" << endl;
		return;
	}
	input.read(reinterpret_cast<char*>(&g.size), sizeof(g.size));
	input.read(reinterpret_cast<char*>(&g.score), sizeof(g.score));
	input.read(reinterpret_cast<char*>(&g.mode), sizeof(g.mode));
	size_t namesize;
	input.read(reinterpret_cast<char*>(&namesize), sizeof(namesize));
	g.name.resize(namesize);
	input.read(&g.name[0], namesize);
	input.read(reinterpret_cast<char*>(&g.time), sizeof(g.time));
	g.m = new int* [g.size];
	for (int i = 0; i < g.size; ++i)
	{
		g.m[i] = new int[g.size];
	}
	for (int i = 0; i < g.size; ++i)
	{
		input.read(reinterpret_cast<char*>(g.m[i]), sizeof(int) * g.size);
	}

	if (g.mode == 1 || g.mode == 2)
	{
		input.read(reinterpret_cast<char*>(&undo.size), sizeof(undo.size));
		if (undo.size != 0)
		{
			Node* current = nullptr;
			for (int i = 0; i < undo.size; ++i)
			{
				Node* newNode = new Node;
				deserializeGame(input, newNode->game);
				newNode->next = nullptr;

				if (current == nullptr)
				{
					undo.head = newNode;
				}
				else
				{
					current->next = newNode;
				}
				current = newNode;
			}
		}
	}
	if (g.mode == 2)
	{
		input.read(reinterpret_cast<char*>(&redo.size), sizeof(redo.size));
		if (redo.size != 0)
		{
			Node* current = nullptr;
			for (int i = 0; i < redo.size; ++i) {
				Node* newNode = new Node;
				deserializeGame(input, newNode->game);
				newNode->next = nullptr;

				if (current == nullptr) {
					redo.head = newNode;
				}
				else
				{
					current->next = newNode;
				}
				current = newNode;
			}
		}
	}
	input.close();
}
void Resume()
{
	Stack undo, redo;
	system("cls");
	string asciiArt =
		" _______     ________   ______  _____  _____  ____    ____  ________ \n"
		"|_   __ \\   |_   __  |.' ____ \\|_   _||_   _||_   \\  /   _||_   __  |\n"
		"  | |__) |    | |_ \\_|| (___ \\_| | |    | |    |   \\/   |    | |_ \\_|\n"
		"  |  __ /     |  _| _  _.____`.  | '    ' |    | |\\  /| |    |  _| _ \n"
		" _| |  \\ \\_  _| |__/ || \\____) |  \\ \\__/ /    _| |_\\/_| |_  _| |__/ |\n"
		"|____| |___||________| \\______.'   `.__.'    |_____||_____||________|\n";
	WordArt(asciiArt, 26, 2);
	cout << "\n\n\n\n\n\t\t\t\t\t-----------------------------------------\n";
	for (int i = 0; i < 12; i++)
	{
		cout << "\t\t\t\t\t|\t\t\t\t\t|\n";
	}
	cout << "\t\t\t\t\t-----------------------------------------\n";
	gotoXY(55, 12);
	TextColor(11);
	cout << "Choose account:" << endl;
	gotoXY(41, 25);
	TextColor(11);
	cout << "Press BACKSPACE or ENTER to return MENU";
	TextColor(15);
	int n;
	readResumeAcc(n);
	if (n > 5)n = 5;
	int y = 14;
	/*for (int i = 0; i < n; i++)
	{
		Game game;
		string filename = "acc" + to_string(i + 1) + ".bin";
		readResume(game, filename, undo, redo);
		gotoXY(55, y); y += 2;
		cout << i + 1 << ". " << game.name << endl;
	}
	for (int i = n; i < 5; i++)
	{
		gotoXY(55, y); y += 2;
		TextColor(8);
		cout << i + 1 << "." << endl;
	}*/
	for (int i = 0; i < 5; i++)
	{
		Game game;
		string filename = "acc" + to_string(i + 1) + ".bin";
		ifstream in(filename, ios::binary);
		if (fileExists(filename)&&!isFileEmpty(filename))
		{
			readResume(game, filename, undo, redo);
			TextColor(15);
			gotoXY(55, y); 
			cout << i + 1 << ". "<< game.name << endl;
		}
		else
		{
			TextColor(8);
			gotoXY(55, y);
			cout << i + 1 << ". ";
		}
		y += 2;
	}
	char chooseAcc;
	bool check = true;
	Game g;
	while (check)
	{
		chooseAcc = _getch();

		switch (chooseAcc)
		{
		case '1':
		{
			if (fileExists("acc1.bin")&&!isFileEmpty("acc1.bin"))
			{
				readResume(g, "acc1.bin", undo, redo);
				check = false;
			}
			break;
		}
		case '2':
		{
			if (fileExists("acc2.bin") && !isFileEmpty("acc2.bin"))
			{
				readResume(g, "acc2.bin", undo, redo);
				check = false;
			}
			break;
		}
		case '3':
		{
			if (fileExists("acc3.bin") && !isFileEmpty("acc3.bin"))
			{
				readResume(g, "acc3.bin", undo, redo);
				check = false;
			}
			break;
		}
		case '4':
		{
			if (fileExists("acc4.bin") && !isFileEmpty("acc4.bin"))
			{
				readResume(g, "acc4.bin", undo, redo);
				check = false;
			}
			break;
		}
		case '5':
		{
			if (fileExists("acc5.bin") && !isFileEmpty("acc5.bin"))
			{
				readResume(g, "acc5.bin", undo, redo);
				check = false;
			}
			break;
		}
		case 8:case 13:case 'e': case 27: GameSet(g); check = false; break;
		}
	}
	g.begin = clock();
	system("cls");
	GamePlay(g, stoi(string(1, chooseAcc)), undo, redo);
}