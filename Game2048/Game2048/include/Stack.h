#pragma once
#include "Library.h"
//Xóa Stack (undo, redo)
void deleteStack(Stack& ds);
//Thêm Node vào stack (undo, redo)
void insert(Stack& ds, Game g);
//Thêm Node vào stack (Top-20 list)
void InsertTopList(Stack& ds, Game g);
//Tạo Node mới (undo, redo)
Node* MakeNode(Game game);
//Xóa Node (undo, redo)
void deleteNode(Node*& node);
//Xóa Game
void deleteGame(Game& game);
//Sắp xếp top-20 theo thứ tự điểm và thời gian
void sort(Stack& list);