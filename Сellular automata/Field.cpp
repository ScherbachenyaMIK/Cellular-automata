#include "Field.h"

Field::Field(int range) : range_(range)
{
}

Field::~Field()
{
	for (auto i : data_)
	{
		delete i;
	}
	for (auto i : types_)
	{
		delete i.second;
	}
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

void Field::AddCell(Cells::Cell* cell)
{
	data_.insert(cell);
}

void Field::AddType(Cells::Type* type)
{
	types_.insert({ static_cast<unsigned int>(types_.size() + 1), type });
}
