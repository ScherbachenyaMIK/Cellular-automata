#pragma once
#include "Cells.h"
#include <set>
#include <vector>
#include <bitset>

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
	unsigned char* diagonal_;							//какие диагональные клетки считать соседними
	
public:
	Field() = delete;
	explicit Field(int range, const std::vector <bool>& v = std::vector <bool>());
	~Field();

	int GetRange() const;
	Cells::Cell* FindWithCoordinates(std::pair<int, int> coordinates) const;
	bool IsChekableDiagonal(int number) const;
	void AddCell(Cells::Cell* cell);

};
