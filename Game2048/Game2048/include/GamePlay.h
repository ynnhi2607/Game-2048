#pragma once
#include "Library.h"
//Khởi tạo game, cho vào stack undo nếu game mode = 1 hoặc 2.
void init(Game& game, Stack& undo);
//Chuẩn hóa tên nhập vào, xóa các dấu cách đầu cuối tên, giữa 2 từ chỉ có 1 dấu cách.
string trim(const string& str);
//Lưu điểm, lưu resume nếu acc khác 0, giải phóng vùng nhớ đã cấp phát
void ExitGame(Game& g, int acc, Stack& undo, Stack& redo);
//Cài đặt khi chơi game
void GamePlay(Game& g, int acc, Stack& undo, Stack& redo);
//Thêm số mới vào map
void add(Game& g);
//In map ra màn hình
void Print(Game& g);
//Nhập tên, kiểm tra tên hợp lệ
string EnterName(Game g, int& acc);
