#include "Field.h"

Cells::Cell::Cell(std::pair<int, int> coordinates, const Field& field, const Type* type) : x_(coordinates.first), y_(coordinates.second), type_(type)
{
	neighbours_.resize(field.GetRange() * 2);					//определение соседей
	auto iterator = neighbours_.begin();
	for (int i = 1; i <= field.GetRange(); ++i)
	{
		if (auto finded = field.FindWithCoordinates({ x_ + i, y_ }))
		{
			iterator->push_back(finded);
			finded->AddNeighbour((i - 1) * 2 + 1, this);
		}
		if (auto finded = field.FindWithCoordinates({ x_, y_ + i }))
		{
			iterator->push_back(finded);
			finded->AddNeighbour((i - 1) * 2 + 1, this);
		}
		if (auto finded = field.FindWithCoordinates({ x_ - i, y_ }))
		{
			iterator->push_back(finded);
			finded->AddNeighbour((i - 1) * 2 + 1, this);
		}
		if (auto finded = field.FindWithCoordinates({ x_, y_ - i }))
		{
			iterator->push_back(finded);
			finded->AddNeighbour((i - 1) * 2 + 1, this);
		}
		++iterator;
		if (auto finded = field.FindWithCoordinates({ x_ + i, y_ + i }))
		{
			iterator->push_back(finded);
			finded->AddNeighbour(i * 2, this);
		}
		if (auto finded = field.FindWithCoordinates({ x_ - i, y_ + i }))
		{
			iterator->push_back(finded);
			finded->AddNeighbour(i * 2, this);
		}
		if (auto finded = field.FindWithCoordinates({ x_ - i, y_ - i }))
		{
			iterator->push_back(finded);
			finded->AddNeighbour(i * 2, this);
		}
		if (auto finded = field.FindWithCoordinates({ x_ + i, y_ - i }))
		{
			iterator->push_back(finded);
			finded->AddNeighbour(i * 2, this);
		}
		++iterator;
	}
}

Cells::Cell::Cell(const Cell& other) : x_(other.x_), y_(other.y_), neighbours_(other.neighbours_), type_(other.type_)
{
}

Cells::Cell::Cell(Cell&& other) noexcept : x_(other.x_), y_(other.y_), type_(other.type_)
{
	other.x_ = NULL;
	other.y_ = NULL;
	std::swap(neighbours_, other.neighbours_);
	other.type_ = nullptr;
}

Cells::Cell::~Cell()
{
	delete next_generation_cell_;
}

std::pair<int, int> Cells::Cell::GetCoordinates() const
{
	return { x_, y_ };
}

const Cells::Type* Cells::Cell::GetProperties() const
{
	return type_;
}

const std::list<std::list<Cells::Cell*>>* Cells::Cell::GetNeighbours() const
{
	return &neighbours_;
}

void Cells::Cell::AddNeighbour(int index, Cell* cell)
{
	auto iterator = neighbours_.begin();
	for (int i = 1; i < index; ++i, ++iterator);
	iterator->push_back(cell);
}

bool Cells::Cell::operator==(const Cell& other) const
{
	return x_ == other.x_ && y_ == other.y_;
}

bool Cells::Cell::operator<(const Cell& other) const
{
	if (y_ == other.y_)
	{
		return x_ < other.x_;
	}
	return y_ < other.y_;
}

bool Cells::Cell::operator<=(const Cell& other) const
{
	return (*this == other) || (*this < other);
}

bool Cells::Cell::operator>(const Cell& other) const
{
	return !(*this <= other);
}

bool Cells::Cell::operator>=(const Cell& other) const
{
	return !(*this < other);
}

Cells::Type::Type(unsigned char properties)
{
	if ((properties & Cells::PropertyFlags::Alive) != 0)		//определение свойств
	{
		properties_.push_back(new AliveCell);
	}
	if ((properties & Cells::PropertyFlags::Changeable) != 0)
	{
		properties_.push_back(new ChangeableCell);
	}
	if ((properties & Cells::PropertyFlags::Destroying) != 0)
	{
		properties_.push_back(new DestroyingCell);
	}
	if ((properties & Cells::PropertyFlags::Generative) != 0)
	{
		properties_.push_back(new GenerativeCell);
	}
	if ((properties & Cells::PropertyFlags::Moving) != 0)
	{
		properties_.push_back(new MovingCell);
	}
	if ((properties & Cells::PropertyFlags::Replacement) != 0)
	{
		properties_.push_back(new ReplacementCell);
	}
	if ((properties & Cells::PropertyFlags::Transporting) != 0)
	{
		properties_.push_back(new TransportingCell);
	}
}

//bool Cells::Type::AliveCell::Rule::IsChekableDiagonal(int number) const
//{
//	return diagonal_[(number - 1) / 8] & (1 << (7 - ((number - 1) % 8)));
//}
//
//Cells::Type::AliveCell::AliveCell(const std::vector<bool>& v) : diagonal_(new unsigned char[(range - 1) / 8 + 1])
//{
//	for (int i = 0; i < (range - 1) / 8 + 1; ++i)
//	{
//		diagonal_[i] = 0;
//	}
//	unsigned char bit = 128;
//	int index = 0;
//	for (auto i : v)
//	{
//		if (i)
//		{
//			diagonal_[index / 8] |= bit;
//		}
//		++index;
//		if (bit != 1)
//		{
//			bit >>= 1;
//		}
//		else
//		{
//			bit = 128;
//		}
//	}
//}

Cells::Type::AliveCell::AliveCell()
{
	//Rule(const std::vector <bool>&v = std::vector <bool>());
}
