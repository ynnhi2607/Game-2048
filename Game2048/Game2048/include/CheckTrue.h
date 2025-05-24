#pragma once
#include "Library.h"
//KIỂM TRA TÍNH ĐÚNG ĐẮN KHI THUA VÀ THẮNG
//Lưu ý: Phải chơi thêm vài bước để kiếm tra

//Thay hàm init trong hàm GameSet ở file Menu.cpp thành hàm này để kiểm tra tính đúng đắn khi thắng
void initVictory(Game& game, Stack& undo);
//Thay hàm inittrong hàm GameSet ở file Menu.cpp thành hàm này để kiểm tra tính đúng đắn khi thua
void initLose(Game& game, Stack& undo);