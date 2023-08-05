#include "pch.h"
#include "CppUnitTest.h"
#include "../Сellular automata/Field.h"
#include <random>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CellularautomataTests
{
	TEST_CLASS(CellsTests)
	{
	public:
		
		TEST_METHOD(AloneCellContructorTest)
		{
			Field field(1, { true });
			Cells::Cell cell({1, 0}, field, Cells::PropertyFlags::Alive | Cells::PropertyFlags::Changeable);
			field.AddCell(&cell);
			Assert::AreEqual(cell.GetCoordinates().first, 1);
			Assert::AreEqual(cell.GetCoordinates().second, 0);
			Assert::AreEqual(cell.GetProperties()->size(), static_cast<size_t>(2));
			auto cell_neighbours = cell.GetNeighbours();
			Assert::AreEqual(cell_neighbours->size(), static_cast<unsigned __int64>(2));
			auto iterator = cell_neighbours->begin();
			Assert::AreEqual(iterator->size(), static_cast <size_t>(0));
			++iterator;
			Assert::AreEqual(iterator->size(), static_cast <size_t>(0));
		}
		TEST_METHOD(CellContructorTest)
		{
			Field field(1, { true });
			Cells::Cell cell1({ 1, 0 }, field, Cells::PropertyFlags::Alive | Cells::PropertyFlags::Changeable);
			field.AddCell(&cell1);
			Cells::Cell cell2({ 0, 0 }, field, Cells::PropertyFlags::Alive);
			field.AddCell(&cell2);
			Cells::Cell cell3({ 1, -1 }, field);
			field.AddCell(&cell3);
			Cells::Cell cell4({ -1, 1 }, field, Cells::PropertyFlags::Changeable | Cells::PropertyFlags::Moving | Cells::PropertyFlags::Destroying);
			field.AddCell(&cell4);
			Assert::AreEqual(cell1.GetCoordinates().first, 1);
			Assert::AreEqual(cell1.GetCoordinates().second, 0);
			Assert::AreEqual(cell1.GetProperties()->size(), static_cast<size_t>(2));
			Assert::AreEqual(cell2.GetCoordinates().first, 0);
			Assert::AreEqual(cell2.GetCoordinates().second, 0);
			Assert::AreEqual(cell2.GetProperties()->size(), static_cast<size_t>(1));
			Assert::AreEqual(cell3.GetCoordinates().first, 1);
			Assert::AreEqual(cell3.GetCoordinates().second, -1);
			Assert::AreEqual(cell3.GetProperties()->size(), static_cast<size_t>(0));
			Assert::AreEqual(cell4.GetCoordinates().first, -1);
			Assert::AreEqual(cell4.GetCoordinates().second, 1);
			Assert::AreEqual(cell4.GetProperties()->size(), static_cast<size_t>(3));
			auto cell1_neighbours = cell1.GetNeighbours();
			auto cell2_neighbours = cell2.GetNeighbours();
			auto cell3_neighbours = cell3.GetNeighbours();
			auto cell4_neighbours = cell4.GetNeighbours();
			Assert::AreEqual(cell1_neighbours->size(), static_cast<unsigned __int64>(2));
			Assert::AreEqual(cell2_neighbours->size(), static_cast<unsigned __int64>(2));
			Assert::AreEqual(cell3_neighbours->size(), static_cast<unsigned __int64>(2));
			Assert::AreEqual(cell4_neighbours->size(), static_cast<unsigned __int64>(2));
			auto iterator = cell1_neighbours->begin();
			Assert::AreEqual(iterator->size(), static_cast <size_t>(2)); 
			++iterator;
			Assert::AreEqual(iterator->size(), static_cast <size_t>(0));
			iterator = cell2_neighbours->begin();
			Assert::AreEqual(iterator->size(), static_cast <size_t>(1));
			++iterator;
			Assert::AreEqual(iterator->size(), static_cast <size_t>(2));
			iterator = cell3_neighbours->begin();
			Assert::AreEqual(iterator->size(), static_cast <size_t>(1));
			++iterator;
			Assert::AreEqual(iterator->size(), static_cast <size_t>(1));
			iterator = cell4_neighbours->begin();
			Assert::AreEqual(iterator->size(), static_cast <size_t>(0));
			++iterator;
			Assert::AreEqual(iterator->size(), static_cast <size_t>(1));
		}
	};
	TEST_CLASS(FieldTests)
	{
	public:

		TEST_METHOD(FieldContructorTest1)
		{
			Field field(1, { true });
			Assert::AreEqual(field.GetRange(), 1);
			Assert::IsTrue(field.IsChekableDiagonal(1));
		}
		TEST_METHOD(FieldContructorTest2)
		{
			Field field(5, { true, false, true, true, false });
			Assert::AreEqual(field.GetRange(), 5);
			Assert::IsTrue(field.IsChekableDiagonal(1));
			Assert::IsFalse(field.IsChekableDiagonal(2));
			Assert::IsTrue(field.IsChekableDiagonal(3));
			Assert::IsTrue(field.IsChekableDiagonal(4));
			Assert::IsFalse(field.IsChekableDiagonal(5));
		}
		TEST_METHOD(FieldContructorTest3)
		{
			std::vector <bool> v(25);
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(0, 1);
			for (int i = 0; i < 25; ++i)
			{
				v[i] = dist(gen);
			}
			Field field(25, v);
			Assert::AreEqual(field.GetRange(), 25);
			for (int i = 1; i <= 25; ++i)
			{
				Assert::IsTrue(v[i - 1] == field.IsChekableDiagonal(i));
			}
		}
		TEST_METHOD(FieldContructorTest4)
		{
			std::vector <bool> v(1500);
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(0, 1);
			for (int i = 0; i < 1500; ++i)
			{
				v[i] = dist(gen);
			}
			Field field(1500, v);
			Assert::AreEqual(field.GetRange(), 1500);
			for (int i = 1; i <= 1500; ++i)
			{
				Assert::IsTrue(v[i - 1] == field.IsChekableDiagonal(i));
			}
		}
		TEST_METHOD(FieldCellSearchingTest)
		{
			const int count_neighbours = 4;
			const int count_checkable_cells = 200;
			const int minimum_intersection_size = 100;
			const int minimum_added_cells = 400;
			std::vector <bool> diagonales(count_neighbours);
			std::vector <std::pair <int, int>> coordinates(count_checkable_cells);
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> diagonales_dist(0, 1);
			std::uniform_int_distribution<> coordinates_dist(-21, 21);
			for (int i = 0; i < count_neighbours; ++i)
			{
				diagonales[i] = diagonales_dist(gen);
			}
			for (int i = 0; i < count_checkable_cells; ++i)
			{
				coordinates[i] = { coordinates_dist(gen), coordinates_dist(gen) };
			}
			Field field(count_neighbours, diagonales);
			Assert::AreEqual(field.GetRange(), count_neighbours);
			for (int i = 1; i <= count_neighbours; ++i)
			{
				Assert::IsTrue(diagonales[i - 1] == field.IsChekableDiagonal(i));
			}
			std::vector <std::pair <int, int>> coordinates_intersection;
			std::sort(coordinates.begin(), coordinates.end(), [](const std::pair <int, int>& first, const std::pair <int, int>& second)
			{
					if (first.second == second.second)
					{
						return first.first > second.first;
					}
					return first.second > second.second;
			}
			);
			for (int i = 0; i < minimum_added_cells || coordinates_intersection.size() <= minimum_intersection_size; ++i)
			{
				std::pair<int, int> pair = { coordinates_dist(gen), coordinates_dist(gen) };
				if (std::binary_search(coordinates.begin(), coordinates.end(), pair, [](const std::pair <int, int>& first, const std::pair <int, int>& second)
					{
						if (first.second == second.second)
						{
							return first.first > second.first;
						}
						return first.second > second.second;
					}
				))
				{
					coordinates_intersection.push_back(pair);
				}
				field.AddCell(new Cells::Cell(pair, field));
			}
			std::sort(coordinates_intersection.begin(), coordinates_intersection.end(), [](const std::pair <int, int>& first, const std::pair <int, int>& second)
				{
					if (first.second == second.second)
					{
						return first.first > second.first;
					}
					return first.second > second.second;
				}
			);
			for (int i = 0; i < count_checkable_cells; ++i)
			{
				Assert::IsTrue((field.FindWithCoordinates(coordinates[i]) != nullptr) == std::binary_search(coordinates_intersection.begin(), coordinates_intersection.end(), coordinates[i], [](const std::pair <int, int>& first, const std::pair <int, int>& second)
					{
						if (first.second == second.second)
						{
							return first.first > second.first;
						}
						return first.second > second.second;
					}));
			}
		}
	};
}
