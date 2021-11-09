#include <iostream>
#include <cmath>
#include "KnightsPath.h"

using namespace std;

KnightsPath::KnightsPath(int r, int c)
{
    // Init board
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = -1;

    // Init private fields
    steps = 0;
    previousC = -1;
    previousR = -1;
    currentC = c;
    currentR = r;
    // init position
    board[r][c] = 0;
}

void KnightsPath::print() const
{
    cout << ' '; // Margin
    // Header
    for (int i = 0; i < N; i++)
        cout << "  " << char('A' + i);
    cout << endl;

    for (int i = 0; i < N; i++)
    {
        // Col name
        cout << i;

        // Content
        for (int j = 0; j < N; j++)
        {
            switch (board[i][j])
            {
            case -1:
                cout << "  .";
                break;

            case 0:
                cout << "  k";
                break;

            default:
                if (steps == board[i][j])
                    cout << "  K";
                else
                {
                    if (board[i][j] < 10)
                        cout << "  ";
                    else
                        cout << " ";
                    cout << board[i][j];
                }
                break;
            }
        }
        cout << endl;
    }

    // Steps
    cout << "Steps: " << steps << endl;
}

int KnightsPath::getSteps() const
{
    return steps;
}

bool KnightsPath::isValid(int r, int c) const
{
    // Check if it is within range
    // cout << "DEBUG: " << (c >= 0 && c < KnightsPath::N) << " " << (r >= 0 && r < KnightsPath::N) << " " << (board[r][c] == -1) << endl;
    if ((c >= 0 && c < KnightsPath::N) &&
        (r >= 0 && r < KnightsPath::N) &&
        (board[r][c] == -1))
    {
        // Check if it is a valid move for a knight
        // cout << "DEBUG: " << (-2 < 2) << endl;
        for (int i = -2; i <= 2; i += 4)
        {
            for (int j = -1; j <= 1; j += 2)
            {
                // cout << "DEBUG: (" << (currentR + i == r) << " && " << (currentC + j == c) << ") || (" << (currentR + j == r) << " && " << (currentC + i == c) << ")" << endl;
                if ((currentR + i == r && currentC + j == c) ||
                    (currentR + j == r && currentC + i == c))
                {
                    // Check if it is going backward by its distance
                    if (steps > 0)
                        return pow(r - previousR, 2) + pow(c - previousC, 2) > 4;
                    else
                        return true;
                }
            }
        }
    }

    return false;
}

bool KnightsPath::hasMoreMoves() const
{
    // Check for every possible move if they are a valid move
    for (int i = -2; i <= 2; i += 4)
    {
        for (int j = -1; j <= 1; j += 2)
        {
            if (isValid(currentR + i, currentC + j) ||
                isValid(currentR + j, currentC + i))
                return true;
        }
    }
    return false;
}

bool KnightsPath::move(int r, int c)
{
    if (isValid(r, c))
    {
        // Change the previous position
        previousR = currentR;
        previousC = currentC;

        // Change the current position
        currentC = c;
        currentR = r;

        // change position on board to the step number
        board[r][c] = ++steps;

        return true;
    }
    else
    {
        // Update nothing
        return false;
    }
}