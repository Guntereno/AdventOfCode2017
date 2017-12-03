#pragma once

#include <iostream>

struct Point
{
	int X = 0;
	int Y = 0;

	Point operator+ (const Point& other) const;
	int GetManhattanMagnitude() const;

	friend std::ostream& operator<<(std::ostream& os, const Point& dt);
};
