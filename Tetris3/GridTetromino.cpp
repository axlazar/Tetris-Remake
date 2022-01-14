#include "GridTetromino.h"
#include "Tetromino.h"
#include "Point.h"
#include <vector>
#include <iostream>


// constructor, initialize gridLoc to 0,0
GridTetromino::GridTetromino() {

	setGridLoc(0, 0);

};

// return the tetromino's grid/gameboard loc (x,y)
Point GridTetromino::getGridLoc() const {

	return this->gridLoc;

};

// sets the tetromino's grid/gameboard loc using x,y
void GridTetromino::setGridLoc(int x, int y) {

	gridLoc.setXY(x,y);

};

// sets the tetromino's grid/gameboard loc using a Point
void GridTetromino::setGridLoc(const Point& pt) {

	gridLoc = pt;

};

// transpose the gridLoc of this shape
//	(1,0) represents a move to the right (x+1)
//	(-1,0) represents a move to the left (x-1)
//	(0,1) represents a move down (y+1)
//	(0,-1) represents a move up? (y-1)
void GridTetromino::move(int xOffset, int yOffset) {

	gridLoc.setXY((gridLoc.getX() + xOffset), (gridLoc.getY() + yOffset));

};

// build and return a vector of Points to represent our inherited
// blockLocs vector mapped to the gridLoc of this object instance.
// You will need to provide this class access to blockLocs (from the Tetromino class).
// eg: if we have a Point [x,y] in our vector,
// and our gridLoc is [5,6] the mapped Point would be [5+x,6+y].
std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const {

	std::vector<Point> mappedLocs{};

	for (Point pt : blockLocs) {

		//Point myPoint = (pt.getX() + gridLoc.getX(), pt.getY() + gridLoc.getY());

		mappedLocs.push_back(Point(pt.getX() + gridLoc.getX(), pt.getY() + gridLoc.getY()));
	}

	return mappedLocs;

};