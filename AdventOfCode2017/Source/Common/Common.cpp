#include <iostream>
#include <cstdarg>

using namespace std;

namespace Common
{
	void Error(const char* file, unsigned line, const char* message)
	{
		cout << "Error at " << file << '(' << line << "): " << message << endl;
		system("pause");
		exit(1);
	}


	void ErrorVargs(const char* file, unsigned line, const char* message, ...)
	{
		const size_t kBuffLen = 256;
		char pBuff[kBuffLen];
		va_list args;
		va_start(args, message);
		vsprintf_s(pBuff, kBuffLen, message, args);
		va_end(args);

		Error(file, line, pBuff);
	}
}
