#include "Common\Point.h"


using namespace std;

Point Point::operator+ (const Point& other) const
{
	return Point
	{
		X + other.X,
		Y + other.Y
	};
}

int Point::GetManhattanMagnitude() const
{
	return abs(X) + abs(Y);
}

ostream& operator<<(ostream& stream, const Point& point)
{
	stream << "[" << point.X << "," << point.Y << "]";
	return stream;
}
