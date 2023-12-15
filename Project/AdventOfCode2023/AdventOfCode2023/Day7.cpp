#include<CommonFunctions.h>
#include <iostream>
#include <fstream>

const static string ValueOrderP1 = "AKQJT98765432";
const static string ValueOrderP2 = "AKQT98765432J";
static class Day7
{
private:
	static void SortHandIntoVector(const static string valueOrder, vector<string>* vector, string newHandAndBid)
	{
		string newHand = newHandAndBid.substr(0,5);
		for (int i = 0; i < vector->size(); i++)
		{
			string currentHand = vector->at(i).substr(0, 5);
			for (int j = 0; j < newHand.size(); j++)
			{
				int valueNew = GetValueOfCard(valueOrder, newHand[j]);
				int valueCurrent = GetValueOfCard(valueOrder, currentHand[j]);

				if (valueNew > valueCurrent)
				{
					vector->insert(vector->begin() + i, newHandAndBid);
					return;
				}
				if (valueNew < valueCurrent)
					break;
			}
		}
		vector->push_back(newHandAndBid);
	}

	static int GetValueOfCard(const static string valueOrder, char value)
	{
		for (int i = 0; i < valueOrder.size(); i++)
		{
			if (value == valueOrder[i])
			{
				return (valueOrder.size() - i);
			}
		}
		return -1;
	}

	static int GetWinningsOfVector(int rank, vector<string>* vector)
	{
		int total = 0;
		for (int i = vector->size() - 1; i >= 0; i--)
		{
			total += (rank * stoi(vector->at(i).substr(6, 100)));
			rank++;
		}
		return total;
	}
public:
	static int D7P1GetTotalWinnings(string filePath)
	{
		std::ifstream file;
		file.open(filePath, ios::in);

		if (!file.is_open())
		{
			cout << "Error! File Does not Exist";
			cout << "\n";
			return 0;
		}

		vector<string>* FiveOfAKinds = new vector<string>();
		vector<string>* FourOfAKinds = new vector<string>();
		vector<string>* FullHouses = new vector<string>();
		vector<string>* ThreeOfAKinds = new vector<string>();
		vector<string>* TwoPairs = new vector<string>();
		vector<string>* OnePairs = new vector<string>();
		vector<string>* HighCards = new vector<string>();
		string line;
		while (getline(file, line))
		{
			list<string> hand = CommonFunc::Split(line, " ");
			bool done = false;
			vector<int> counts;
			for (int i = 0; i < ValueOrderP1.size(); i++)
			{
				int count = std::count(hand.front().begin(), hand.front().end(), ValueOrderP1[i]);
				if(count > 1)
					counts.push_back(count);
			}
			if(counts.size() == 0)
				SortHandIntoVector(ValueOrderP1, HighCards, line);
			else if (counts.size() == 1)
			{
				if(counts[0] == 5)
					SortHandIntoVector(ValueOrderP1, FiveOfAKinds, line);
				else if (counts[0] == 4)
					SortHandIntoVector(ValueOrderP1, FourOfAKinds, line);
				else if (counts[0] == 3)
					SortHandIntoVector(ValueOrderP1, ThreeOfAKinds, line);
				else if (counts[0] == 2)
					SortHandIntoVector(ValueOrderP1, OnePairs, line);
			}
			else// if (counts.size() == 2)
			{
				if (counts[0] == 3 || counts[1] == 3)
					SortHandIntoVector(ValueOrderP1, FullHouses, line);
				else
					SortHandIntoVector(ValueOrderP1, TwoPairs, line);
			}
		}
		int winnings = 0;
		int rank = 1;

		winnings += GetWinningsOfVector(rank, HighCards);
		rank += HighCards->size();
		winnings += GetWinningsOfVector(rank, OnePairs);
		rank += OnePairs->size();
		winnings += GetWinningsOfVector(rank, TwoPairs);
		rank += TwoPairs->size();
		winnings += GetWinningsOfVector(rank, ThreeOfAKinds);
		rank += ThreeOfAKinds->size();
		winnings += GetWinningsOfVector(rank, FullHouses);
		rank += FullHouses->size();
		winnings += GetWinningsOfVector(rank, FourOfAKinds);
		rank += FourOfAKinds->size();
		winnings += GetWinningsOfVector(rank, FiveOfAKinds);


		delete FiveOfAKinds;
		delete FourOfAKinds;
		delete FullHouses;
		delete ThreeOfAKinds;
		delete TwoPairs;
		delete OnePairs;
		delete HighCards;

		return winnings;
	}

	static int D7P2GetTotalWinnings(string filePath)
	{
		std::ifstream file;
		file.open(filePath, ios::in);

		if (!file.is_open())
		{
			cout << "Error! File Does not Exist";
			cout << "\n";
			return 0;
		}

		vector<string>* FiveOfAKinds = new vector<string>();
		vector<string>* FourOfAKinds = new vector<string>();
		vector<string>* FullHouses = new vector<string>();
		vector<string>* ThreeOfAKinds = new vector<string>();
		vector<string>* TwoPairs = new vector<string>();
		vector<string>* OnePairs = new vector<string>();
		vector<string>* HighCards = new vector<string>();
		string line;
		while (getline(file, line))
		{
			list<string> hand = CommonFunc::Split(line, " ");
			bool done = false;
			vector<int> counts;
			for (int i = 0; i < ValueOrderP2.size() -1; i++)
			{
				int count = std::count(hand.front().begin(), hand.front().end(), ValueOrderP2[i]);
				if (count > 1)
					counts.push_back(count);
			}
			int jCount = std::count(hand.front().begin(), hand.front().end(), 'J');

			int count1 = jCount;
			if (counts.size() > 0)
				count1 += counts[0];
			else if(jCount < 5 && jCount > 0)
				count1 += 1;

			int count2 = jCount;
			if (counts.size() > 1)
				count2 += counts[1];

			if (count1 == 0)
			{
				SortHandIntoVector(ValueOrderP2, HighCards, line);
			}
			else if (counts.size() < 2)
			{
				if (count1 == 5)
					SortHandIntoVector(ValueOrderP2, FiveOfAKinds, line);
				else if (count1 == 4)
					SortHandIntoVector(ValueOrderP2, FourOfAKinds, line);
				else if (count1 == 3)
					SortHandIntoVector(ValueOrderP2, ThreeOfAKinds, line);
				else //if (count1 == 2)
					SortHandIntoVector(ValueOrderP2, OnePairs, line);
			}
			else// if (counts.size() == 2)
			{
				if (count1 == 3 || count2 == 3)
					SortHandIntoVector(ValueOrderP2, FullHouses, line);
				else
					SortHandIntoVector(ValueOrderP2, TwoPairs, line);
			}
		}
		int winnings = 0;
		int rank = 1;

		winnings += GetWinningsOfVector(rank, HighCards);
		rank += HighCards->size();
		winnings += GetWinningsOfVector(rank, OnePairs);
		rank += OnePairs->size();
		winnings += GetWinningsOfVector(rank, TwoPairs);
		rank += TwoPairs->size();
		winnings += GetWinningsOfVector(rank, ThreeOfAKinds);
		rank += ThreeOfAKinds->size();
		winnings += GetWinningsOfVector(rank, FullHouses);
		rank += FullHouses->size();
		winnings += GetWinningsOfVector(rank, FourOfAKinds);
		rank += FourOfAKinds->size();
		winnings += GetWinningsOfVector(rank, FiveOfAKinds);


		delete FiveOfAKinds;
		delete FourOfAKinds;
		delete FullHouses;
		delete ThreeOfAKinds;
		delete TwoPairs;
		delete OnePairs;
		delete HighCards;

		return winnings;
	}
};