#pragma once
#include <string>
#include<list>
using namespace std;
static class CommonFunc
{
public:
	static list<string> Split(string mainString, string delimiter);

	static string RemoveSubstring(string mainString, string subString);
};