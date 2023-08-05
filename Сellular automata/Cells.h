#pragma once
#include <list>
#include <vector>

class Field;

namespace Cells
{
	class Property											//базовый класс
	{
	};

	class Cell												//базовый класс
	{
		int x_, y_;											//координаты клетки
		std::list <std::list <Cell*> > neighbours_;			//список соседей
		std::vector <Property*> properties_;				//массив обработчиков свойств клетки
		Cell* next_generation_cell_ = nullptr;				//эта же клетка в следующем поколении
	
	public:
		Cell() = delete;
		Cell(std::pair<int, int> coordinates, const Field& field, unsigned char properties = 0);
		Cell(const Cell& other);
		Cell(Cell&& other) noexcept;
		~Cell();

		std::pair<int, int> GetCoordinates() const;
		const std::vector <Property*>* GetProperties() const;
		const std::list <std::list <Cell*> >* GetNeighbours() const;
		void AddNeighbour(int index, Cell* cell);

		bool operator== (const Cell& other) const;
		bool operator< (const Cell& other) const;
		bool operator<= (const Cell& other) const;
		bool operator> (const Cell& other) const;
		bool operator>= (const Cell& other) const;
	};

	class AliveCell : public Property						//Оживающая/умирающая клетка
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
	
	enum PropertyFlags
	{
		Alive = 0x01,
		Transporting = 0x02,
		Moving = 0x04,
		Generative = 0x08,
		Destroying = 0x10,
		Replacement = 0x20,
		Changeable = 0x40
	};
}