#include "Field.h"

Field::Field(int range, const std::vector <bool>& v) : range_(range), diagonal_(new unsigned char[(range - 1) / 8 + 1])
{
	for (int i = 0; i < (range - 1) / 8 + 1; ++i)
	{
		diagonal_[i] = 0;
	}
	unsigned char bit = 128;
	int index = 0;
	for (auto i : v)
	{
		if (i)
		{
			diagonal_[index / 8] |= bit;
		}
		++index;
		if (bit != 1)
		{
			bit >>= 1;
		}
		else
		{
			bit = 128;
		}
	}
}

Field::~Field()
{
	delete[] diagonal_;
}

int Field::GetRange() const
{
	return range_;
}

Cells::Cell* Field::FindWithCoordinates(std::pair<int, int> coordinates) const
{
	if (data_.empty())
	{
		return nullptr;
	}
	auto finded = data_.find(new Cells::Cell(coordinates, Field(5)));
	if (finded != data_.end() && (*finded)->GetCoordinates() == coordinates)
	{
		return *finded;
	}
	return nullptr;
}

bool Field::IsChekableDiagonal(int number) const
{
	return diagonal_[(number - 1) / 8] & (1 << (7 - ((number - 1) % 8)));
}

void Field::AddCell(Cells::Cell* cell)
{
	data_.insert(cell);
}
