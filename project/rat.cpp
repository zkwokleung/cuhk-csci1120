#include "rat.h"
#include <iostream>

using namespace std;

Rat::Rat(Color color, int y, int x) : Piece(color, y, x)
{
    setName(PIECE_NAME[RAT - 1]);
    setRank(RAT);
}

bool Rat::isMoveValid(Board *board, int y, int x)
{
    if (abs(getY() - y) + abs(getX() - x) != 1) // move other than 1 square
        return false;

    Piece *q = board->get(y, x);
    // allow a Rat to move into a square occuppied by an Elephant
    if (q != EMPTY)
        return canCapture(q);

    // allow a Rat to enter a water square
    // Just don't return false when it is a river
    return true;
}

bool Rat::canCapture(Piece *p)
{
    // A Rat can capture an Elephant
    if (p->getRank() == ELEPHANT)
        return true;

    return Piece::canCapture(p);
}