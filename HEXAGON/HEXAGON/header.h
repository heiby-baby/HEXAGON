#pragma once
#define PI 3.14159265358979323846
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "graficfunc.h"
#include "func.h"
#include "funcForMinimax.h"
struct gamestats {
	bool move = true; //ход игрока
	bool inActive = false;
	int vertexMove = -1;
	int Final = 0;
};

