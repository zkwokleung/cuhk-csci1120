#include <iostream>
#include <cctype>
#include "game.h"
#include "board.h"
#include "piece.h"
#include "elephant.h"
#include "lion.h"
// TODO: include more necessary headers
#include "fileman.h"

using namespace std;

Board::Board(Game* game, char* filename) : 
    game(game), cells() {  // initalize cells' elements to nullptr
    // Set up the initial game board
    if (filename != nullptr)
        loadFromFile(filename, this);
    else
        init();
}

// initial gameboard configuration
void Board::init() {
    // TODO:
    // set up the Jungle chess standard initial gameboard properly;
    // add Elephants, Lions, ..., Rats to the cells array at correct positions 
    
    // TODO: also add the created pieces to each player's vector of pieces
}

// Return true if (y, x) is an empty cell, and false otherwise
bool Board::isEmpty(int y, int x) {
    if (cells[y][x] == EMPTY)
        return true;
    return false;
}

// Return true if (y, x) is the den on the side of the specified color, 
// and false otherwise
bool Board::isDen(int y, int x, Color color) {
    // TODO: Add your code here
}

// Return true if (y, x) is a trap on the side of the specified color, 
// and false otherwise
bool Board::isTrap(int y, int x, Color color) {
    // TODO: Add your code here
}

// Return true if (y, x) is a river cell, and false otherwise
bool Board::isRiver(int y, int x) {
    return y >= 3 && y <= 5 && (x >= 1 && x <= 2 || x >= 4 && x <= 5);
}

// Get a piece from the specified cell
Piece* Board::get(int y, int x){
    if (0 <= y && y < H && 0 <= x && x < W)
        return cells[y][x];
    return OUT_BOUND; // out of bound
}

// Put piece p onto the specified cell
void Board::put(int y, int x, Piece* p){
    cells[y][x] = p;
    if (p != EMPTY) {
        p->setY(y);
        p->setX(x);
    }
}

// Print the gameboard
void Board::print() {
    // TODO: Add code to print the HxW gameboard by looping over cells array
    // Hint: Make use of isEmpty(), isRiver(), isTrap(), isDen(), and 
    //       getLabel() of Piece to ease your work
    // Remember * for river cells, # for trap cells, X for den cells

}

// Check if the move from (y1, x1) to (y2, x2) is valid
bool Board::isMoveValid(int y1, int x1, int y2, int x2) {
    // TODO:
    // check against invalid cases, for example,
    // - the source is an empty cell
    // - the source and destination are the same position
    // - the destination is out of bound of the board (hint: use OUT_BOUND)
    // - the source piece is not of same color of current turn of the game
    // (... and anymore ?)
    // [Note: you can modify the following code if it doesn't fit your design]

    // Piece-specific validation
    if (p->isMoveValid(this, y2, x2) == false)
        return false;

    return true;
}

// Carry out the move from (y1, x1) to (y2, x2)
bool Board::move(int y1, int x1, int y2, int x2) {
    if (isMoveValid(y1, x1, y2, x2)) {
        get(y1, x1)->move(this, y2, x2);
        return true;
    }
    return false;
}

// Return the pointer to the Game object
Game* Board::getGame() const {
    return game;
}
