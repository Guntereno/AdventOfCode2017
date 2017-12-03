#include "Common/TsvParser.h"
#include "Common/Common.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


namespace Common
{
	TsvParser::TsvParser(const char* fileName)
	{
		_pFileName = fileName;
	}

	std::vector <std::vector<int>> TsvParser::Parse()
	{
		vector <vector<int>> data;

		ifstream inputFile;
		inputFile.open(_pFileName, ifstream::in);

		if (inputFile.is_open())
		{
			char c;
			vector<int> currentRow;
			stringstream cellStream;
			while (inputFile.get(c))
			{
				switch (c)
				{
				case '\t':
				{
					int value = stoi(cellStream.str());
					currentRow.push_back(value);

					cellStream.str("");
					cellStream.clear();
				}
				break;


				case '\n':
				{
					int value = stoi(cellStream.str());
					currentRow.push_back(value);

					data.push_back(currentRow);

					cellStream.str("");
					currentRow.clear();
				}
				break;

				default:
				{
					cellStream << c;
					break;
				}
				}
			}

			inputFile.close();
		}
		else
		{
			ERROR_BREAK("Failed to load file: %s", _pFileName);
		}

		return data;
	}
}