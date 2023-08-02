#pragma once
#include <list>
#include <vector>

namespace Cells
{
	class Cell												//базовый класс
	{
		int x_, y_;											//координаты клетки
		std::list <std::list <Cell*> > neighbours_;			//список соседей
		std::vector <Property*> property;					//массив обработчиков свойств клетки
		Cell* next_generation_cell_;						//эта же клетка в следующем поколении
	};

	class Property											//базовый класс
	{
	};

	class StaticCell : public Property						//статичная клетка
	{
	};

	class DynamicCell : public Property						//динамичная (оживающая/умирающая) клетка
	{
	};

	class TransportingCell : public Property				//клетка для переноса других клеток
	{
	};

	class MovingCell : public Property						//двигающаяся клетка
	{
	};

	class GenerativeCell : public Property					//порождающая клетка
	{
	};

	class DestroyingCell : public Property					//уничтожающая клетка
	{
	};

	class ReplacementCell : public Property					//заменяющая клетка
	{
	};

	class ChangeableCell : public Property					//изменяющаяся клетка
	{
	};
}