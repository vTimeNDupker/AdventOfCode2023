#include <iostream>
#include <fstream>
#include <ctype.h>
#include<list>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
#include <map>

static class Day1
{
	public:
		static int D1CalcInputSum(string filePath, bool checkForSpelledNumbers)
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
			while (getline(file, line)) {
				//cout << line << endl;
				data.push_back(line);
			}

			/*if (file.is_open()) { // always check whether the file is open
				file >> data; // pipe file's content into stream
				std::cout << data; // pipe stream's content to standard output
				cout << "\n";
			}*/

			int total = 0;

			for (std::list<string>::iterator it = data.begin(); it != data.end(); ++it)
			{
				std::string line = *it;

				string lineNumbers = "";
				string currentSpelledNumber = "";
				for (int j = 0; j < line.length(); j++)
				{

					if (isdigit(line[j]))
					{
						if (checkForSpelledNumbers)
						{
							lineNumbers += CheckSpelledNumbers(currentSpelledNumber);
							currentSpelledNumber = "";
						}
						lineNumbers += line[j];
					}
					else if (checkForSpelledNumbers)
						currentSpelledNumber += line[j];
				}
				if (checkForSpelledNumbers)
					lineNumbers += CheckSpelledNumbers(currentSpelledNumber);


				if (lineNumbers.length() == 0)
					cout << "Error! Line contains no digits\n";
				/*else if (lineNumbers.length() < 2)
				{
					cout << "Line only contains 1 number\n";
					int val = lineNumbers[0] - '0';

					cout << val;
					cout << "\n";
					total += val;
				}*/
				else
				{
					char str[] = { lineNumbers[0], lineNumbers[lineNumbers.length() - 1] };
					char* output;
					long result = strtol(str, &output, 10);

					int val = (int)(result);
					//cout << val;
					//cout << "\n";
					total += val;
				}
			}

			return total;
		}

		static string CheckSpelledNumbers(string input)
		{
			string result = "";
			std::map<int, char> my_map = {};
			int value = 0;
			list<string> spelledNumbers = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
			char numberChars[] = { '1', '2','3','4','5','6','7','8','9' };
			for (std::list<string>::iterator it = spelledNumbers.begin(); it != spelledNumbers.end(); ++it)
			{
				std::string sn = *it;
				bool done = false;
				int pos = -1;
				while (!done)
				{
					pos = input.find(sn, pos+1);
					if (pos != std::string::npos) {
						my_map[pos] = numberChars[value];
					}
					else
						done = true;
				}
				value++;
			}
			for (auto element : my_map) {
				result += element.second;
			}
			return result;
		}
};