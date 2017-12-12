#pragma once

#include <string>

namespace Common
{
	class ParseInt
	{
	public:
		ParseInt() {}
		int operator() (std::string str);
	};

	class ParseString
	{
	public:
		ParseString() {}
		std::string operator() (std::string str)
		{
			return str;
		}
	};
}