#pragma once
#include "Cells.h"
#include <list>

class Field						//игровое поле
{
	std::list <Cells::Cell*> data_;	//содержимое поля
	int range;					//дальность просмотра соседних клеток
};
