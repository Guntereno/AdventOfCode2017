#include "Puzzles\Day6.h"

#include <algorithm>
#include <sstream>
#include <set>
#include <vector>

#include "Common\Parsing.h"
#include "Common\CsvParser.h"

using namespace std;

Day6::Day6()
{

}

vector<int> LoadBanks(const char* fileName)
{
	Common::ParseInt parseInt;
	Common::CsvParser<int, Common::ParseInt> tsv(fileName, parseInt, '\t', '\n');
	vector <vector<int>> sheet = tsv.Parse();

	return sheet[0];
}

void Reallocate(vector<int>& banks)
{
	auto currentBank = max_element(begin(banks), end(banks));
	int toRedistribute = *currentBank;
	*currentBank = 0;

	do {
		++currentBank;
		if (currentBank == end(banks))
		{
			currentBank = begin(banks);
		}

		*currentBank += 1;
		toRedistribute -= 1;
	} while (toRedistribute > 0);
}

std::string Day6::Solve()
{
	vector<int> banks = LoadBanks("Day6Input.txt");

	int solution1 = 0;
	int solution2 = 0;

	set<vector<int>> history;
	bool shouldContinue = false;
	const vector<int>* pFoundConfig = nullptr;
	int cycles = 0;
	do {
		++cycles;
		history.insert(banks);
		Reallocate(banks);

		shouldContinue = true;

		auto inSet = history.find(banks);
		if (inSet != end(history))
		{
			const vector<int>* pFoundSetValue = &(*inSet);
			if (pFoundConfig == nullptr)
			{
				pFoundConfig = pFoundSetValue;
				solution1 = cycles;
				cycles = 0;
			}
			else if (pFoundConfig == pFoundSetValue)
			{
				solution2 = cycles;
				shouldContinue = false;
			}
		}
	} while (shouldContinue);



	stringstream solutionStream;
	solutionStream << "1: " << solution1;
	solutionStream << endl;
	solutionStream << "2: " << solution2;

	return solutionStream.str();
}


