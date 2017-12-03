#include "Puzzles\Day3.h"

#include <iostream>
#include <sstream>

#include "Common\Common.h"
#include "Common\Point.h"


using namespace std;

const size_t kInput = 347991;


struct Entry
{
	size_t Value = 0;
	int TestValue = 0;
	Point Position;
};


bool NextInSpiral(const Point & current, int ring, Point & outNext)
{
	outNext = current;
	if (current.X == ring)
	{
		// On right side
		if (current.Y == -ring)
		{
			// Finished ring
			return false;
		}
		else if (current.Y == ring)
		{
			// On top, turn left
			--outNext.X;
		}
		else
		{
			// On edge, continue up
			++outNext.Y;
		}
	}
	else if (current.X == -ring)
	{
		// On left side
		if (current.Y == -ring)
		{
			// At bottom, turn left
			++outNext.X;
		}
		else if (current.Y == ring)
		{
			// At top, turn left
			--outNext.Y;
		}
		else
		{
			// On edge continue down
			--outNext.Y;
		}
	}
	else
	{
		if (current.Y == ring)
		{
			// On top row, continue left
			--outNext.X;
		}
		else if (current.Y == -ring)
		{
			// On bottom row, continue right
			++outNext.X;
		}
		else
		{
			ERROR_BREAK("At invalid cell!")
				return true;
		}
	}

	return true;
}

int WidthOfRing(int ring)
{
	return (ring * 2) + 1;
}

int CapacityAtfRing(int ring)
{
	int width = WidthOfRing(ring);
	return width * width;
}

int GetRingNeededToContain(size_t size)
{
	int ring = 0;
	while (CapacityAtfRing(ring) < size)
	{
		++ring;
	}
	return ring;
}

int GetMapIndexForCoord(const Point& coord, int numRings)
{
	int x = coord.X + (numRings - 1);
	int y = coord.Y + (numRings - 1);
	int index = x + (y * ((numRings * 2) - 1));
	return index;
}

bool PointIsInRange(const Point& coord, int numRings)
{
	return
		coord.X > -numRings
		&&	coord.Y > -numRings
		&&	coord.X < numRings
		&&	coord.Y < numRings;
}

class SpriralMemory
{
public:
	SpriralMemory(size_t size)
	{
		_pMemory = new Entry[size];

		int lastRing = GetRingNeededToContain(size);
		int numRings = lastRing + 1;
		int ringWidth = WidthOfRing(lastRing);

		size_t mapSize = ringWidth * ringWidth;
		_pMap = new Entry*[mapSize];
		memset(_pMap, NULL, sizeof(Entry*) * mapSize);

		int currentRing = 0;
		Point currentPos = { 0, 0 };

		for (size_t current = 0; current < size; ++current)
		{
			_pMemory[current] =
			{
				current,
				0,
				currentPos
			};

			Entry& currentEntry = _pMemory[current];

			size_t mapIndex = GetMapIndexForCoord(currentPos, numRings);
			_pMap[mapIndex] = &(_pMemory[current]);

			if(current == 0)
			{
				currentEntry.TestValue = 1;
			}
			else
			{
				// Sum the neighbouring test values
				int testSum = 0;
				Point offset{ 1, 0 };
				bool shouldContinue;
				do
				{
					Point neighbourCoord = currentPos + offset;
					if (PointIsInRange(neighbourCoord, numRings))
					{
						int neighbourIndex = GetMapIndexForCoord(neighbourCoord, numRings);

						Entry* pNeighbour = _pMap[neighbourIndex];
						if (pNeighbour != NULL)
						{
							testSum += pNeighbour->TestValue;
						}
					}

					Point nextOffset;
					shouldContinue = NextInSpiral(offset, 1, nextOffset);
					offset = nextOffset;
				} while (shouldContinue);

				currentEntry.TestValue = testSum;
			}

			if ((_testValue < 0) && (currentEntry.TestValue > kInput))
			{
				_testValue = currentEntry.TestValue;
			}

			// Move te the next point in the spiral
			Point nextPos;
			bool ringComplete = !NextInSpiral(currentPos, currentRing, nextPos);
			if (ringComplete)
			{
				++currentRing;
				++currentPos.X;
			}
			else
			{
				currentPos = nextPos;
			}
		}
	}

	SpriralMemory()
	{
		delete _pMemory;
	}

	Entry* _pMemory;
	Entry** _pMap;
	int _testValue = -1;
};

Day3::Day3()
{

}

std::string Day3::Solve()
{
	stringstream solutionStream;
	int solution1 = 0;

	SpriralMemory spiralMemory(kInput);
	const Entry& last = spiralMemory._pMemory[kInput - 1];
	int manhattan = last.Position.GetManhattanMagnitude();

	solutionStream << "1: " << manhattan;
	solutionStream << endl;
	solutionStream << "2: " << spiralMemory._testValue;

	return solutionStream.str();
}
