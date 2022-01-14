#pragma once
#include "Point.h"
#include <vector>

enum class TetColor {
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE_LIGHT,
	BLUE_DARK,
	PURPLE
};

enum class TetShape {
	S,
	Z,
	L,
	J,
	O,
	I,
	T,
	COUNT
};

class Tetromino {

	friend class TestSuite; // allows TestSuite access to private members for testing

private:
	TetColor color;
	TetShape shape;

protected:
	std::vector<Point>blockLocs;

public:

	Tetromino();

	TetColor getColor() const;

	TetShape getShape() const;

	// Set Shape
	// Clear any blockLocs set previously
	// set the blockLocs for the shape
	// Set the color for the shape
	void setShape(TetShape shape);

	//Generate a random shape
	TetShape getRandomShape();

	//Rotate the shape 90 degrees around [0,0] (clockwise)
	// To do this:
	//	- iterate through blockLocs
	//	- rotate each point 90 degrees around [0,0]
	// Hint: rotate the point [1,2] clockwise around [0,0] and note how the x and y values change. 
	// Hint: there are two functions in the point class that can be used to accomplish a rotatation.
	void rotateClockwise();

	// Print a grid to display the current shape
	// To do this:
	//	- print out a "grid" of text to represent a co-ordinate system.
	//	- Start at the top left [-3, 3], go to bottom right [3, -3] (use nested for loops)
	//	- For each [x,y] point, loop through blockLocs and if the point exists in the list, print an 'x' instead of a '.'
	//	- Example:
	// .......
	// .......
	// ...x...
	// ..xx...
	// ...x...
	// .......
	void printToConsole() const;
};