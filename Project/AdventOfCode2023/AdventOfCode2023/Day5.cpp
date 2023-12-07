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

		static list<ConversionRange> GetConversionsFromFileAndCondense(std::ifstream& file, list<ConversionRange> inputConversions)
		{
			string line;
			list<ConversionRange> nextConversions;
			while (getline(file, line))
			{
				if (line.size() == 0)
					return inputConversions;
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
				nextConversions.push_back(conversion);
			}
			return Condense(inputConversions, nextConversions);
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

		static unsigned long ConvertValueIfLower(unsigned long current, unsigned long input, list<ConversionRange> range, bool first = false)
		{
			unsigned long value = Convert(range, input);

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



		static list< ConversionRange> Condense(list< ConversionRange> currentRanges, list< ConversionRange > nextRanges)
		{
			//once a range has been "converted" we then add it to a "converted range" this is now not checked against
			//any left overs are added back to their respective lists
			//once no overlaps occur then all lists are merged and returned,

			list<ConversionRange> convertedRanges;
			bool overlaped = true;
			while (overlaped)
			{
				overlaped = false;
				bool breakOut = false;

				list<ConversionRange> currentsToRemove;
				list < ConversionRange> nextsToRemove;

				list < ConversionRange> currentsToAdd;
				list < ConversionRange> nextsToAdd;

				for (auto nextRange : nextRanges)
				{
					for (auto currentRange : currentRanges)
					{
						unsigned long currentDestEnd = currentRange.destination + (currentRange.length - 1);
						unsigned long nextSourceEnd = nextRange.source + (nextRange.length - 1);


						if (currentDestEnd < nextRange.source ||
							currentRange.destination > nextSourceEnd)
						{
							//no overlap
							continue;
						}
						overlaped = true;
						currentsToRemove.push_back(currentRange);
						nextsToRemove.push_back(nextRange);
						if (currentRange.destination <= nextRange.source)
						{
							//element overlaps or contains range
							unsigned long startDif = nextRange.source - currentRange.destination;

							if (startDif > 0) //chopping off the bit of element before the overlap
								currentsToAdd.push_back(CreateConversion(currentRange.source, currentRange.destination, startDif));

							convertedRanges.push_back(CreateConversion(currentRange.source + startDif, nextRange.destination, min(nextRange.length, currentRange.length - startDif)));

							if (currentDestEnd >= nextSourceEnd)
							{
								//element contains range
								unsigned long endDif = currentDestEnd - nextSourceEnd;
								if (endDif > 0)
									currentsToAdd.push_back(CreateConversion(currentRange.source + startDif + nextRange.length, currentRange.destination + startDif + nextRange.length, endDif));
							}
							else
							{
								nextsToAdd.push_back(CreateConversion(nextRange.source + currentRange.length - startDif, nextRange.destination + currentRange.length - startDif, nextSourceEnd - currentDestEnd));
								//element doesn't contain range
							}
						}
						else
						{
							unsigned long startDif = currentRange.destination - nextRange.source;

							nextsToAdd.push_back(CreateConversion(nextRange.source, nextRange.destination, startDif));

							convertedRanges.push_back(CreateConversion(currentRange.source, nextRange.destination + startDif, min(nextRange.length - startDif, currentRange.length)));
							if (nextSourceEnd >= currentDestEnd)
							{
								//range contains element
								unsigned long endDif = nextSourceEnd - currentDestEnd;
								if (endDif > 0)
									nextsToAdd.push_back(CreateConversion(nextRange.source + startDif + currentRange.length, nextRange.destination + startDif + currentRange.length, endDif));
							}
							else
							{
								currentsToAdd.push_back(CreateConversion(currentRange.source + nextRange.length - startDif, currentRange.destination + nextRange.length - startDif, currentDestEnd - nextSourceEnd));
							}
						}
						breakOut = true;
						break;
					}
					if (breakOut)
						break;
				}
				do these
				//for removes, remove
				//for adds add
			}
			//Combine remaining currnent and next into converted, and return
			return convertedRanges;
		}

		static unsigned long GetLowestNotInARange(unsigned long defaultValue, unsigned long start, unsigned long end, list< ConversionRange> ranges)
		{
			bool collidedWithRange = false;
			for (auto element : ranges)
			{
				if (start >= element.source && start < element.source + element.length)
				{
					collidedWithRange = true;
					start = element.source + element.length;
					break;
				}
			}
			if (start >= end)
				return defaultValue;
			if (collidedWithRange)
				return GetLowestNotInARange(defaultValue, start, end, ranges);
			return start;
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
			list<ConversionRange> seedToLocation;
			while (getline(file, line))
			{
				data.push_back(line);
				if (line.size() == 0)
					continue;
				if (line.find("-to-") != string::npos)
					seedToLocation = GetConversionsFromFileAndCondense(file, seedToLocation);
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


				//min = ConvertValueIfLower(min, start, first);
				for (auto range : seedToLocation)
				{
					if (range.source + range.length < start ||
						range.source > end)
						continue;
					if (range.source <= start)
						min = ConvertValueIfLower(min, start, seedToLocation, first);
					else
						min = ConvertValueIfLower(min, range.source, seedToLocation, first);

					first = false;
				}
				min = GetLowestNotInARange(min, start, end, seedToLocation);
				hasStart = false;
			}
			return min;
		}
};