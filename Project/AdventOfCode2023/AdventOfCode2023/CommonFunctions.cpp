#include <iostream>
#include <fstream>
#include <CommonFunctions.h>

list<string> CommonFunc::Split(string mainString, string delimiter)
{
	size_t pos = 0;
	string token;
	list<string> data = {};
	string copy = mainString;
	while ((pos = mainString.find(delimiter)) != string::npos) {
		token = mainString.substr(0, pos);
		if(token.size() > 0)
			data.push_back(token);
		mainString.erase(0, pos + delimiter.length());
	}
	data.push_back(mainString);
	return data;
}

list<int> CommonFunc::SplitIntoInts(string mainString, string delimiter)
{
	size_t pos = 0;
	string token;
	list<int> data = {};
	string copy = mainString;
	while ((pos = mainString.find(delimiter)) != string::npos) {
		token = mainString.substr(0, pos);
		if (token.size() > 0)
			data.push_back(stoi(token, 0, 10));
		mainString.erase(0, pos + delimiter.length());
	}
	data.push_back(stoi(mainString, 0, 10));
	return data;
}


vector<int> CommonFunc::SplitIntoIntsVector(string mainString, string delimiter)
{
	size_t pos = 0;
	string token;
	vector<int> data = {};
	string copy = mainString;
	while ((pos = mainString.find(delimiter)) != string::npos) {
		token = mainString.substr(0, pos);
		if (token.size() > 0)
			data.push_back(stoi(token, 0, 10));
		mainString.erase(0, pos + delimiter.length());
	}
	data.push_back(stoi(mainString, 0, 10));
	return data;
}

list<long long> CommonFunc::SplitIntoLongLongs(string mainString, string delimiter)
{
	size_t pos = 0;
	string token;
	list<long long> data = {};
	string copy = mainString;
	while ((pos = mainString.find(delimiter)) != string::npos) {
		token = mainString.substr(0, pos);
		if (token.size() > 0)
		{
			long long val = stoll(token, 0, 10);
			data.push_back(val);
		}
		mainString.erase(0, pos + delimiter.length());
	}
	data.push_back(stoll(mainString, 0, 10));
	return data;
}

list<unsigned long> CommonFunc::SplitIntoUnsignedLongs(string mainString, string delimiter)
{
	size_t pos = 0;
	string token;
	list<unsigned long> data = {};
	string copy = mainString;
	while ((pos = mainString.find(delimiter)) != string::npos) {
		token = mainString.substr(0, pos);
		if (token.size() > 0)
		{
			unsigned long val = stoul(token, 0, 10);
			data.push_back(val);
		}
		mainString.erase(0, pos + delimiter.length());
	}
	data.push_back(stoul(mainString, 0, 10));
	return data;
}

string CommonFunc::RemoveSubstring(string mainString, string subString)
{
	size_t pos = 0;
	while ((pos = mainString.find(subString)) != string::npos) {
		mainString.erase(pos, subString.length());
	}
	return mainString;
}