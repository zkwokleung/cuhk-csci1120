#include <iostream>
#include <time.h>
#include <algorithm>
#include <array>
#include <vector>
#include "machine.h"
#include "game.h"
#include "board.h"

using namespace std;

Machine::Machine(string name, Color color) : Player(name, color)
{
    // randomize the seed of random number generator using the current time
    srand(time(NULL));
}

// a sample machine that makes random valid moves
void Machine::makeMove(Board *board)
{
    // {pieceIdx, Y, X}
    vector<array<int, 3>> moves;

    // Generate a list of all valid moves
    for (int i = 0; i < getPieceCount(); i++)
    {
        Piece *p = getPiece(i);

        // Check for the surrounding 4 cells
        for (int dir = -1; dir <= 1; dir += 2)
        {
            // if it is a valid move for p, add to the list
            if (p->isMoveValid(board, p->getY() + dir, p->getX()))
                moves.push_back({i, p->getY() + dir, p->getX()});

            if (p->isMoveValid(board, p->getY(), p->getX()))
                moves.push_back({i, p->getY(), p->getX() + dir});

            // Special case for jumpable pieces
            if (p->getRank() == LION || p->getRank() == TIGER)
            {
                int tarY = -1, tarX = -1;
                // Check for jumps
                if (board->isRiver(p->getY() + dir, p->getX()))
                {
                    // 3 steps jump
                    tarY = p->getY() + i * 4;
                    tarX = p->getX();
                }
                else if (board->isRiver(p->getY(), p->getX()))
                {
                    // 2 steps jump
                    tarY = p->getY();
                    tarX = p->getX() + i * 3;
                }

                if (tarY != -1 && tarX != -1)
                {
                    if (p->isMoveValid(board, tarY, tarX))
                        moves.push_back({i, tarY, tarX});
                }
            }
        }
    }

    // Check for surrender
    if (!moves.size())
    {
        board->getGame()->setState(GAME_OVER);
        // set opponent as winner,
        // by flipping the turn
        board->getGame()->setTurn((getColor() == BLUE) ? RED : BLUE);
        return;
    }

    // Pick a random move
    int ran = rand() % moves.size(); // Index of list of moves

    // Perform the move
    int y1 = getPiece(moves[ran][0])->getY();
    int x1 = getPiece(moves[ran][0])->getX();
    board->move(y1, x1, moves[ran][1], moves[ran][2]);
}
