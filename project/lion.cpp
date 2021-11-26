#include "lion.h"
#include <iostream>

using namespace std;

Lion::Lion(Color color, int y, int x) : Piece(color, y, x)
{
    setName(PIECE_NAME[LION - 1]);
    setRank(LION);
}

bool Lion::isMoveValid(Board *board, int y, int x)
{
    /* make use of the isJumpable() function inherited from Jumper
             to check if horizontal and vertical jump can be done */

    if (abs(getY() - y) + abs(getX() - x) != 1) // move other than 1 square
    {
        // Check if is jumpable

        // Horizontal Jump
        if (y == this->getY() && x != this->getX())
        {
            return isJumpable(board, this, y, x, abs(x - this->getX()));
        }

        // Vertical Jump
        if (x == this->getX() && y != this->getY())
        {
            return isJumpable(board, this, y, x, abs(y - this->getY()));
        }

        return false;
    }

    return Piece::isMoveValid(board, y, x);
}
