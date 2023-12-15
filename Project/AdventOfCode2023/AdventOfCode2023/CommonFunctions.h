#pragma once
#include <string>
#include<list>
#include<vector>
using namespace std;
static class CommonFunc
{
public:
	static list<string> Split(string mainString, string delimiter);
	static list<int> SplitIntoInts(string mainString, string delimiter);
	static vector<int> SplitIntoIntsVector(string mainString, string delimiter);
	static list<long long> SplitIntoLongLongs(string mainString, string delimiter);
	static list<unsigned long> SplitIntoUnsignedLongs(string mainString, string delimiter);

	static string RemoveSubstring(string mainString, string subString);
};