#pragma once
#include "Cells.h"
#include <list>

class Field						//������� ����
{
	std::list <Cells::Cell*> data_;	//���������� ����
	int range;					//��������� ��������� �������� ������
};
