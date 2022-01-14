#include "TetrisGame.h"
//#include "Tetromino.h"
#include <iostream>
#include <cassert>

// constructor
//   initialize/assign variables
//   reset() the game
//   load font from file: fonts/RedOctober.ttf
//   setup scoreText
TetrisGame::TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, Point gameboardOffset, Point nextShapeOffset)

	:window(window), blockSprite(blockSprite), gameboardOffset(gameboardOffset), nextShapeOffset(nextShapeOffset) {

	reset();

	//set font for drawing the score
	if (!scoreFont.loadFromFile("fonts/RedOctober.ttf")) {
		assert(false && "Missing Font: RedOctober.ttf");
	};
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(435, 325);


	//currentShape.setShape(currentShape.getRandomShape());
	//currentShape.setGridLoc(board.getSpawnLoc());
	//board.setContent(Gameboard::MAX_X / 2, Gameboard::MAX_Y / 2, 1);

}

// Draw anything to do with the game,
//   includes the board, currentShape, nextShape, score
//   called every game loop
void TetrisGame::draw() {

	drawGameboard();
	drawTetromino(currentShape, gameboardOffset);
	drawTetromino(nextShape, nextShapeOffset);
	window.draw(scoreText);

	//std::cout << "Next Offset X: " << std::to_string(nextShapeOffset.getX()) << "\n"; //54
	//std::cout << "Next Offset Y: " << std::to_string(nextShapeOffset.getY()) << "\n"; //125
}

// Event and game loop processing
// handles keypress events (up, left, right, down, space)
void TetrisGame::onKeyPressed(sf::Event event) {

	switch (event.key.code) {
	case sf::Keyboard::Up:
		attemptRotate(currentShape);
		break;
	case sf::Keyboard::Left:
		attemptMove(currentShape, -1, 0);
		break;
	case sf::Keyboard::Right:
		attemptMove(currentShape, 1, 0);
		break;
	case sf::Keyboard::Down:
		if (!attemptMove(currentShape, 0, 1)) {
			lock(currentShape);
			shapePlacedSinceLastGameLoop = true;
		}
		break;
	case sf::Keyboard::Space:
		drop(currentShape);
		lock(currentShape);
		shapePlacedSinceLastGameLoop = true;
		break;
	}

}

// called every game loop to handle ticks & tetromino placement (locking)
void TetrisGame::processGameLoop(float secondsSinceLastLoop) {

	secondsSinceLastTick += secondsSinceLastLoop;

	if (shapePlacedSinceLastGameLoop) {
		if (!spawnNextShape()) {
			reset(); //game over
		}
		else {
			pickNextShape();
			int rowsRemoved = board.removeCompletedRows();
			if (rowsRemoved == 2) {
				score += (rowsRemoved * 2);
			}
			else if (rowsRemoved == 3) {
				score += (rowsRemoved * 3);
			}
			else if (rowsRemoved >= 4) {
				score += (rowsRemoved * 4);
			}
			else {
				score += rowsRemoved;
			}
			updateScoreDisplay();
			determineSecondsPerTick();
		}
		shapePlacedSinceLastGameLoop = false;
	}

	if (secondsSinceLastTick >= secondsPerTick) {
		tick();
		secondsSinceLastTick = (secondsSinceLastTick - secondsPerTick);
		//std::cout << secondsSinceLastTick << "\n";
	}
}

// A tick() forces the currentShape to move (if there were no tick,
// the currentShape would float in position forever). This should
// call attemptMove() on the currentShape.  If not successful, lock() 
// the currentShape (it can move no further), and record the fact that a
// shape was placed (using shapePlacedSinceLastGameLoop)
void TetrisGame::tick() {

	if (!attemptMove(currentShape, 0, 1)) {
		lock(currentShape);
		shapePlacedSinceLastGameLoop = true;
	}
}

//private:

	// reset everything for a new game (use existing functions) 
	//  - set the score to 0 and call updateScoreDisplay()
	//  - call determineSecondsPerTick() to determine the tick rate.
	//  - clear the gameboard,
	//  - pick & spawn next shape
	//  - pick next shape again (for the "on-deck" shape)
void TetrisGame::reset() {
	score = 0;
	updateScoreDisplay();
	determineSecondsPerTick();
	board.empty();
	pickNextShape();
	spawnNextShape();
	pickNextShape();

}

// assign nextShape.setShape a new random shape  
void TetrisGame::pickNextShape() {
	
	nextShape.setShape(nextShape.getRandomShape());

}

// copy the nextShape into the currentShape (through assignment)
//   position the currentShape to its spawn location.
//	 - return true/false based on isPositionLegal()
bool TetrisGame::spawnNextShape() {

	currentShape = nextShape;
	currentShape.setGridLoc(board.getSpawnLoc());

	return isPositionLegal(currentShape);

}

// Test if a rotation is legal on the tetromino and if so, rotate it. 
//  To do this:
//	 1) create a (local) temporary copy of the tetromino
//	 2) rotate it (shape.rotateClockwise())
//	 3) test if temp rotation was legal (isPositionLegal()), 
//      if so - rotate the original tetromino.
//	 4) return true/false to indicate successful movement
bool TetrisGame::attemptRotate(GridTetromino& shape) {

	GridTetromino tempTet = shape;
	tempTet.rotateClockwise();
	if (isPositionLegal(tempTet)) {
		shape.rotateClockwise();
		return true;
	}

	return false;
}

// test if a move is legal on the tetromino, if so, move it.
//  To do this:
//	 1) create a (local) temporary copy of the tetromino
//	 2) move it (temp.move())
//	 3) test if temp move was legal (isPositionLegal(),
//      if so - move the original.
//	 4) return true/false to indicate successful movement
bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y) {

	GridTetromino tempTet = shape;
	tempTet.move(x,y);
	if (isPositionLegal(tempTet)) {
		shape.move(x,y);
		return true;
	}

	return false;
}

// drops the tetromino vertically as far as it can 
//   legally go.  Use attemptMove(). This can be done in 1 line.
void TetrisGame::drop(GridTetromino& shape) {

	while (attemptMove(shape, 0, 1)) {};

}

// copy the contents (color) of the tetromino's mapped block locs to the grid.
//	 1) get the tetromino's mapped locs via tetromino.getBlockLocsMappedToGrid()
//   2) make Gameboard's isValidPoint() methods public
//	 2) iterate through the mapped locations, if the location is a valid point 
//      (according to the gameboard) then use Gameboard.setContent() to set the
//      board content to be the color of the tetromino. 
void TetrisGame::lock(const GridTetromino& shape) {

	for (Point& pt : shape.getBlockLocsMappedToGrid()) {
		if (board.isValidPoint(pt)) {
			board.setContent(pt, static_cast<int>(shape.getColor()));
		}
	}

}

// Graphics methods ==============================================

// Draw a tetris block sprite on the canvas		
// The block position is specified in terms of 2 offsets: 
//    1) the top left (of the gameboard in pixels)
//    2) an x & y offset into the gameboard - in blocks (not pixels)
//       meaning they need to be multiplied by BLOCK_WIDTH and BLOCK_HEIGHT
//       to get the pixel offset.
//	 1) set the block color using blockSprite.setTextureRect()
//   2) set the block location using blockSprite.setPosition()   
//	 3) draw the block using window.draw()
//   For details/instructions on these 3 operations see:
//       www.sfml-dev.org/tutorials/2.5/graphics-sprite.php
//       use member variables: window and blockSprite (assigned in constructor)
void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, TetColor color) {

	sf::IntRect blockTexture = sf::IntRect(static_cast<int>(color) * BLOCK_WIDTH, 0, BLOCK_WIDTH, BLOCK_HEIGHT);
	blockSprite.setTextureRect(blockTexture);
	blockSprite.setPosition(topLeft.getX() + (xOffset * BLOCK_WIDTH), topLeft.getY() + (yOffset * BLOCK_HEIGHT));
	window.draw(blockSprite);


}

// Draw the gameboard blocks on the window
//   Iterate through each row & col, use drawBlock() to 
//   draw a block if it isn't empty.
void TetrisGame::drawGameboard() {

	for (int y{ 0 }; y < Gameboard::MAX_Y; y++) {
		for (int x{ 0 }; x < Gameboard::MAX_X; x++) {
			if (board.getContent(x, y) != Gameboard::EMPTY_BLOCK) {
				drawBlock(gameboardOffset, x, y, static_cast<TetColor>(board.getContent(x, y)));
			}
		}
	}

}


// Draw a tetromino on the window
//	 Iterate through each mapped loc & drawBlock() for each.
//   The topLeft determines a 'base point' from which to calculate block offsets
//      If the Tetromino is on the gameboard: use gameboardOffset
void TetrisGame::drawTetromino(const GridTetromino& tetromino, const Point& topLeft) {

	int x = tetromino.getGridLoc().getX();
	int y = tetromino.getGridLoc().getY();

	std::cout << "X: " << x << " Y: " << y << "\n";

	for (Point& pt : tetromino.getBlockLocsMappedToGrid()) {
		drawBlock(topLeft, pt.getX(), pt.getY(), tetromino.getColor());
	}

}

// update the score display
// form a string "score: ##" to display the current score
// user scoreText.setString() to display it.
void TetrisGame::updateScoreDisplay() {

	std::string scoreString = "Score: " + std::to_string(score);
	scoreText.setString(scoreString);

}

// State & gameplay/logic methods ================================

// return true if shape is within borders (isShapeWithinBorders()) and the shape's mapped board locs are empty.
//   Make use of Gameboard's areLocsEmpty() and pass it the shape's mapped locs.
bool TetrisGame::isPositionLegal(const GridTetromino& shape) const {

	return (isShapeWithinBorders(shape) && board.areLocsEmpty(shape.getBlockLocsMappedToGrid()));

	//if (isShapeWithinBorders(shape) && board.areLocsEmpty(shape.getBlockLocsMappedToGrid())) {
	//	return true;
	//}
	//else {
	//	return false;
	//}

}

// return true if the shape is within the left, right, and lower border of
//	 the grid, but *NOT* the top border. (return false otherwise)
//   * Ignore the upper border because we want shapes to be able to drop
//     in from the top of the gameboard.
//   All of a shape's blocks must be inside these 3 borders to return true
bool TetrisGame::isShapeWithinBorders(const GridTetromino& shape) const {

	for (Point& pt : shape.getBlockLocsMappedToGrid()) {
		if ( (pt.getX() < 0 || pt.getX() >= board.MAX_X) ||  (pt.getY() >= board.MAX_Y) ){
			return false;
		}
	}
	return true;
}


// set secsPerTick 
//   - basic: use MAX_SECS_PER_TICK
//   - advanced: base it on score (higher score results in lower secsPerTick)
void TetrisGame::determineSecondsPerTick() {

	secondsPerTick = std::max(MIN_SECONDS_PER_TICK, MAX_SECONDS_PER_TICK - (score / 5000.0));
}