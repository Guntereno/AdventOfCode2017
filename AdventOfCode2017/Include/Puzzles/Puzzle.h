#pragma once

#include <string>

class Puzzle
{
public:
	virtual ~Puzzle() {};
    virtual std::string Solve() = 0;
};

