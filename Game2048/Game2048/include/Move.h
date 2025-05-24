#pragma once
#include "Library.h"
#include "Struct.h"
void up(Game& g);
void down(Game& g);
void left(Game& g);
void right(Game& g);
void Undo(Stack& ds1, Stack& ds2, Game& g);
void Redo(Stack& ds1, Stack& ds2, Game& g);
