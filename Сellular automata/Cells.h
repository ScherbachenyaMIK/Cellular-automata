#pragma once
#include <list>
#include <vector>

class Field;

namespace Cells
{
	class Type
	{
		class Property											//������� �����
		{
		};

		class AliveCell : public Property						//���������/��������� ������
		{
			struct Rule
			{
				Type* type;										//��� ������� ������
				std::vector <int> lower_count;					//�� ������ ����������
				std::vector <int> higher_count;					//�� ������ ����������
				std::vector <int> lower_range;					//�� ������ �������
				std::vector <int> higher_range;					//�� ������ �������
				unsigned char* check_diagonal;					//����� ������������ ������ ���������
				unsigned char* only_diagonal;					//������� �� ������������ ������ ��������
				unsigned char* direction;						//� ����� ����������� ������
				bool expected_result;							//��������� ����������/������������ ���� ������
				bool conditionality;							//����������/������������� �������
			};

			unsigned int timer_ = 0;
			Rule rule_;

		public:
			AliveCell();
		};

		class TransportingCell : public Property				//������ ��� �������� ������ ������
		{
		};

		class MovingCell : public Property						//����������� ������
		{
		};

		class GenerativeCell : public Property					//����������� ������
		{
		};

		class DestroyingCell : public Property					//������������ ������
		{
		};

		class ReplacementCell : public Property					//���������� ������
		{
		};

		class ChangeableCell : public Property					//������������ ������
		{
		};

		std::vector <Property*> properties_;

	public:

		Type() = delete;
		explicit Type(unsigned char properties);
	};

	class Cell												//����� ������
	{
		int x_, y_;											//���������� ������
		std::list <std::list <Cell*> > neighbours_;			//������ �������
		const Type* type_;									//����� ����
		Cell* next_generation_cell_ = nullptr;				//��� �� ������ � ��������� ���������
	
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