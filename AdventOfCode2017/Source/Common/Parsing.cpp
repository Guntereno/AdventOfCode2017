#include "Common/Parsing.h"

namespace Common
{
	int ParseInt::operator() (std::string str)
	{
	return stoi(str);
	}
}