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

  int dir = (steps == 2) ? ((p->getX() < x) ? 1 : -1) : ((p->getY() < y) ? 1 : -1);
  for (int i = 0; i < steps; i++)
  {
    // Determine the direction
    int tarY = p->getY() + i * dir;
    int tarX = p->getX() + i * dir;
    if (!board->isRiver(tarY, tarX) || !board->isEmpty(tarY, tarX))
      return false;
  }

  Piece *q = board->get(y, x);
  if (q != EMPTY && !p->canCapture(q)) // cell occuppied by higher-rank opponent
    return false;

  return true;
}