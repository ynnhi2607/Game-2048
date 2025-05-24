#pragma once
#include "Library.h"
using namespace std;
//Tham khảo Google
//Dùng để tới vị trí có tọa độ x,y để cout
void gotoXY(int x, int y);
//Cài đặt màu chữ
void TextColor(int x);
//Xóa con trỏ "_"
void ShowCur(bool CursorVisibility);
//Cài đặt màu chữ cho từng số
void SetColor(int x);
//Tạo các chữ to như 2048, Resume,... ở tọa độ startX, startY
void WordArt(string chu, int startX, int startY);