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

		static ConversionRange GetRangeFromString(string input)
		{
			list<unsigned long> conversionString = CommonFunc::SplitIntoUnsignedLongs(input, " ");
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
			return conversion;
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

				list < ConversionRange> temp;
				for (auto currentRange : currentRanges)
				{
					bool found = false;
					for (auto toRemove : currentsToRemove)
					{
						if (currentRange.destination == toRemove.destination && currentRange.length == toRemove.length && currentRange.source == toRemove.source)
						{
							found = true;
							break;
						}
					}
					if (!found)
						temp.push_back(currentRange);
				}
				currentRanges = temp;

				temp.clear();
				for (auto nextRange : nextRanges)
				{
					bool found = false;
					for (auto toRemove : nextsToRemove)
					{
						if (nextRange.destination == toRemove.destination && nextRange.length == toRemove.length && nextRange.source == toRemove.source)
						{
							found = true;
							break;
						}
					}
					if (!found)
						temp.push_back(nextRange);
				}
				nextRanges = temp;


				for (auto toAdd : currentsToAdd)
					currentRanges.push_back(toAdd);
				for (auto toAdd : nextsToAdd)
					nextRanges.push_back(toAdd);
			}

			for (auto toAdd : nextRanges)
				convertedRanges.push_back(toAdd);
			for (auto toAdd : currentRanges)
				convertedRanges.push_back(toAdd);
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
			list<ConversionRange> seedToLocation;
			list<ConversionRange> next;
			while (getline(file, line))
			{
				data.push_back(line);
				if (line.size() == 0)
				{
					seedToLocation = Condense(seedToLocation, next);
					next.clear();
					continue;
				}
				if (line.find("-to-") == string::npos)
					next.push_back(GetRangeFromString(line));
			}
			seedToLocation = Condense(seedToLocation, next);
			bool first = true;
			unsigned long min = 0;
			for (auto element : seeds)
			{
				unsigned long value = Convert(seedToLocation, element);

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
			list<ConversionRange> next;
			while (getline(file, line))
			{
				data.push_back(line);
				if (line.size() == 0)
				{
					seedToLocation = Condense(seedToLocation, next);
					next.clear();
					continue;
				}
				if (line.find("-to-") == string::npos)
					next.push_back(GetRangeFromString(line));
			}
			seedToLocation = Condense(seedToLocation, next);
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