#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <assert.h>
#include "Point.h"
#include "Gameboard.h"

//Y = Rows
//X = Columns


// constructor - empty() the grid
Gameboard::Gameboard() {

	empty();
}

// return the content at a given point (assert the point is valid)
int Gameboard::getContent(const Point& pt) const {

	assert(isValidPoint(pt));

	//int gridTest = grid[pt.getY()][pt.getX()];
	//std::cout << "result of getContent using Point:" << gridTest << '\n';

	return (grid[pt.getY()][pt.getX()]);
}

// return the content at an x,y grid loc (assert the point is valid)
int Gameboard::getContent(int x, int y) const {

	assert(isValidPoint(x, y));

	//int pointTest = grid[x][y];
	//std::cout << "result of getContent using x,y:" << pointTest << '\n';

	return (grid[y][x]);
}

// return the spawn location of a tetomino
Point Gameboard::getSpawnLoc() const {

	return spawnLoc;

}

// set the content at a given point (only if the point is valid)
void Gameboard::setContent(const Point& pt, int content) {

	assert (isValidPoint(pt));

	grid[pt.getY()][pt.getX()] = content;

}

// set the content at an x,y position (only if the point is valid)
void Gameboard::setContent(int x, int y, int content) {

	assert(isValidPoint(Point(x, y)));

	grid[y][x] = content;

}

// set the content for a set of points (only if the points are valid)
void Gameboard::setContent(const std::vector<Point>& locs, int content) {

	for (const Point& point : locs) {
		setContent(point, content);
	}

}

// return true if the content at ALL (valid) points is empty
//   *** IMPORTANT NOTE: invalid x,y values can be passed to this method.
//   Invalid meaning outside the bounds of the grid.
//   * ONLY TEST VALID POINTS (disregard the others - and ensure you
//   don't use them to index into the grid).  Use isValidPoint() 
//   Testing invalid points would likely result in an out of bounds
//     error or segmentation fault!
//   If none of the points are valid, return true
bool Gameboard::areLocsEmpty(std::vector<Point> locs) const {

	bool isEmpty{ true };

	for (const Point& point : locs) {
		if (isValidPoint(point)) {
			if (grid[point.getY()][point.getX()] != EMPTY_BLOCK) {
				isEmpty = false;
				break;
			}
		}
	}

	return isEmpty;
}

// removes all completed rows from the board
//   use getCompletedRowIndices() and removeRows() 
//   return the # of completed rows removed
int Gameboard::removeCompletedRows() {

	std::vector<int> completedRows{ getCompletedRowIndices() };
	
	removeRows(completedRows);

	return completedRows.size();
}

// fill the board with EMPTY_BLOCK 
//   (iterate through each rowIndex and fillRow() with EMPTY_BLOCK))
void Gameboard::empty() {

	for (int y{ 0 }; y < MAX_Y; y++) {

		fillRow(y, EMPTY_BLOCK);

	}
}

// print the grid contents to the console (for debugging purposes)
//   use std::setw(2) to space the contents out (#include <iomanip>).
void Gameboard::printToConsole() const {

	for (int y{ 0 }; y < MAX_Y; y++) {
		for (int x{ 0 }; x < MAX_X; x++) {

			std::cout << std::setw(2) << grid[x][y];

		}
		std::cout << '\n';
	}
}


//Private

// return a bool indicating if a given row is full (no EMPTY_BLOCK in the row)
bool Gameboard::isRowCompleted(int rowIndex) const {

	for (int x{ 0 }; x < MAX_X; x++) {

		if (grid[rowIndex][x] == EMPTY_BLOCK){
			return false;
		}
	}

	return true;
}

// scan the board for completed rows.
//   Iterate through grid rows and use isRowCompleted(rowIndex)
//   return a vector of completed row indices.
std::vector<int> Gameboard::getCompletedRowIndices() const {

	std::vector<int> myVeccy{};

	for (int rowIndex{ 0 }; rowIndex < MAX_Y; rowIndex++) {

		if (isRowCompleted(rowIndex)) {
			myVeccy.push_back(rowIndex);
		}
	
	}

	//For testing
		//for (int i : myVeccy) {
		//	std::cout << "Completed Row Indicies: " << i << "\n";
		//}

	return myVeccy;
}

// In gameplay, when a full row is completed (filled with content)
// it gets "removed".  To be exact, the row itself is not removed
// but the content from the row above it is copied into it.
// This continues all the way up the grid until the first row
// is copied into the second row.  Finally, the first row is 
// filled with EMPTY_BLOCK
// given a row index:
//   1) Starting at rowIndex, copy each row above the removed
//     row "one-row-downwards" in the grid.
//     (loop from y=rowIndex down to 0, and copyRowIntoRow(y-1, y)).
//   2) call fillRow() on the first row (and place EMPTY_BLOCKs in it).
void Gameboard::removeRow(int rowIndex) {

	for (int y{ rowIndex }; y > 0; y--) {

		copyRowIntoRow((y - 1), y);

	}

	fillRow(0, EMPTY_BLOCK);
}

// given a vector of row indices, remove them 
//   (iterate through the vector and and call removeRow()
//   on each row index). 
void Gameboard::removeRows(const std::vector<int>& rowIndices) {

	for (int rowIndex : rowIndices) {
		removeRow(rowIndex);
	}
}

// fill a given grid row with specified content
void Gameboard::fillRow(int rowIndex, int content) {

	for (int x{ 0 }; x < MAX_X; x++) {
		grid[rowIndex][x] = content;
	}

}

// copy a source row's contents into a target row.
void Gameboard::copyRowIntoRow(int sourceRowIndex, int targetRowIndex) {

	//iterate through source row, copying contents to target row
	int column{ 0 };

	for (int data : grid[sourceRowIndex]) {

		grid[targetRowIndex][column] = data;
		column++;
	}

}

// return true if the point is on the grid, false otherwise
bool Gameboard::isValidPoint(const Point& p) const {

	int x{ p.getX() };
	int y{ p.getY() };

	return (x < MAX_X && x >= 0) && (y < MAX_Y && y >= 0);
}

// return true if the x,y location is on the grid, false otherwise
bool Gameboard::isValidPoint(int x, int y) const {

	return (x < MAX_X && x >= 0) && (y < MAX_Y && y >= 0);
}