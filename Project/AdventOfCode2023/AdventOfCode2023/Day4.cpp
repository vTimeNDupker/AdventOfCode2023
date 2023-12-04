#include<CommonFunctions.h>
#include<set>
#include <iostream>
#include <fstream>
#include <map>

static class Day4
{
	private:
	public:
		static int D4P1CalcCardPoints(string filePath)
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
			int total = 0;
			while (getline(file, line))
			{
				data.push_back(line);
				line.erase(0, line.find(':') + 2);
				list<string> cardNumbers = CommonFunc::Split(line, " | ");

				list<string> winningNumbersStrings = CommonFunc::Split(cardNumbers.front(), " ");
				set<int> winningNumbers;
				for (auto element : winningNumbersStrings)
					winningNumbers.insert(stoi(element, 0, 10));

				list<string> numbersStrings = CommonFunc::Split(cardNumbers.back(), " ");
				set<int> numbers;
				for (auto element : numbersStrings)
					numbers.insert(stoi(element, 0, 10));

				int value = 0;

				for (auto element : numbers)
				{
					if (winningNumbers.find(element) != winningNumbers.end())
					{
						if (value == 0)
							value = 1;
						else
							value *= 2;
					}
				}
				total += value;
			}
			return total;
		}
		static int D4P2CalcScratchCards(string filePath)
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
			int total = 0;
			while (getline(file, line))
			{
				data.push_back(line);
			}
			list<string>::reverse_iterator iter = data.rbegin();

			int id = data.size() - 1;
			map<int, int> cardValues;
			for (; iter != data.rend(); ++iter)
			{
				line = *iter;
				line.erase(0, line.find(':') + 2);
				list<string> cardNumbers = CommonFunc::Split(line, " | ");

				list<string> winningNumbersStrings = CommonFunc::Split(cardNumbers.front(), " ");
				set<int> winningNumbers;
				for (auto element : winningNumbersStrings)
					winningNumbers.insert(stoi(element, 0, 10));

				list<string> numbersStrings = CommonFunc::Split(cardNumbers.back(), " ");
				set<int> numbers;
				for (auto element : numbersStrings)
					numbers.insert(stoi(element, 0, 10));

				int value = 1;
				int matches = 0;
				for (auto element : numbers)
				{
					if (winningNumbers.find(element) != winningNumbers.end())
					{
						matches++;
						if (cardValues.count(id+ matches) != 0)
						{
							value += cardValues[id + matches];
						}
					}
				}
				total += value;
				cardValues[id] = value;
				id--;
			}
			return total;
		}
};