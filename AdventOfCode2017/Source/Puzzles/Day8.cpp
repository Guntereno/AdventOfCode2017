#include "Puzzles\Day8.h"

#include <algorithm>
#include <climits>
#include <fstream>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>

#include "Common\Common.h"

using namespace std;

enum Comparator
{
	GreaterThan,
	GreaterOrEqual,
	LessThan,
	LessOrEqual,
	Equal,
	NotEqual
};

struct Condition
{
	string Register;

	Comparator Comparator;

	int Value;
};

istream& operator>>(istream& stream, Condition& condition)
{
	const char* kSeparator = " if ";
	const size_t kSeparatorLen = 5;
	char pBuffer[kSeparatorLen];

	stream.read(pBuffer, kSeparatorLen - 1);
	pBuffer[kSeparatorLen - 1] = '\0';

	if (strncmp(pBuffer, kSeparator, kSeparatorLen) != 0)
	{
		ERROR_BREAK("Invalid file format!");
	}

	getline(stream, condition.Register, ' ');

	string comparison;
	getline(stream, comparison, ' ');

	if (comparison == ">")
	{
		condition.Comparator = Comparator::GreaterThan;
	}
	else if (comparison == ">=")
	{
		condition.Comparator = Comparator::GreaterOrEqual;
	}
	else if (comparison == "<")
	{
		condition.Comparator = Comparator::LessThan;
	}
	else if (comparison == "<=")
	{
		condition.Comparator = Comparator::LessOrEqual;
	}
	else if (comparison == "==")
	{
		condition.Comparator = Comparator::Equal;
	}
	else if (comparison == "!=")
	{
		condition.Comparator = Comparator::NotEqual;
	}
	else
	{
		ERROR_BREAK("Unhandled comparison: ", comparison);
	}

	stream >> condition.Value;

	return stream;
}

enum Operator
{
	Inc,
	Dec
};

struct Instruction
{
	string Register;

	Operator Operator;

	int Value;

	Condition Condition;
};

istream& operator>>(istream& stream, Instruction& instruction)
{
	getline(stream, instruction.Register, ' ');

	string operatorString;
	getline(stream, operatorString, ' ');

	if (operatorString == "inc")
	{
		instruction.Operator = Operator::Inc;
	}
	else if (operatorString == "dec")
	{
		instruction.Operator = Operator::Dec;
	}
	else
	{
		ERROR_BREAK("Unhandled operator: ", operatorString);
	}

	stream >> instruction.Value;

	stream >> instruction.Condition;

	return stream;
}

vector<Instruction> LoadProgram(const char* pFileName)
{
	vector<Instruction> program;

	ifstream inputFile;
	inputFile.open(pFileName, ifstream::in);
	string line;
	while (getline(inputFile, line))
	{
		stringstream lineStream(line);
		Instruction instruction;
		lineStream >> instruction;
		program.push_back(instruction);
	}

	return program;
}


namespace Day8Utils
{
	class Cpu
	{
		map<string, int> _registers;
		int _highestValue = INT_MIN;

		bool Evaluate(Condition condition)
		{
			int reg = GetRegister(condition.Register);
			int val = condition.Value;

			switch (condition.Comparator)
			{
			case GreaterThan:
				return reg > val;

			case GreaterOrEqual:
				return reg >= val;

			case LessThan:
				return reg < val;

			case LessOrEqual:
				return reg <= val;

			case Equal:
				return reg == val;

			case NotEqual:
				return reg != val;

			default:
				ERROR_BREAK("Unhandled comparison!: ", condition.Comparator);
				return false;
			}
		}

	public:
		int GetRegister(string name)
		{
			auto registerIter = _registers.find(name);
			if (registerIter != _registers.end())
			{
				return registerIter->second;
			}
			else
			{
				_registers[name] = 0;
				return 0;
			}
		}

		int GetLargestHistoricalRegisterValue()
		{
			return _highestValue;
		}

		static bool RegisterCompare(const pair<string, int>& p1, const pair<string, int>& p2)
		{
			return p1.second < p2.second;
		}

		int GetLargestCurrentRegisterValue()
		{
			auto iter = std::max_element(_registers.begin(), _registers.end(), RegisterCompare);
			return iter->second;
		}

		void RunProgram(vector<Instruction> program)
		{
			for (Instruction instruction : program)
			{
				int conditionRegister = GetRegister(instruction.Condition.Register);
				int conditionValue = instruction.Condition.Value;

				if (Evaluate(instruction.Condition))
				{
					int reg = GetRegister(instruction.Register);

					switch (instruction.Operator)
					{
					case Operator::Inc:
						reg += instruction.Value;
						break;

					case Operator::Dec:
						reg -= instruction.Value;
						break;

					default:
						ERROR_BREAK("Unhandled operator!: ", instruction.Operator);
						break;
					}

					if (reg > _highestValue)
					{
						_highestValue = reg;
					}

					_registers[instruction.Register] = reg;
				}
			}
		}
	};
}


Day8::Day8()
{

}


std::string Day8::Solve()
{
	vector<Instruction> program = LoadProgram("Day8Input.txt");

	Day8Utils::Cpu cpu;
	cpu.RunProgram(program);

	int solution1 = cpu.GetLargestCurrentRegisterValue();
	int solution2 = cpu.GetLargestHistoricalRegisterValue();

	stringstream solutionStream;
	solutionStream << "1: " << solution1;
	solutionStream << endl;
	solutionStream << "2: " << solution2;

	return solutionStream.str();
}


