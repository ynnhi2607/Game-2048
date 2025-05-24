#pragma once
#include "Library.h"
#include "Struct.h"
//Lưu 1 trạng thái game
void serializeGame(ofstream& out, const Game& game);
//Đọc 1 trạng thái game
void deserializeGame(ifstream& in, Game& game);
//Lưu số tài khoản đăng kí resume hiện tại
void saveResumeAcc(int n);
//Đọc số tài khoản đăng kí resume hiện tại
void readResumeAcc(int& n);
//Lưu trạng thái game để resume
void saveResume(Game g, string file, Stack undo, Stack redo);
//Đọc trạng thái game để resume
void readResume(Game& g, string file, Stack& undo, Stack& redo);
//Cài đặt khi bấm resume
void Resume();
