#include "Puzzles\Day5.h"

#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

namespace Day5Utils
{
	struct Cpu
	{
		void Run(vector<int> program)
		{
			Pc = 0;
			Cycles = 0;
			Program = program;

			bool shouldContinue = false;
			do
			{
				shouldContinue = Execute();
			} while (shouldContinue);
		}

		bool Execute()
		{
			int jumps = Program[Pc];

			if (StrangeJumps && (jumps >= 3))
			{
				Program[Pc] -= 1;
			}
			else
			{
				Program[Pc] += 1;
			}

			Pc += jumps;
			++Cycles;
			return ((Pc >= 0) && (Pc < Program.size()));
		}

		int Pc = 0;
		int Cycles = 0;
		bool StrangeJumps = false;
		vector<int> Program;
	};
}

Day5::Day5()
{

}


vector<int> LoadProgram(string fileName)
{
	vector<int> program;

	ifstream inputFile;
	inputFile.open(fileName, ifstream::in);
	if (inputFile.is_open())
	{
		string line;
		while (getline(inputFile, line))
		{
			int value = stoi(line);
			program.push_back(value);
		}
	}

	return program;
}

std::string Day5::Solve()
{
	vector<int> program = LoadProgram("Day5Input.txt");
	Day5Utils::Cpu cpu;
	cpu.Run(program);
	int solution1 = cpu.Cycles;

	cpu.StrangeJumps = true;
	cpu.Run(program);
	int solution2 = cpu.Cycles;

	stringstream solutionStream;
	solutionStream << "1: " << solution1;
	solutionStream << endl;
	solutionStream << "2: " << solution2;

	return solutionStream.str();
}


