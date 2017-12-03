#pragma once

#include <vector>


namespace Common
{
	class TsvParser
	{
	public:
		TsvParser(const char* fileName);
		std::vector <std::vector<int>> TsvParser::Parse();

	private:
		const char* _pFileName;
	};
}
