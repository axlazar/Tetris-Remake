#include "Point.h"

//Default construct for a point, will initialize the value of x and y to zero
Point::Point()
	: x{ 0 }, y{ 0 }
{
}

/// <summary>
/// Constructor for a point which takes in x and y values, and sets those as the values of the point
/// </summary>
Point::Point(int x, int y)
	: x(x), y(y)
{
}

/// <summary>
/// Returns the value of Y
/// </summary>
int Point::getY() const {
	return y;
}

/// <summary>
/// Returns the value of X
/// </summary>
int Point::getX() const {
	return x;
}

/// <summary>
/// Set's the value of X
/// </summary>
/// <param name="y">
/// The value X will be set to
/// </param>
void Point::setX(int x) {
	this->x = x;
}

/// <summary>
/// Set's the value of Y
/// </summary>
/// <param name="y">
/// The value Y will be set to
/// </param>
void Point::setY(int y) {
	this->y = y;
}

/// <summary>
/// Swaps the values of X and Y.
/// If Initially (1,2), would become (2,1)
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Point::setXY(int x, int y) {
	this->x = x;
	this->y = y;
}

/// <summary>
/// Swaps the value of X and Y
/// 
/// </summary>
void Point::swapXY() {
	int temp = x;
	x = y;
	y = temp;
}

/// <summary>
/// Multiplies X by some factor
/// </summary>
/// <param name="factor">
/// The factor to multiply X by
/// </param>
void Point::multiplyX(int factor) {
	x = x * factor;
}

/// <summary>
/// Multiplies Y by some factor
/// </summary>
/// <param name="factor">
/// The factor to multiply Y by
/// </param>
void Point::multiplyY(int factor) {
	y = y * factor;
}

/// <summary>
/// Returns the (X,Y) points of the shape
/// </summary>
std::string Point::toString() const {
	return "[" + std::to_string(x) + "," + std::to_string(y) + "]";
}