#pragma once
#include <string>

class Point {

	friend class TestSuite; // allows TestSuite access to private members for testing

private:
	int x, y;

public:

	//Default construct for a point, will initialize the value of x and y to zero
	Point();

	/// Constructor for a point which takes in x and y values, and sets those as the values of the point
	Point(int x, int y);

	//return the value of y
	int getY() const;// { return y; }

	//return the value of x
	int getX() const;// { return x; }

	//set the value of x 
	void setX(int x);

	//set the value of y
	void setY(int y);

	//set the value of both x and y
	void setXY(int x, int y);

	//swap the value of x for the value of y, and vice versa
	void swapXY();

	//multiply x by the supplied factor
	void multiplyX(int factor);

	//multiply y by the supplied factor
	void multiplyY(int factor);

	// return a string in the form "[x,y]" to representthe state of the Point instance (for debugging)
	// You could use stringstream if you want to try a forming a string in the same way we use cout
	std::string toString() const;
};