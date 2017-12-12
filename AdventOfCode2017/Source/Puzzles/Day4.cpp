#include "Puzzles\Day4.h"

#include <algorithm>
#include <vector>

#include "Common\Parsing.h"
#include "Common\CsvParser.h"

using namespace std;

Day4::Day4()
{

}

bool IsInvalid(const vector<string>& phrase)
{
	for (int a = 0; a < phrase.size(); ++a)
	{
		for (int b = a+1; b < phrase.size(); ++b)
		{
			if (phrase[a] == phrase[b])
			{
				return true;
			}
		}
	}

	return false;
}

int CountValid(const vector<vector<string>>& input)
{
	int count = 0;
	for (vector<string> phrase : input)
	{
		if (!IsInvalid(phrase))
		{
			++count;
		}
	}
	return count;
}

void SortStringCharacters(vector<vector<string>>& input)
{
	for (int phraseIndex = 0; phraseIndex < input.size(); ++phraseIndex)
	{
		vector<string>& phrase = input[phraseIndex];

		for (int wordIndex = 0; wordIndex < phrase.size(); ++wordIndex)
		{
			sort(phrase[wordIndex].begin(), phrase[wordIndex].end());
		}
	}
}

std::string Day4::Solve()
{
	Common::ParseString parseString;
	Common::CsvParser<string, Common::ParseString> csvParser(
		"Day4Input.txt",
		parseString,
		' ',
		'\n'
	);
	vector<vector<string>> input = csvParser.Parse();
	
	int solution1 = CountValid(input);

	// Sort the characters in the input
	SortStringCharacters(input);

	int solution2 = CountValid(input);

	stringstream solutionStream;
	solutionStream << "1: " << solution1;
	solutionStream << endl;
	solutionStream << "2: " << solution2;

	return solutionStream.str();
}


