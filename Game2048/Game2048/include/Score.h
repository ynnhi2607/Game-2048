#pragma once
#include "Library.h"
//Đọc danh sách top-20 list từ file
void ReadTopList(Stack& list);
//In ra danh sách top-20 list
void ShowTopList();
//Tìm điểm cao nhất
int HighScore(Game g);
//Lưu danh sách top-20 list
void SaveTopList(Game g);
