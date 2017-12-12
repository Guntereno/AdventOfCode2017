#include "Puzzles\Day2.h"

#include <limits>
#include <sstream>

#include "Common\Common.h"
#include "Common\CsvParser.h"
#include "Common\Parsing.h"

using namespace std;


long CalculateChecksum(const vector <vector<int>>& sheet);
int CalculateSumOfDivisiblePairs(const vector <vector<int>>& sheet);
void CheckFoundDivisible(bool& foundDivisiblePair, size_t rowNum);

Day2::Day2()
{

}

std::string Day2::Solve()
{
	stringstream solutionStream;

	const char* kInputFileName = "Day2Input.tsv";
	Common::ParseInt parseInt;
	Common::CsvParser<int, Common::ParseInt> tsv(kInputFileName, parseInt, '\t', '\n');
	vector <vector<int>> sheet = tsv.Parse();

	long checksum = CalculateChecksum(sheet);
	long divisionSum = CalculateSumOfDivisiblePairs(sheet);

	solutionStream << "1: " << checksum;
	solutionStream << endl;
	solutionStream << "2: " << divisionSum;

	return solutionStream.str();
}

long CalculateChecksum(const vector <vector<int>>& sheet)
{
	long checksum = 0;
	size_t rowCount = sheet.size();
	for (size_t rowIndex = 0; rowIndex < rowCount; ++rowIndex)
	{
		vector<int> row = sheet[rowIndex];
		int min = numeric_limits<int>::max();
		int max = numeric_limits<int>::min();

		size_t cellCount = row.size();
		for (size_t cellIndex = 0; cellIndex < cellCount; ++cellIndex)
		{
			int cell = row[cellIndex];
			if (cell < min)
			{
				min = cell;
			}
			if (cell > max)
			{
				max = cell;
			}
		}

		int diff = max - min;
		checksum += diff;
	}

	return checksum;
}

int CalculateSumOfDivisiblePairs(const vector <vector<int>>& sheet)
{
	long sum = 0;
	size_t rowCount = sheet.size();
	for (size_t rowIndex = 0; rowIndex < rowCount; ++rowIndex)
	{
		vector<int> row = sheet[rowIndex];

		bool foundDivisiblePair = false;

		size_t cellCount = row.size();
		for (size_t cellIndex = 0; cellIndex < cellCount; ++cellIndex)
		{
			int cell = row[cellIndex];

			if (cell == 0)
			{
				ERROR_BREAK("Table cell [%d, %d] is zero!", cellIndex, rowIndex);
			}

			for (size_t otherCellIndex = cellIndex + 1; otherCellIndex < cellCount; ++otherCellIndex)
			{
				int otherCell = row[otherCellIndex];

				if (cell == 0)
				{
					ERROR_BREAK("Table cell [%d, %d] is zero!", cellIndex, rowIndex);
				}

				if ((cell % otherCell) == 0)
				{
					CheckFoundDivisible(foundDivisiblePair, rowIndex);
					sum += cell / otherCell;
				}
				else if((otherCell % cell) == 0)
				{
					CheckFoundDivisible(foundDivisiblePair, rowIndex);
					sum += otherCell / cell;
				}
			}
		}

		if (!foundDivisiblePair)
		{
			ERROR_BREAK("No divisible pairs found on row %d!", rowIndex);
		}
	}

	return sum;
}

void CheckFoundDivisible(bool& foundDivisiblePair, size_t rowNum)
{
	if (foundDivisiblePair)
	{
		ERROR_BREAK("Found multiple divisible pairs on row %d!", rowNum);
	}
	else
	{
		foundDivisiblePair = true;
	}
}