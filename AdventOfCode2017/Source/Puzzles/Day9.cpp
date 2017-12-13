#include "Puzzles\Day9.h"

#include <fstream>
#include <sstream>

using namespace std;

int CalculateTotalScore(istream& input, int& countedGarbage)
{
	int totalScore = 0;

	stringstream processed;

	char c;
	bool inGarbage = false;
	int currentGroupScore = 0;
	countedGarbage = 0;
	while (input.get(c))
	{
		if (c == '!')
		{
			processed << input.peek();
			input.ignore(1);
		}
		else if (inGarbage)
		{
			if (c == '>')
			{
				inGarbage = false;
			}
			else
			{
				++countedGarbage;
			}
		}
		else
		{
			switch (c)
			{
			case '<':
				inGarbage = true;
				break;

			case '{':
				++currentGroupScore;
				break;

			case '}':
				totalScore += currentGroupScore;
				if (--currentGroupScore < 0)
				{
					currentGroupScore = 0;
				}
				break;

			default:
				// Do nothing
				break;
			}
		}
		processed << c;
	}

	return totalScore;
}


Day9::Day9()
{

}


std::string Day9::Solve()
{
	ifstream inputFile;
	inputFile.open("Day9Input.txt", ifstream::in);

	int countedGarbage;
	int solution1 = CalculateTotalScore(inputFile, countedGarbage);
	int solution2 = countedGarbage;

	stringstream solutionStream;
	solutionStream << "1: " << solution1;
	solutionStream << endl;
	solutionStream << "2: " << solution2;

	return solutionStream.str();
}


