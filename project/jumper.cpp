#include "jumper.h"
#include <algorithm>

using namespace std;

Jumper::Jumper()
{
}

/* Check if animal p can jump over a river
   The 'steps' argument is used to control how many river cells to test.
   Call isJumpable(board, p, y, x, 2) to test if p can do a horizontal river jump (2 steps)
   Call isJumpable(board, p, y, x, 3) to test if p can do a vertical river jump (3 steps)
   Return true if p can jump and false otherwise (e.g. due to blocking by a Rat in river)
 */
bool Jumper::isJumpable(Board *board, Piece *p, int y, int x, int steps)
{
  /* check if p can jump over 'steps' river squares to the destination(y, x) */
  if (steps != 2 && steps != 3)
    return false;

  if (y == p->getY() && x == p->getX())
    return false;

  // Determine the jump direction by the steps and
  int dirX = (steps == 2) ? (x < p->getX() ? -1 : 1) : 0;
  int dirY = (steps == 3) ? (y < p->getY() ? -1 : 1) : 0;
  for (int i = 1; i <= steps; i++)
  {
    // Determine the destination
    int tarY = p->getY() + i * dirY;
    int tarX = p->getX() + i * dirX;

    // return false if it is not a river or the river is not empty
    if (!board->isRiver(tarY, tarX) || !board->isEmpty(tarY, tarX))
    {
      return false;
    }
  }

  Piece *q = board->get(y, x);
  if (q != EMPTY && !p->canCapture(q)) // cell occuppied by higher-rank opponent
    return false;

  return true;
}