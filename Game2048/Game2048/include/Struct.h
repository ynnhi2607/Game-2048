#pragma once
#include "Library.h"
struct Game
{
	int size = 4;
	int** m = NULL;
	int score = 0;
	int mode = 0; //mode=0: tắt undo&redo, mode=1: bật undo, mode 2: bật undo&redo
	string name = "";
	double time = 0; //Lưu thời gian chơi
	clock_t begin; //Lưu thời gian bắt đầu chơi
};
struct Node
{
	Game game;
	Node* next = NULL;
};
struct Stack
{
	Node* head = NULL;
	int size = 0;
};