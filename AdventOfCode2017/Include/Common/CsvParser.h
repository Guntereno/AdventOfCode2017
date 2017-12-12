#pragma once

#include "Common/Common.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


namespace Common
{
	template <class TCell, class TCompare>
	class CsvParser
	{
	public:
		CsvParser(const char* fileName, TCompare compare, char separator, char newLine):
			_pFileName(fileName),
			_compare(compare),
			_separator(separator),
			_newLine(newLine)
		{}

		std::vector <std::vector<TCell>> CsvParser::Parse()
		{
			vector <vector<TCell>> data;

			ifstream inputFile;
			inputFile.open(_pFileName, ifstream::in);

			if (inputFile.is_open())
			{
				char c;
				vector<int> currentRow;
				stringstream cellStream;
				while (inputFile.get(c))
				{
					if(c == _separator)
					{
						int value = stoi(cellStream.str());
						currentRow.push_back(value);

						cellStream.str("");
						cellStream.clear();
					}
					else if (c == _newLine)
					{
						int value = _compare(cellStream.str());
						currentRow.push_back(value);

						data.push_back(currentRow);

						cellStream.str("");
						currentRow.clear();
					}
					else
					{
						cellStream << c;
						break;
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

	private:
		const char* _pFileName;
		TCompare _compare;
		char _separator;
		char _newLine;
	};
}
