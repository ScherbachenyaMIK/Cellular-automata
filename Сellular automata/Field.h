#pragma once
#include "Cells.h"
#include <set>
#include <vector>
#include <bitset>
#include <map>

class Comparator
{

public:
	bool operator() (Cells::Cell* const& first, Cells::Cell* const& second) const
	{
		if (first->GetCoordinates().second == second->GetCoordinates().second)
		{
			return first->GetCoordinates().first > second->GetCoordinates().first;
		}
		return first->GetCoordinates().second > second->GetCoordinates().second;
	}
};

class Field												//игровое поле
{
	std::set <Cells::Cell*, Comparator> data_;			//содержимое поля
	int range_;											//дальность просмотра соседних клеток
	std::map<const unsigned int, Cells::Type*> types_;	//существующие типы
	
public:
	Field() = delete;
	explicit Field(int range);
	~Field();

	int GetRange() const;
	Cells::Cell* FindWithCoordinates(std::pair<int, int> coordinates) const;
	void AddCell(Cells::Cell* cell);
	void AddType(Cells::Type* type);

};
