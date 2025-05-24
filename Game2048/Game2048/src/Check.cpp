#include "Check.h"
bool checkupdown(Game g)
{
	for (int j = 0; j < g.size; j++)
	{
		for (int i = 0; i < g.size - 1; i++)
		{
			if (g.m[i][j] == g.m[i + 1][j]) return 0;
		}
	}
	return 1;
}
bool checkrightleft(Game g)
{
	for (int i = 0; i < g.size; i++)
	{
		for (int j = 0; j < g.size - 1; j++)
		{
			if (g.m[i][j] == g.m[i][j + 1]) return 0;
		}
	}
	return 1;
}
bool checkOver(Game g)
{
	//còn ô trống
	if (!checkEmpty(g)) return 0;

	//còn có thể đi lên xuống hoặc trái phải
	if (checkupdown(g) == 0 || checkrightleft(g) == 0) return 0;
	return 1;
}
bool checkEmpty(Game g)
{
	for (int i = 0; i < g.size; i++)
	{
		for (int j = 0; j < g.size; j++)
		{
			//còn ô trống
			if (g.m[i][j] == 0) return 0;
		}
	}
	return 1;
}
bool checkSimilar(Game g1, Game g2)
{
	for (int i = 0; i < g1.size; i++)
	{
		for (int j = 0; j < g1.size; j++)
		{
			if (g1.m[i][j] != g2.m[i][j]) return 0;//g1!=g2
		}
	}
	return 1;//g1=g2
}
bool checkVictory(Game g)
{
	for (int i = 0; i < g.size; i++)
	{
		for (int j = 0; j < g.size; j++)
		{
			// Khi có bất kì 1 số đạt 2048 thì thắng
			if (g.m[i][j] >= 2048) return 1;
		}
	}
	return 0;
}
bool isNameDuplicate(string name, Stack& l, int acc)
{
	//Lấy dữ liệu top-20 từ file
	ReadTopList(l);
	//Kiểm tra xem tên có trùng với top-20 không
	for (Node* i = l.head; i != NULL; i = i->next)
	{
		if (name == i->game.name) return true;
	}

	//Lấy dữ liệu các tên đã đăng kí resume từ file
	int n;
	Stack undo, redo;
	readResumeAcc(n);
	//Kiểm tra xem tên có trùng với tên đã đăng kí resume không
	for (int i = 1; i < n; i++)
	{
		if (i != acc)
		{
			Game game;
			string filename = "acc" + to_string(i) + ".bin";
			readResume(game, filename, undo, redo);
			if (game.name == name) return true;
		}
	}
	return false;
}
bool isNameValid(string name)
{
	//các tên trùng tên đặc biệt
	//Có tham khảo google
	const char* keywords[] =
	{
	"alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept",
	"auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
	"class", "compl", "concept", "const", "consteval", "constexpr", "const_cast", "continue", "co_await",
	"co_return", "co_yield", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum",
	"explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int",
	"long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or",
	"or_eq", "private", "protected", "public", "register", "reinterpret_cast", "requires", "return",
	"short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "synchronized",
	"template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union",
	"unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq","alt","shift",
	"backspace","delete","tab","esc","enter","ctrl","windows","main","remove"
	};
	//Không quá 15 kí tự
	if (name.size() > 15) return false;
	//Không rỗng
	if (name.empty()) return false;
	//Kí tự đầu phải là chữ
	if (!isalpha(name[0])) return false;
	//Chỉ chứa số và chữ
	for (int i = 0; i < name.size(); i++)
	{
		if (!isalnum(name[i]) && !isspace(name[i])) return false;
	}
	//Không trùng tên đặc biệt
	const int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
	for (int i = 0; i < numKeywords; i++)
	{
		if (name == keywords[i])
		{
			return false;
		}
	}
	return true;
}
bool fileExists(const string& fileName)
{
	ifstream file(fileName);
	return file.good();
}
bool isFileEmpty(const string& filePath)
{
	ifstream file(filePath,ios::binary| ios::ate); // mở tệp và đặt con trỏ ở cuối tệp
	return file.tellg() == 0; // trả về true nếu kích thước tệp là 0
}