#include <iostream>
#include "game.h"
#include "piece.h"
#include "board.h"

using namespace std;

Piece::Piece(Color color, int y, int x) : 
    color(color), y(y), x(x), trapped(false) {
}

void Piece::setName(string name) {
    this->name = name;
}

string Piece::getName() const {
    return name;
}

char Piece::getLabel() const {
    char c = getName().at(0);
    return color == BLUE ? tolower(c) : c;
}

Color Piece::getColor() const {
    return color;
}

void Piece::setRank(int rank){
    this->rank = rank;
}

int Piece::getRank() const {
    return rank;
}

int Piece::getY() const {
    return y;
}

int Piece::getX() const {
    return x;
}

void Piece::setY(int y) {
    this->y = y;
}

void Piece::setX(int x) {
    this->x = x;
}

bool Piece::isTrapped() {
    return trapped;
}

void Piece::setTrapped(bool trapped) {
    this->trapped = trapped;
}

// Return true if p is an opponent piece of this piece, and false otherwise
bool Piece::isOpponent(Piece* p) {
    if (p != EMPTY && p->getColor() != getColor())
        return true;
    return false;
}

// Return true if this piece can capture piece p (assumed p is an opponent),
// and false otherwise
bool Piece::canCapture(Piece* p) {
    // TODO:
    // Check if this piece's rank is >= p's rank
    // Hint: remember to handle trapped situations
    // ...
}

// Carry out the capture of piece p
void Piece::capture(Board* board, Piece* p) {
    // TODO:
    // Remove the piece from board and opponent player's list of pieces
    // ...

    cout << p->getName() << " of " << player->getName() << " captured!" << endl;
}

// Carry out the move of this piece to (y, x)
void Piece::move(Board* board, int y, int x) {
    // TODO:
    // Hint: by calling suitable existing methods
    
    // capture opponent piece 
    // ...

    // handle rank changes when entering and leaving traps
    // ...

    // check winning conditions
    // (moved into opponent's den or captured all opponent pieces)
    // ...

    // carry out the move
    // ...
}

// Check if moving this piece to (y, x) is valid
// (Subclasses of Piece may override this method for defining special rules)
// [Note: you can modify this function if it doesn't fit your design]
bool Piece::isMoveValid(Board* board, int y, int x) {
    Piece* q = board->get(y, x);  // target cell
    if (isOpponent(q) && !canCapture(q))  // cell occuppied by higher-rank opponent
        return false;
    if (board->isRiver(y, x))  // target is a river cell
        return false;
    return true;
}