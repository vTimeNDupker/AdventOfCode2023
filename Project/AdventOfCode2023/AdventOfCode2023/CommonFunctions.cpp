#include <iostream>
#include <fstream>
#include <string>
#include<list>
using namespace std;

static class CommonFuncAOC2023
{
	public:
		static list<string> Split(string mainString, string delimiter)
		{
			size_t pos = 0;
			string token;
			list<string> data = {};
			string copy = mainString;
			while ((pos = mainString.find(delimiter)) != string::npos) {
				token = mainString.substr(0, pos);
				data.push_back(token);
				mainString.erase(0, pos + delimiter.length());
			}
			data.push_back(mainString);
			return data;
		}

		static string RemoveSubstring(string mainString, string subString)
		{
			size_t pos = 0;
			while ((pos = mainString.find(subString)) != string::npos) {
				mainString.erase(pos, subString.length());
			}
			return mainString;
		}
};