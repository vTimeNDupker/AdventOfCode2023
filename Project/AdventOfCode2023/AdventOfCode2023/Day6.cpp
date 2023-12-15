#include<CommonFunctions.h>
#include <iostream>
#include <fstream>

static class Day6
{
private:

public:
	static int D6P1GetMultWinNumbers(string filePath)
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
		while (getline(file, line))
		{
			data.push_back(line);
		}
		vector<int> Times = CommonFunc::SplitIntoIntsVector((CommonFunc::Split(data.front(), ":")).back(), " ");
		vector<int> Distances = CommonFunc::SplitIntoIntsVector((CommonFunc::Split(data.back(), ":")).back(), " ");
		int Total = 0;
		for (int i = 0 ; i < Times.size(); i++)
		{
			int count = 0;
			for (int j = 1; j < Times[i]; j++)
			{
				if((j * (Times[i] - j) > Distances[i]))
					count++;
			}
			if (Total == 0)
				Total = count;
			else
				Total *= count;
		}
		return Total;
	}
	static int D6P2GetMergedWinNumber(string filePath)
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
		while (getline(file, line))
		{
			data.push_back(line);
		}
		long long Time = stoll(CommonFunc::RemoveSubstring((CommonFunc::Split(data.front(), ":")).back(), " "));
		long long Distance = stoll(CommonFunc::RemoveSubstring((CommonFunc::Split(data.back(), ":")).back(), " "));
		long long count = 0;
		for (long long j = 1; j < Time; j++)
		{
			if ((j * (Time - j) > Distance))
				count++;
		}
		return count;
	}
};
