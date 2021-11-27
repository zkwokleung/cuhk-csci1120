#include <iostream>
#include <cctype>
#include "game.h"
#include "board.h"
#include "piece.h"
#include "elephant.h"
#include "lion.h"
#include "tiger.h"
#include "leopard.h"
#include "wolf.h"
#include "dog.h"
#include "cat.h"
#include "rat.h"
#include "fileman.h"

using namespace std;

Board::Board(Game *game, char *filename) : game(game), cells()
{ // initalize cells' elements to nullptr
    // Set up the initial game board
    if (filename != nullptr)
        loadFromFile(filename, this);
    else
        init();
}

// initial gameboard configuration
void Board::init()
{
    // 2D array for pieces initial position
    int poss[][2] = {{2, 0}, {1, 5}, {1, 1}, {2, 4}, {2, 2}, {0, 6}, {0, 0}, {2, 6}};

    // set up the Jungle chess standard initial gameboard properly;
    // Color
    for (int c = 0; c <= 1; c++)
    {
        // piece rank
        for (int r = 1; r <= 8; r++)
        {
            int posY = poss[r - 1][0];
            int posX = poss[r - 1][1];
            posY = ((Color)c == BLUE) ? posY : 8 - posY;
            posX = ((Color)c == BLUE) ? posX : 6 - posX;
            Piece *p;
            switch ((Rank)r)
            {
            case RAT:
                p = new Rat((Color)c, posY, posX);
                break;
            case CAT:
                p = new Cat((Color)c, posY, posX);
                break;

            case DOG:
                p = new Dog((Color)c, posY, posX);
                break;

            case WOLF:
                p = new Wolf((Color)c, posY, posX);
                break;

            case LEOPARD:
                p = new Leopard((Color)c, posY, posX);
                break;

            case TIGER:
                p = new Tiger((Color)c, posY, posX);
                break;

            case LION:
                p = new Lion((Color)c, posY, posX);
                break;

            case ELEPHANT:
                p = new Elephant((Color)c, posY, posX);
                break;

            default:
                // Shouldn't even get down here
                p = EMPTY;
                break;
            }
            put(posY, posX, p);
            getGame()->getPlayer((Color)c)->addPiece(p);
        }
    }
}

// Return true if (y, x) is an empty cell, and false otherwise
bool Board::isEmpty(int y, int x)
{
    if (cells[y][x] == EMPTY)
        return true;
    return false;
}

// Return true if (y, x) is the den on the side of the specified color,
// and false otherwise
bool Board::isDen(int y, int x, Color color)
{
    return (x == 3) && ((color == BLUE) ? y == 0 : y == 8);
}

// Return true if (y, x) is a trap on the side of the specified color,
// and false otherwise
bool Board::isTrap(int y, int x, Color color)
{
    switch (color)
    {
    case BLUE:
        return (y == 0 && (x == 2 || x == 4)) || (x == 3 && y == 1);
        break;
    case RED:
        return (y == 8 && (x == 2 || x == 4)) || (y == 7 && x == 3);
        break;
    default:
        return false;
        break;
    }
}

// Return true if (y, x) is a river cell, and false otherwise
bool Board::isRiver(int y, int x)
{
    return y >= 3 && y <= 5 && (x >= 1 && x <= 2 || x >= 4 && x <= 5);
}

// Get a piece from the specified cell
Piece *Board::get(int y, int x)
{
    if (0 <= y && y < H && 0 <= x && x < W)
        return cells[y][x];
    return OUT_BOUND; // out of bound
}

// Put piece p onto the specified cell
void Board::put(int y, int x, Piece *p)
{
    cells[y][x] = p;
    if (p != EMPTY)
    {
        p->setY(y);
        p->setX(x);
    }
}

// Print the gameboard
void Board::print()
{
    // print the HxW gameboard by looping over cells array
    // * for river cells, # for trap cells, X for den cells

    // Column Header
    cout << "   ";
    for (int i = 0; i < 7; i++)
        cout << " " << char('A' + i) << "  ";
    cout << endl;
    // Row frame
    cout << "  ";
    for (int i = 0; i < 29; i++)
        cout << ((i % 4 == 0) ? '+' : '-');
    cout << endl;

    // Row
    for (int row = 0; row < 9; row++)
    {
        // Row number
        cout << row + 1;
        // Column frame
        cout << " | ";
        for (int col = 0; col < 7; col++)
        {

            // Board content
            if (get(row, col) != nullptr)
            {
                // Print the piece
                cout << get(row, col)->getLabel();
            }
            else
            {
                // Print environment

                if (isTrap(row, col, BLUE) || isTrap(row, col, RED))
                    cout << "#";
                else if (isRiver(row, col))
                    cout << "*";
                else if (isDen(row, col, BLUE) || isDen(row, col, RED))
                    cout << "X";
                else if (isEmpty(row, col))
                    cout << " ";
                else
                    cout << "?";
            }

            // Column frame
            cout << " | ";
        }
        cout << endl;

        // Row frame
        cout << "  ";
        for (int i = 0; i < 29; i++)
            cout << ((i % 4 == 0) ? '+' : '-');
        cout << endl;
    }
}

// Check if the move from (y1, x1) to (y2, x2) is valid
bool Board::isMoveValid(int y1, int x1, int y2, int x2)
{
    // - the source is an empty cell
    if (get(y1, x1) == EMPTY || get(y1, x1) == OUT_BOUND)
        return false;

    // - the source and destination are the same position
    if (y1 == y2 && x1 == x2)
        return false;

    // - the destination is out of bound of the board (hint: use OUT_BOUND)
    if (get(y2, x2) == OUT_BOUND)
        return false;

    // - the source piece is not of same color of current turn of the game
    if (getGame()->getTurn() != get(y1, x1)->getColor())
        return false;

    // Piece-specific validation
    return get(y1, x1)->isMoveValid(this, y2, x2);
}

// Carry out the move from (y1, x1) to (y2, x2)
bool Board::move(int y1, int x1, int y2, int x2)
{
    if (isMoveValid(y1, x1, y2, x2))
    {
        get(y1, x1)->move(this, y2, x2);
        return true;
    }
    return false;
}

// Return the pointer to the Game object
Game *Board::getGame() const
{
    return game;
}
