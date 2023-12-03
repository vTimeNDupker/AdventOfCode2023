#include<CommonFunctions.cpp>

static class Day2
{
	private:
		static bool isWithinLimit(string data, int limit, string id)
		{
			size_t pos = 0;
			if ((pos = data.find(id)) != string::npos)
			{
				data.erase(pos, id.length());
				return stoi(data, 0, 10) <= limit;
			}
			return true;
		}
		static int getCubeAmount(string data, string id)
		{
			size_t pos = 0;
			if ((pos = data.find(id)) != string::npos)
			{
				data.erase(pos, id.length());
				return stoi(data, 0, 10);
			}
			return 0;
		}
	public:

		static int D2P1CalcCubeIDs(string filePath)
		{
			ifstream file;
			file.open(filePath, ios::in);

			if (!file.is_open())
			{
				cout << "Error! File Does not Exist";
				cout << "\n";
				return 0;
			}

			string line;
			list<string> data = {};
			while (getline(file, line)) {
				data.push_back(line);
			}
			int redLimit = 12;
			int greenLimit = 13;
			int blueLimit = 14;
			string red = "red";
			string green = "green";
			string blue = "blue";
			int total = 0;
			int id = 1;
			for (list<string>::iterator it = data.begin(); it != data.end(); ++it)
			{
				string line = *it;
				line.erase(0, line.find(": ") + 2);
				line = CommonFuncAOC2023::RemoveSubstring(line, " ");
				list<string> subsets = CommonFuncAOC2023::Split(line, ";");
				bool withinLimits = true;
				for (list<string>::iterator subsetit = subsets.begin(); subsetit != subsets.end(); ++subsetit)
				{
					string subset = *subsetit;
					list<string> cubeColorSet = CommonFuncAOC2023::Split(subset, ",");
					for (list<string>::iterator colorit = cubeColorSet.begin(); colorit != cubeColorSet.end(); ++colorit)
					{
						string colorCubes = *colorit;
						if (!isWithinLimit(colorCubes, redLimit, red) ||
							!isWithinLimit(colorCubes, blueLimit, blue) ||
							!isWithinLimit(colorCubes, greenLimit, green))
						{
							withinLimits = false;
							break;
						}
					}
					if (!withinLimits)
						break;
				}

				if (withinLimits)
					total += id;
				id++;
			}
			return total;
		}
		static int D2P2CalcCubePowers(string filePath)
		{
			ifstream file;
			file.open(filePath, ios::in);

			if (!file.is_open())
			{
				cout << "Error! File Does not Exist";
				cout << "\n";
				return 0;
			}

			string line;
			list<string> data = {};
			while (getline(file, line)) {
				data.push_back(line);
			}
			string red = "red";
			string green = "green";
			string blue = "blue";
			int total = 0;
			for (list<string>::iterator it = data.begin(); it != data.end(); ++it)
			{
				string line = *it;
				line.erase(0, line.find(": ") + 2);
				line = CommonFuncAOC2023::RemoveSubstring(line, " ");
				list<string> subsets = CommonFuncAOC2023::Split(line, ";");

				int redMax = 0;
				int greenMax = 0;
				int blueMax = 0;

				for (list<string>::iterator subsetit = subsets.begin(); subsetit != subsets.end(); ++subsetit)
				{
					string subset = *subsetit;
					list<string> cubeColorSet = CommonFuncAOC2023::Split(subset, ",");
					for (list<string>::iterator colorit = cubeColorSet.begin(); colorit != cubeColorSet.end(); ++colorit)
					{
						string colorCubes = *colorit;
						redMax = max(redMax, getCubeAmount(colorCubes, red));
						blueMax = max(blueMax, getCubeAmount(colorCubes, blue));
						greenMax = max(greenMax, getCubeAmount(colorCubes, green));
					}
				}
				total += redMax * greenMax * blueMax;
			}
			return total;
		}
};