#include "Move.h"
void up(Game& g)
{
	for (int j = 0; j < g.size; j++)
	{
		int pos = 0;
		for (int i = 1; i < g.size; i++)
		{
			if (g.m[i][j] != 0)
			{
				if (g.m[pos][j] == 0)
				{
					g.m[pos][j] = g.m[i][j];
					g.m[i][j] = 0;
				}
				else if (g.m[pos][j] == g.m[i][j])
				{
					g.m[pos][j] = g.m[pos][j] * 2;
					g.score += g.m[pos][j];
					g.m[i][j] = 0;
					pos++;
				}
				else
				{
					pos++;
					if (pos != i)
					{
						g.m[pos][j] = g.m[i][j];
						g.m[i][j] = 0;
					}
				}
			}
		}
	}
}
void down(Game& g)
{
	for (int j = 0; j < g.size; j++)
	{
		int pos = g.size - 1;
		for (int i = g.size - 2; i >= 0; i--)
		{
			if (g.m[i][j] != 0)
			{
				if (g.m[pos][j] == 0)
				{
					g.m[pos][j] = g.m[i][j];
					g.m[i][j] = 0;
				}
				else if (g.m[pos][j] == g.m[i][j])
				{
					g.m[pos][j] = g.m[pos][j] * 2;
					g.score += g.m[pos][j];
					g.m[i][j] = 0;
					pos--;
				}
				else
				{
					pos--;
					if (pos != i)
					{
						g.m[pos][j] = g.m[i][j];
						g.m[i][j] = 0;
					}
				}
			}
		}
	}
}
void left(Game& g)
{
	for (int i = 0; i < g.size; i++)
	{
		int pos = 0;
		for (int j = 1; j < g.size; j++)
		{
			if (g.m[i][j] != 0)
			{
				if (g.m[i][pos] == 0)
				{
					g.m[i][pos] = g.m[i][j];
					g.m[i][j] = 0;
				}
				else if (g.m[i][pos] == g.m[i][j])
				{
					g.m[i][pos] = g.m[i][pos] * 2;
					g.score += g.m[i][pos];
					g.m[i][j] = 0;
					pos++;
				}
				else
				{
					pos++;
					if (pos != j)
					{
						g.m[i][pos] = g.m[i][j];
						g.m[i][j] = 0;
					}
				}
			}
		}
	}
}
void right(Game& g)
{
	for (int i = 0; i < g.size; i++)
	{
		int pos = g.size - 1;
		for (int j = g.size - 2; j >= 0; j--)
		{
			if (g.m[i][j] != 0)
			{
				if (g.m[i][pos] == 0)
				{
					g.m[i][pos] = g.m[i][j];
					g.m[i][j] = 0;
				}
				else if (g.m[i][pos] == g.m[i][j])
				{
					g.m[i][pos] = g.m[i][pos] * 2;
					g.score += g.m[i][pos];
					g.m[i][j] = 0;
					pos--;
				}
				else
				{
					pos--;
					if (pos != j)
					{
						g.m[i][pos] = g.m[i][j];
						g.m[i][j] = 0;
					}
				}
			}
		}
	}
}
void Undo(Stack& undo, Stack& redo, Game& g)
{
	Node* t = undo.head;
	if (g.mode == 2) insert(redo, undo.head->game);
	for (int i = 0; i < g.size; i++)
	{
		for (int j = 0; j < g.size; j++)
		{
			g.m[i][j] = undo.head->next->game.m[i][j];
		}
	}
	g.score = undo.head->next->game.score;
	undo.head = undo.head->next;
	undo.size--;
	delete t;
}
void Redo(Stack& undo, Stack& redo, Game& g)
{
	insert(undo, redo.head->game);
	for (int i = 0; i < g.size; i++)
	{
		for (int j = 0; j < g.size; j++)
		{
			g.m[i][j] = redo.head->game.m[i][j];
		}
	}
	g.score = redo.head->game.score;
	redo.head = redo.head->next;
	redo.size--;
}