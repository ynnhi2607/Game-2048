#include "Score.h"
void ReadTopList(Stack& list)
{
	//Tạo file nếu chưa có file
	string filename = "rank.bin";
	ofstream out(filename, ios::binary | ios::app);
	out.close();

	ifstream in(filename, ios::binary);
	if (!in)
	{
		cout << "Can not open file for reading!" << endl;

	}
	in.seekg(0, ios::end);  // Di chuyển con trỏ tới cuối tệp
	if (in.tellg() == 0)
	{  // Kiểm tra vị trí con trỏ, nếu là 0 thì tệp rỗng
		return;
	}
	else
	{
		in.seekg(0, ios::beg);
	}// Di chuyển con trỏ về đầu tệp để bắt đầu đọc
	while (!in.eof())
	{
		Game g;
		size_t namesize;
		in.read(reinterpret_cast<char*>(&namesize), sizeof(namesize));
		g.name.resize(namesize);
		in.read(&g.name[0], namesize);
		in.read(reinterpret_cast<char*>(&g.score), sizeof(g.score));
		in.read(reinterpret_cast<char*>(&g.time), sizeof(g.time));
		InsertTopList(list, g);
	}
	
	//Vì đọc xong nó sẽ bị dư 1 Node nên phải xóa
	Node* t = list.head;
	list.head = list.head->next;
	delete t;
	sort(list);
	in.close();
}
void ShowTopList()
{
	system("cls");
	cout <<endl<<endl<<endl<<endl<< "    Press ENTER or BACKSPACE"<<endl<<"    to return MENU";
	string asciiArt =
		" _________    ___   _______     _____     ____   \n"
		"|  _   _  | .'   `.|_   __ \\   / ___ `. .'    '. \n"
		"|_/ | | \\_|/  .-.  \\ | |__) | |_/___) ||  .--.  |\n"
		"    | |    | |   | | |  ___/   .'____.'| |    | |\n"
		"   _| |_   \\  `-'  /_| |_     / /_____ |  `--'  |\n"
		"  |_____|   `.___.'|_____|    |_______| '.____.' \n";
	WordArt(asciiArt, 37, 1);
	Stack l;
	ReadTopList(l);
	gotoXY(0, 8);
	int index = 1;
	TextColor(11);
	cout << setw(35) << "Rank" << setw(20) << "Name" << setw(15) << "Score" << setw(20) << "Time" << endl;
	TextColor(15);
	if (l.head == NULL)
	{
		TextColor(4);
		gotoXY(55, 12);
		cout << "No rating yet!";
		TextColor(15);
		return;
	}
	for (Node* i = l.head; i != NULL; i = i->next)
	{
		cout << setw(35) << index << setw(20) << i->game.name << setw(15) << i->game.score << setw(20) <<SectoString(i->game.time) << endl;
		index++;
	}
}
int HighScore(Game g)
{
	Stack l;
	ReadTopList(l);
	int max = 0;
	for (Node*i=l.head;i!=NULL;i=i->next)
	{
		if (i->game.score > max) max = i->game.score;
	}
	if (g.score > max) return g.score;
	return max;
}
void SaveTopList(Game g)
{
	Stack l;
	ReadTopList(l);
	//xóa tên khi trùng trong trường hợp chơi lại bằng resume
	if (l.head != NULL)
	{
		if (l.head->game.name == g.name)
		{
			if (l.head->game.score > g.score)
			{
				g.score = l.head->game.score;
				g.time = l.head->game.time;
			}
			Node* p = l.head;
			l.head = l.head->next;
			delete p;
			l.size--;
		}
		else
		{
			for (Node* i = l.head; i->next != NULL; i = i->next)
			{
				if (i->next->game.name == g.name)
				{
					if (i->next->game.score > g.score)
					{
						g.score = i->next->game.score;
						g.time = i->next->game.time;
					}
					Node* p = i->next;
					i->next = i->next->next;
					delete p;
					l.size--;
					break;
				}
			}
		}
	}
	else//Nếu chưa có người nào
	{
		gotoXY(0, 2 * g.size + 3);
		TextColor(14);
		cout << "Your rank: " << 1 << endl;
		TextColor(15);
	}
	//Tìm hạng
	int index = 0;
	bool check = false;
	//Nếu hạng nằm trong khoảng top đang có
	for (Node* i = l.head; i != NULL; i = i->next)
	{
		if (g.score > i->game.score || (g.score == i->game.score && g.time < i->game.time))
		{
			gotoXY(0, 2 * g.size + 3);
			TextColor(14);
			cout << "Your rank: " << index + 1 << endl;
			TextColor(15);
			check = true;
			break;
		}
		index++;
	}
	if (!check)
	{
		if (l.size == 20)
		{
			gotoXY(0, 2 * g.size + 3);
			TextColor(13);
			cout << "No rank." << endl;
			TextColor(15);
		} 
		else
		{
			gotoXY(0, 2 * g.size + 3);
			TextColor(14);
			cout << "Your rank: " << index + 1 << endl;
			TextColor(15);
		}
	}
	//Thêm acc mới vào list nếu nằm trong top-20
	if (l.size >= 20)
	{
		for (Node* i = l.head; i != NULL; i = i->next)
		{
			if (g.score > i->game.score || (g.score == i->game.score && g.time < i->game.time))
			{
				InsertTopList(l, g);
				sort(l);
				//Xóa Node cuối
				Node* k = l.head;
				while (k->next->next != NULL) k = k->next;
				delete k->next;
				k->next = NULL;
				l.size--;
			
				break;
			}
		}
	}
	else
	{
		InsertTopList(l, g);
		sort(l);
	}
	//ghi lại vào file
	ofstream output("rank.bin", ios::binary);
	if (!output)
	{
		cout << "Can not open file for writing!\n";
		return;
	}
	Node* t = l.head;
	while (t != NULL)
	{
		size_t sizeofname = t->game.name.size();
		output.write(reinterpret_cast<const char*>(&sizeofname), sizeof(sizeofname));
		output.write(t->game.name.c_str(), sizeofname);

		output.write(reinterpret_cast<const char*>(&t->game.score), sizeof(t->game.score));
		output.write(reinterpret_cast<const char*>(&t->game.time), sizeof(t->game.time));
		t = t->next;
	}
	output.close();

	//xóa list đã tạo
	Node* p;
	while (l.head != NULL)
	{
		p = l.head;
		l.head = l.head->next;
		delete p;
	}
	l.size = 0;
}