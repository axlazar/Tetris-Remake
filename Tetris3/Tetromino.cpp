#include "Tetromino.h"
#include "Point.h"
#include <iostream>

#define PRINT(x) std::cout << x

Tetromino::Tetromino()
{
	setShape(getRandomShape());
}

TetColor Tetromino::getColor() const {
	return color;
};

TetShape Tetromino::getShape() const {
	return shape;
};

TetShape Tetromino::getRandomShape() {

	return static_cast<TetShape>(rand() % static_cast<int>(TetShape::COUNT));

}

// Set Shape
// Clear any blockLocs set previously
// set the blockLocs for the shape
// Set the color for the shape
void Tetromino::setShape(TetShape shape) {
	blockLocs.empty();
	this->shape = shape;
	//case to determine color, and where the blocLocs are
	switch (shape) {
	case TetShape::S:
		blockLocs = { Point(-1,0), Point(0,0), Point(0,1), Point(1,1) };
		color = TetColor::RED;
		break;
	case TetShape::Z:
		blockLocs = { Point(-1,1), Point(0,1), Point(0,0), Point(1,0) };
		color = TetColor::GREEN;
		break;
	case TetShape::L:
		blockLocs = { Point(0,1), Point(0,0), Point(0,-1), Point(1, -1) };
		color = TetColor::ORANGE;
		break;
	case TetShape::J:
		blockLocs = { Point(0,1), Point(0,0), Point(0,-1), Point(-1,-1) };
		color = TetColor::BLUE_DARK;
		break;
	case TetShape::O:
		blockLocs = { Point(0,1), Point(1,1), Point(0,0), Point(1,0) };
		color = TetColor::YELLOW;
		break;
	case TetShape::I:
		blockLocs = { Point(0,-1), Point(0,0), Point(0,1), Point(0,2) };
		color = TetColor::BLUE_LIGHT;
		break;
	case TetShape::T:
		blockLocs = { Point(-1,0), Point(0,0), Point(0,-1), Point(1,0) };
		color = TetColor::PURPLE;
		break;
	}

};

//Rotate the shape 90 degrees around [0,0] (clockwise)
// To do this:
//	- iterate through blockLocs
//	- rotate each point 90 degrees around [0,0]
// Hint: rotate the point [1,2] clockwise around [0,0] and note how the x and y values change. 
// Hint: there are two functions in the point class that can be used to accomplish a rotatation.
void Tetromino::rotateClockwise() {

	for (Point& each : blockLocs) {

		//std::cout << "X is now: " << each.getX() << "\n";
		//std::cout << "Y is now: " << each.getY() << "\n";
		each.swapXY();
		each.multiplyY(-1);
		//std::cout << "Swapping...\n";
		//std::cout << "X is now: " << each.getX() << "\n";
		//std::cout << "Y is now: " << each.getY() << "\n";
		//std::cout << "Done Swap\n\n";
	}

};

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
void Tetromino::printToConsole() const {
	for (int y{ 3 }; y > -3; y--) {
		for (int x{ -3 }; x < 3; x++) {
			char toPrint{ '.' };
			for (Point each : blockLocs) {
				if (each.getX() == x && each.getY() == y) {
					toPrint = 'x';
				}
			}
			std::cout << toPrint << ' ';
		}
		std::cout << std::endl;
	}
};