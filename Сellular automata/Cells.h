#pragma once
#include <list>
#include <vector>

namespace Cells
{
	class Cell												//������� �����
	{
		int x_, y_;											//���������� ������
		std::list <std::list <Cell*> > neighbours_;			//������ �������
		std::vector <Property*> property;					//������ ������������ ������� ������
		Cell* next_generation_cell_;						//��� �� ������ � ��������� ���������
	};

	class Property											//������� �����
	{
	};

	class StaticCell : public Property						//��������� ������
	{
	};

	class DynamicCell : public Property						//���������� (���������/���������) ������
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
}