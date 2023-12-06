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
		static list<ConversionRange> seedToSoil;
		static list<ConversionRange> soilToFertilizer;
		static list<ConversionRange> fertilizerToWater;
		static list<ConversionRange> waterToLight;
		static list<ConversionRange> lightToTemperature;
		static list<ConversionRange> temperatureToHumidity;
		static list<ConversionRange> humidityToLocation;


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
		static int ConvertValueIfLower(int current, int input, bool first = false)
		{
			unsigned long value = Convert(seedToSoil, input);
			value = Convert(soilToFertilizer, value);
			value = Convert(fertilizerToWater, value);
			value = Convert(waterToLight, value);
			value = Convert(lightToTemperature, value);
			value = Convert(temperatureToHumidity, value);
			value = Convert(humidityToLocation, value);

			if (value < current || first)
				return value;
			return current;
		}

		static ConversionRange CreateConversion(unsigned long sourceIn, unsigned long destinationIn, unsigned long lengthIn)
		{
			ConversionRange newRange;
			newRange.source = sourceIn;
			newRange.destination = destinationIn;
			newRange.length = lengthIn;
			return newRange;
		}

		static list< ConversionRange> Condense(list< ConversionRange> ranges, ConversionRange range)
		{
			list<ConversionRange> newList;
			ConversionRange newRange = CreateConversion(range.source, range.destination, range.length);
			for (auto element : ranges)
			{
				range = newRange;
				unsigned long elementDestEnd = element.destination + (element.length - 1);
				unsigned long rangeSourceEnd = range.source + (range.length - 1);


				if (elementDestEnd < range.source ||
					element.destination > rangeSourceEnd)
				{
					//no overlap
					newList.push_back(element);
					continue;
				}

				if (element.destination <= range.source)
				{
					//element overlaps or contains destination
					unsigned long startDif = range.source - element.destination;

					if (startDif > 0) //chopping off the bit of element before the overlap
						newList.push_back(CreateConversion(element.source, element.destination, startDif));

					newList.push_back(CreateConversion(element.source + startDif, range.destination, min(range.length, element.length - startDif)));

					if (elementDestEnd >= rangeSourceEnd)
					{
						//element contains range
						unsigned long endDif = elementDestEnd - rangeSourceEnd;
						if(endDif > 0)
							newList.push_back(CreateConversion(element.source + startDif + range.length, element.destination + startDif + range.length, endDif));
						newRange.length = 0;
						break;
					}
					newRange = CreateConversion(range.source + element.length - startDif, range.destination + element.length - startDif, rangeSourceEnd - elementDestEnd);
					//element doesn't contain range
					continue;
				}
				//element overlaps or contains destination
				{
					unsigned long startDif = element.destination - range.source;

					//this could involve the need for "range" to be split into multiple different lists
					//	if there are multiple it could be added to a "holdover" list and dealt with after the current Condense is finished

					if (startDif > 0) //chopping off the bit of element before the overlap
						newList.push_back(CreateConversion(element.source, element.destination, startDif));
				}
				

			}
			if(newRange.length > 0)
				newList.push_back(newRange);
			return newList;
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
				min = ConvertValueIfLower(min, element, first);
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

				//condense ranges into 1 big converter
				//once this exists test 
				// check if the lowest value outside of ranges (if one exists) is lowest
				// check if the lowest value inside of ranges is lowest

				min = ConvertValueIfLower(min, start, first);


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