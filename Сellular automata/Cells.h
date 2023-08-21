#pragma once
#include <list>
#include <vector>

class Field;

namespace Cells
{
	class Type
	{
		class Property											//базовый класс
		{
		};

		class AliveCell : public Property						//оживающая/умирающая клетка
		{
			struct Rule
			{
				Type* type;										//тип искомой клетки
				std::vector <int> lower_count;					//от какого количества
				std::vector <int> higher_count;					//до какого количества
				std::vector <int> lower_range;					//от какого радиуса
				std::vector <int> higher_range;					//до какого радиуса
				unsigned char* check_diagonal;					//какие диагональные клетки учитывать
				unsigned char* only_diagonal;					//считать ли диагональные клетки отдельно
				unsigned char* direction;						//в каком направлении искать
				bool expected_result;							//ожидается выполнение/невыполнение этих правил
				bool conditionality;							//условность/безусловность правила
			};

			unsigned int timer_ = 0;
			Rule rule_;

		public:
			AliveCell();
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

		std::vector <Property*> properties_;

	public:

		Type() = delete;
		explicit Type(unsigned char properties);
	};

	class Cell												//класс клетки
	{
		int x_, y_;											//координаты клетки
		std::list <std::list <Cell*> > neighbours_;			//список соседей
		const Type* type_;									//класс типа
		Cell* next_generation_cell_ = nullptr;				//эта же клетка в следующем поколении
	
	public:
		Cell() = delete;
		Cell(std::pair<int, int> coordinates, const Field& field, const Type* type = nullptr);
		Cell(const Cell& other);
		Cell(Cell&& other) noexcept;
		~Cell();

		std::pair<int, int> GetCoordinates() const;
		const Type* GetProperties() const;
		const std::list <std::list <Cell*> >* GetNeighbours() const;
		void AddNeighbour(int index, Cell* cell);

		bool operator== (const Cell& other) const;
		bool operator< (const Cell& other) const;
		bool operator<= (const Cell& other) const;
		bool operator> (const Cell& other) const;
		bool operator>= (const Cell& other) const;
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

	enum DirecionFlags
	{
		Top = 0x01,
		Right = 0x02,
		Down = 0x04,
		Left = 0x08,
		Top_Right = 0x10,
		Down_Right = 0x20,
		Down_Left = 0x40,
		Top_Left = 0x80
	};
}