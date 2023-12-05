#include<CommonFunctions.h>
#include <iostream>
#include <fstream>


class ConversionRange
{
	public:
		unsigned long source;
		unsigned long destination;
		unsigned long length;
};

static class Day5
{
	private:
		static list<ConversionRange> GetConversionsFromFile(std::ifstream& file)
		{
			list<ConversionRange> ranges;
			string line;
			while (getline(file, line))
			{
				if (line.size() == 0)
					return ranges;
				list<unsigned long> conversionString = CommonFunc::SplitIntoUnsignedLongs(line, " ");
				unsigned long id = 0;
				ConversionRange conversion;
				for (auto element : conversionString)
				{
					if (id == 0)
						conversion.destination = element;
					if (id == 1)
						conversion.source = element;
					if (id == 2)
						conversion.length = element;
					id++;
				}

				ranges.push_back(conversion);
			}
			return ranges;
		}

		static unsigned long Convert(list<ConversionRange> ranges, unsigned long value)
		{
			unsigned long newValue;

			newValue = value;
			for (auto element : ranges)
			{
				if (value < element.source)
					continue;
				if (value >= (element.source + element.length))
					continue;
				newValue = (element.destination - element.source) + value;
				break;
			}

			return newValue;
		}

	public:
		static unsigned long D5P1GetLowestLocation(string filePath)
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
			string seedsString;
			getline(file, seedsString);
			seedsString.erase(0, seedsString.find(':') + 2);
			list<unsigned long> seeds = CommonFunc::SplitIntoUnsignedLongs(seedsString, " ");
			list<ConversionRange> seedToSoil;
			list<ConversionRange> soilToFertilizer;
			list<ConversionRange> fertilizerToWater;
			list<ConversionRange> waterToLight;
			list<ConversionRange> lightToTemperature;
			list<ConversionRange> temperatureToHumidity;
			list<ConversionRange> humidityToLocation;

			while (getline(file, line))
			{
				data.push_back(line);
				if (line.size() == 0)
					continue;
				if (line.find("seed-to-soil") != string::npos)
					seedToSoil = GetConversionsFromFile(file);
				if (line.find("soil-to-fertilizer") != string::npos)
					soilToFertilizer = GetConversionsFromFile(file);
				if (line.find("fertilizer-to-water") != string::npos)
					fertilizerToWater = GetConversionsFromFile(file);
				if (line.find("water-to-light") != string::npos)
					waterToLight = GetConversionsFromFile(file);
				if (line.find("light-to-temperature") != string::npos)
					lightToTemperature = GetConversionsFromFile(file);
				if (line.find("temperature-to-humidity") != string::npos)
					temperatureToHumidity = GetConversionsFromFile(file);
				if (line.find("humidity-to-location") != string::npos)
					humidityToLocation = GetConversionsFromFile(file);
			}
			bool first = true;
			unsigned long min = 0;
			for (auto element : seeds)
			{
				unsigned long value = Convert(seedToSoil, element);
				value = Convert(soilToFertilizer, value);
				value = Convert(fertilizerToWater, value);
				value = Convert(waterToLight, value);
				value = Convert(lightToTemperature, value);
				value = Convert(temperatureToHumidity, value);
				value = Convert(humidityToLocation, value);

				if (value < min || first)
					min = value;
				first = false;
			}
			return min;
		}
		static unsigned long D5P2GetLowestLocationRanges(string filePath)
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
			string seedsString;
			getline(file, seedsString);
			seedsString.erase(0, seedsString.find(':') + 2);
			list<unsigned long> seeds = CommonFunc::SplitIntoUnsignedLongs(seedsString, " ");
			list<ConversionRange> seedToSoil;
			list<ConversionRange> soilToFertilizer;
			list<ConversionRange> fertilizerToWater;
			list<ConversionRange> waterToLight;
			list<ConversionRange> lightToTemperature;
			list<ConversionRange> temperatureToHumidity;
			list<ConversionRange> humidityToLocation;

			while (getline(file, line))
			{
				data.push_back(line);
				if (line.size() == 0)
					continue;
				if (line.find("seed-to-soil") != string::npos)
					seedToSoil = GetConversionsFromFile(file);
				if (line.find("soil-to-fertilizer") != string::npos)
					soilToFertilizer = GetConversionsFromFile(file);
				if (line.find("fertilizer-to-water") != string::npos)
					fertilizerToWater = GetConversionsFromFile(file);
				if (line.find("water-to-light") != string::npos)
					waterToLight = GetConversionsFromFile(file);
				if (line.find("light-to-temperature") != string::npos)
					lightToTemperature = GetConversionsFromFile(file);
				if (line.find("temperature-to-humidity") != string::npos)
					temperatureToHumidity = GetConversionsFromFile(file);
				if (line.find("humidity-to-location") != string::npos)
					humidityToLocation = GetConversionsFromFile(file);
			}
			bool first = true;
			unsigned long min = 0;


			bool hasStart = false;
			unsigned long start = 0;

			for (auto element : seeds)
			{
				if (!hasStart)
				{
					start = element;
					hasStart = true;
					continue;
				}
				unsigned long range = element;
				unsigned long end = start + range;

				for (unsigned long i = start; i < end; i++)
				{
					unsigned long value = Convert(seedToSoil, i);
					value = Convert(soilToFertilizer, value);
					value = Convert(fertilizerToWater, value);
					value = Convert(waterToLight, value);
					value = Convert(lightToTemperature, value);
					value = Convert(temperatureToHumidity, value);
					value = Convert(humidityToLocation, value);

					if (value < min || first)
						min = value;
					first = false;
				}
				hasStart = false;
			}
			return min;
		}
};