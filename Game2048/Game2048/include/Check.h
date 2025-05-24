#pragma once
#include "Library.h"
#include "Struct.h"
//khi map đầy, kiểm tra xem còn có thể đi lên hay xuống được không, nếu không thể thì trả về true.
bool checkupdown(Game g);
//khi map đầy, kiểm tra xem còn có thể đi trái hay phải được không, nếu không thể thì trả về true.
bool checkrightleft(Game g);
//Kiểm tra xem game đã kết thúc chưa, game kết thúc khi:
//1. Không còn ô trống
//2. Không thể di chuyển được nữa
//Nếu game over trả về true.
bool checkOver(Game g);
//Kiểm tra xem còn ô trống nào không, nếu không còn trả về true.
bool checkEmpty(Game g);
//Kiểm tra map của g1 và g2 có giống nhau không (để add số), nếu giống trả về true.
bool checkSimilar(Game g1, Game g2);
//Kiểm tra game đã thắng chưa, game thắng khi có ít nhất 1 số đạt 2048, nếu thắng trả về true.
bool checkVictory(Game g);
//Kiểm tra tên xem có trùng với top-20 và các acc đã đăng kí resume không, nếu trùng trả về true.
bool isNameDuplicate(string name, Stack& l,int acc);
//Kiểm tra tên có hợp lệ không, tên hợp lệ là tên không trùng với các hàm trong c++, 
//không quá 15 kí tự, không rỗng, kí tự đầu tiên phải là chữ cái, chỉ được chứa chữ cái và số.
//Nếu hợp lệ trả về true.
bool isNameValid(string name);
//Kiểm tra file có tồn tại không, nếu tồn tại trả về true.
bool fileExists(const string& fileName);
bool isFileEmpty(const string& filePath);
