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
}