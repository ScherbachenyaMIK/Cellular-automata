#pragma once
#include <list>
#include <vector>

class Field;

namespace Cells
{
	class Property											//������� �����
	{
	};

	class Cell												//������� �����
	{
		int x_, y_;											//���������� ������
		std::list <std::list <Cell*> > neighbours_;			//������ �������
		std::vector <Property*> properties_;				//������ ������������ ������� ������
		Cell* next_generation_cell_ = nullptr;				//��� �� ������ � ��������� ���������
	
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

	class AliveCell : public Property						//���������/��������� ������
	{
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