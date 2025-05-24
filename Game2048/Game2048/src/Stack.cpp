#include "Stack.h"
void deleteStack(Stack& ds)
{
	Node* p;
	while (ds.head != NULL)
	{
		p = ds.head;
		ds.head = ds.head->next;
		deleteGame(p->game);
		delete p;
	}
	ds.size = 0;
}
void insert(Stack& ds, Game g)
{

	Node* t = MakeNode(g);
	if (ds.head == NULL) ds.head = t;
	else
	{
		t->next = ds.head;
		ds.head = t;
	}
	ds.size++;
}
void InsertTopList(Stack& ds, Game g)
{
	Node* t = new Node;
	t->game = g;
	t->next = NULL;
	if (ds.head == NULL) ds.head = t;
	else
	{
		t->next = ds.head;
		ds.head = t;
	}
	ds.size++;
}
Node* MakeNode(Game game)
{
	Game g;
	g.m = new int* [game.size];
	for (int i = 0; i < game.size; i++)
	{
		g.m[i] = new int[game.size];
	}
	g.size = game.size;
	g.score = game.score;
	for (int i = 0; i < g.size; i++)
	{
		for (int j = 0; j < g.size; j++)
		{
			g.m[i][j] = game.m[i][j];
		}
	}
	Node* newnode = new Node;
	newnode->game = g;
	newnode->next = NULL;
	return newnode;
};
void deleteNode(Node*& node)
{
	for (int i = 0; i < node->game.size; i++)
	{
		delete[] node->game.m[i];
	}
	delete[] node->game.m;
	node->game.m = NULL;
	delete node;
	node = NULL;
}
void deleteGame(Game& game)
{
	if (game.m)
	{
		for (int i = 0; i < game.size; ++i) 
		{
			delete[] game.m[i];
		}
		delete[] game.m;
		game.m = nullptr;
	}
}
void sort(Stack& list)
{
	if (list.head == NULL || list.head->next == NULL) return;
	for (Node* i = list.head; i->next != NULL; i = i->next)
	{
		for (Node* j = i->next; j != NULL; j = j->next)
		{

			if (i->game.score < j->game.score)
			{
				int score = i->game.score;
				double time = i->game.time;
				string name = i->game.name;

				i->game.score = j->game.score;
				i->game.name = j->game.name;
				i->game.time = j->game.time;

				j->game.time = time;
				j->game.name = name;
				j->game.score = score;
			}
			else if (i->game.score == j->game.score)
			{
				if (i->game.time > j->game.time)
				{
					int score = i->game.score;
					double time = i->game.time;
					string name = i->game.name;

					i->game.score = j->game.score;
					i->game.name = j->game.name;
					i->game.time = j->game.time;

					j->game.time = time;
					j->game.name = name;
					j->game.score = score;
				}
			}
		}
	}
}