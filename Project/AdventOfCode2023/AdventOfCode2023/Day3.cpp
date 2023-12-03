#include<vector>
#include <iostream>
#include <fstream>
#include <string>
#include<list>
#include<set>
using namespace std;
#include <map>
//#include<CommonFunctions.cpp>

static class Day3
{
	private:
		inline static vector< vector<char>> grid;
		inline static int width;
		inline static int height;

		inline static set<int> tempGearIds;
		inline static map<int, list<int>> gearIds;

		static bool CheckForSymbol(vector< vector<char>> grid, int x, int y, int width, int height)
		{
			if (x < 0 || x >= width || y < 0 || y >= height)
				return false;
			return (!isdigit(grid[y][x]) && grid[y][x] != '.');
		}
		static bool CheckForSymbols(vector< vector<char>> grid, int i, int j, int width, int height)
		{
			return (CheckForSymbol(grid, i - 1, j - 1, width, height) ||
				CheckForSymbol(grid, i, j - 1, width, height) ||
				CheckForSymbol(grid, i + 1, j - 1, width, height) ||

				CheckForSymbol(grid, i - 1, j, width, height) ||
				CheckForSymbol(grid, i + 1, j, width, height) ||

				CheckForSymbol(grid, i - 1, j + 1, width, height) ||
				CheckForSymbol(grid, i, j + 1, width, height) ||
				CheckForSymbol(grid, i + 1, j + 1, width, height));
		}

		static void CheckForGear(vector< vector<char>> grid, int x, int y, int width, int height)
		{
			if (x < 0 || x >= width || y < 0 || y >= height)
				return;

			if (grid[y][x] == '*')
			{
				int id = (y * width) + x;
				if (tempGearIds.find(id) == tempGearIds.end()) {
					tempGearIds.insert(id);
				}
			}
		}
		static void CheckForGears(vector< vector<char>> grid, int i, int j, int width, int height)
		{
			CheckForGear(grid, i - 1, j - 1, width, height);
			CheckForGear(grid, i, j - 1, width, height);
			CheckForGear(grid, i + 1, j - 1, width, height);

			CheckForGear(grid, i - 1, j, width, height);
			CheckForGear(grid, i + 1, j, width, height);

			CheckForGear(grid, i - 1, j + 1, width, height);
			CheckForGear(grid, i, j + 1, width, height);
			CheckForGear(grid, i + 1, j + 1, width, height);
		}

		static void PopulateGears(int partNumber)
		{
			set<int>::iterator itr;
			for (itr = tempGearIds.begin(); itr != tempGearIds.end(); itr++)
			{
				int id = *itr;
				if (gearIds.count(id) == 0)
				{
					list<int> list = { partNumber };
					gearIds[id] = list;
				}
				else
				{
					gearIds[id].push_back(partNumber);
				}
			}
			tempGearIds.clear();
		}
	public:
		static int D3GetGrid(string filePath)
		{
			std::ifstream file;
			file.open(filePath, ios::in);

			if (!file.is_open())
			{
				cout << "Error! File Does not Exist";
				cout << "\n";
				return 0;
			}

			string line;
			std::list<string> data = {};
			int id = 0;
			while (getline(file, line))
			{
				data.push_back(line);
				vector<char> vec;
				grid.push_back(vec);
				for (std::string::size_type i = 0; i < line.size(); ++i) {
					grid[id].push_back(line[i]);
				}
				id++;
			}
			width = line.size();
			height = data.size();
		}


		static int D3P1CalcPartNumbers()
		{
			int total = 0;
			for (int j = 0; j < height; j++)
			{
				string digits;
				bool hasDigits = false;
				bool foundSymbol = false;
				for (int i = 0; i < width; i++)
				{
					if (isdigit(grid[j][i]))
					{
						hasDigits = true;
						digits.push_back(grid[j][i]);
						if (!foundSymbol)
							foundSymbol = CheckForSymbols(grid, i, j, width, height);
					}
					else if (hasDigits)
					{
						if (foundSymbol)
							total += stoi(digits, 0, 10);
						digits = "";
						foundSymbol = false;
						hasDigits = false;
					}
				}
				if (hasDigits && foundSymbol)
					total += stoi(digits, 0, 10);
			}
			return total;
		}

		static int D3P2GetGearRatios()
		{
			for (int j = 0; j < height; j++)
			{
				string digits;
				bool hasDigits = false;
				for (int i = 0; i < width; i++)
				{
					if (isdigit(grid[j][i]))
					{
						hasDigits = true;
						digits.push_back(grid[j][i]);
						CheckForGears(grid, i, j, width, height);
					}
					else if (hasDigits)
					{
						int num = stoi(digits, 0, 10);
						PopulateGears(num);
						digits = "";
						hasDigits = false;
					}
				}
				if (hasDigits)
				{
					int num = stoi(digits, 0, 10);
					PopulateGears(num);
				}
			}

			int total = 0;
			for (auto element : gearIds)
			{
				if (element.second.size() == 2)
					total += element.second.front() * element.second.back();
			}
			return total;
		}
};