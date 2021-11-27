#include "tiger.h"
#include <iostream>

using namespace std;

Tiger::Tiger(Color color, int y, int x) : Piece(color, y, x)
{
    setName(PIECE_NAME[TIGER - 1]);
    setRank(TIGER);
}

bool Tiger::isMoveValid(Board *board, int y, int x)
{
    if (abs(getY() - y) + abs(getX() - x) != 1) // move other than 1 square
    {
        // Check if is jumpable

        // Horizontal Jump
        if (y == this->getY() && x != this->getX())
        {
            return isJumpable(board, this, y, x, abs(x - this->getX()) - 1);
        }

        // Vertical Jump
        if (x == this->getX() && y != this->getY())
        {
            return isJumpable(board, this, y, x, abs(y - this->getY()) - 1);
        }

        return false;
    }

    return Piece::isMoveValid(board, y, x);
}
