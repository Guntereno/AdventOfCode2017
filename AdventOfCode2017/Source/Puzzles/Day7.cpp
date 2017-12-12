#include "Puzzles\Day7.h"

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include "Common\Common.h"


using namespace std;


struct Program
{
	string Name;
	vector<string> Children;
	int Weight = 0;

	Program* pParent = nullptr;

	int TotalWeight = 0;
};

static Program* gpRoot;
static Program* gpUnbalancedNode;
static vector<Program*> gUnbalancedPrograms;

istream& operator>>(istream& stream, Program& program)
{
	stringstream currentStream;
	getline(stream, program.Name, ' ');

	if (stream.peek() == '(')
	{
		stream.ignore(1);
	}
	else
	{
		ERROR_BREAK("Invalid file format!");
	}

	stream >> program.Weight;

	if (stream.peek() == ')')
	{
		stream.ignore(1);
	}
	else
	{
		ERROR_BREAK("Invalid file format!");
	}

	bool done = ((stream.peek() == '\n') || stream.eof());
	if (!done)
	{
		const char* kSeparator = " -> ";
		const size_t kSeparatorLen = 5;
		char pBuffer[kSeparatorLen];

		stream.read(pBuffer, kSeparatorLen - 1);
		pBuffer[kSeparatorLen - 1] = '\0';

		if (strncmp(pBuffer, kSeparator, kSeparatorLen) != 0)
		{
			ERROR_BREAK("Invalid file format!");
		}

		string value;
		while (getline(stream, value, ','))
		{
			program.Children.push_back(value);

			while (stream.peek() == ' ')
			{
				stream.ignore(1);
			}
		}
	}
	return stream;
}

Day7::Day7()
{

}

Program* GetRoot(Program& program)
{
	Program* pCurrent = &program;
	while (pCurrent->pParent != nullptr)
	{
		pCurrent = pCurrent->pParent;
	}
	return pCurrent;
}

int CalculateTotalWeights(map<string, Program>& map, Program& root)
{
	root.TotalWeight = 0;

	for (string childId : root.Children)
	{
		Program& childProgram = map[childId];
		int currentWeight =
			CalculateTotalWeights(map, childProgram);

		root.TotalWeight += currentWeight;
	}

	root.TotalWeight += root.Weight;

	return root.TotalWeight;
}

map<string, Program> LoadPrograms(const char* pFileName)
{
	map<string, Program> programMap;
	ifstream inputFile;
	inputFile.open(pFileName, ifstream::in);
	string line;
	while (getline(inputFile, line))
	{
		Program program;
		stringstream lineStream(line);
		lineStream >> program;
		programMap[program.Name] = program;
	}

	// Resolve the parent pointers
	for (auto it = programMap.begin();
		it != programMap.end();
		++it)
	{
		Program& program = it->second;
		for (const string& childId : program.Children)
		{
			Program& childProgram = programMap[childId];
			childProgram.pParent = &program;
		}
	}

	// Find the root
	Program& first = programMap.begin()->second;
	gpRoot = GetRoot(first);

	// Recursively calculate the weights
	CalculateTotalWeights(programMap, *gpRoot);

	return programMap;
}

int GetDesiredWeightForFirstIncorrectProgram(map<string, Program>& map, Program* pRoot)
{
	Program* pLastProgram = nullptr;
	size_t childCount = pRoot->Children.size();

	for (int i = 0; i < childCount; ++i)
	{
		string childId = pRoot->Children[i];
		Program& currentChild = map[childId];

		int childResult = GetDesiredWeightForFirstIncorrectProgram(map, &currentChild);
		if (childResult > -1)
		{
			return childResult;
		}

		int currentWeight = currentChild.TotalWeight;
		if ((pLastProgram != nullptr) && (currentWeight != pLastProgram->TotalWeight))
		{
			assert(childCount >= 3);

			int desiredTotalWeight = -1;
			Program* pIncorrectProgram = nullptr;

			// If we're at the last element, we must be the incorrect one
			if (i == (childCount - 1))
			{
				pIncorrectProgram = &currentChild;
				desiredTotalWeight = pLastProgram->TotalWeight;
			}
			else
			{
				string nextId = pRoot->Children[i + 1];
				Program& nextProgram = map[nextId];
				int nextWeight = nextProgram.TotalWeight;

				// If the surrounding ones are the same, it must be this one
				if (nextWeight == pLastProgram->TotalWeight)
				{
					pIncorrectProgram = &currentChild;
					desiredTotalWeight = pLastProgram->TotalWeight;
				}
				else
				{
					// ... else the last one was incorrect
					assert(currentChild.TotalWeight == nextProgram.TotalWeight);
					pIncorrectProgram = &currentChild;
					desiredTotalWeight = pLastProgram->TotalWeight;
				}

				int diff = desiredTotalWeight - pIncorrectProgram->TotalWeight;
				return pIncorrectProgram->Weight + diff;
			}
		}

		pLastProgram = &currentChild;
	}

	return -1;
}


std::string Day7::Solve()
{
	map<string, Program> programs = LoadPrograms("Day7Input.txt");

	string solution1 = gpRoot->Name;

	int solution2 = GetDesiredWeightForFirstIncorrectProgram(programs, gpRoot);

	stringstream solutionStream;
	solutionStream << "1: " << solution1;
	solutionStream << endl;
	solutionStream << "2: " << solution2;

	return solutionStream.str();
}


