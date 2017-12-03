#pragma once

#define ERROR_BREAK( message, ... ) Common::ErrorVargs(__FILE__, __LINE__, #message, __VA_ARGS__);

namespace Common
{
	void Error(const char* file, unsigned line, const char* message);
	void ErrorVargs(const char* file, unsigned line, const char* message, ...);
}
