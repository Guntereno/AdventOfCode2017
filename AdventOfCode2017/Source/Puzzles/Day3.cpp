#include "Puzzles\Day3.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "Common\Common.h"

using namespace std;

const size_t kInput = 347991;

Day3::Day3()
{

}

struct Entry
{
	size_t Value;
	int X;
	int Y;
};

class SpriralMemory
{
public:
	SpriralMemory(size_t size)
	{
		int currentRing = 0;
		int currentX = 0;
		int currentY = 0;

		_pMemory = new Entry[size];

		for (size_t current = 0; current < size; ++current)
		{
			_pMemory[current] =
			{
				current,
				currentX,
				currentY
			};

			//_lookup.emplace(pair<int,int>(currentX, currentY), _pMemory[current]);

			if (currentX == currentRing)
			{
				// On right side
				if (currentY == -currentRing)
				{
					// Finished ring, go to next
					++currentRing;
					++currentX;
				}
				else if (currentY == currentRing)
				{
					// On top, turn left
					--currentX;
				}
				else
				{
					// On edge, continue up
					++currentY;
				}
			}
			else if (currentX == -currentRing)
			{
				// On left side
				if (currentY == -currentRing)
				{
					// At bottom, turn left
					++currentX;
				}
				else if (currentY == currentRing)
				{
					// At top, turn left
					--currentY;
				}
				else
				{
					// On edge continue down
					--currentY;
				}
			}
			else
			{
				if (currentY == currentRing)
				{
					// On top row, continue left
					--currentX;
				}
				else if (currentY == -currentRing)
				{
					// On bottom row, continue right
					++currentX;
				}
				else
				{
					ERROR_BREAK("At invalid cell!")
				}
			}
		}
	}

	SpriralMemory()
	{
		delete _pMemory;
	}

	Entry* _pMemory;
	//map<pair<int, int>, const Entry&> _lookup;
};

int GetManhattan(int x, int y)
{
	return abs(x) + abs(y);
}

std::string Day3::Solve()
{
	stringstream solutionStream;
	int solution1 = 0;

	SpriralMemory spiralMemory(kInput);
	const Entry& last = spiralMemory._pMemory[kInput - 1];
	int manhattan = GetManhattan(last.X, last.Y);

	solutionStream << "1: " << manhattan;
	solutionStream << endl;

	return solutionStream.str();
}
