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
    if (p->getRank() == ELEPHANT && !isOnRiver())
        return true;

    // A Rat can capture a Rat that is also on River
    if (isOnRiver() && p->getRank() == RAT && ((Rat *)p)->isOnRiver())
        return true;

    return !isOnRiver() && Piece::canCapture(p);
}

void Rat::move(Board *board, int y, int x)
{
    m_isOnRiver = board->isRiver(y, x);

    Piece::move(board, y, x);
}

bool Rat::isOnRiver()
{
    return m_isOnRiver;
}