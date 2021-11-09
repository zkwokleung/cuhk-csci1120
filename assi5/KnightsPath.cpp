#include <iostream>
#include "KnightsPath.h"

using namespace std;

KnightsPath::KnightsPath(int r, int c)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = -1;

    steps = 0;

    previousC = -1;
    previousR = -1;
    currentC = c;
    currentR = r;
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

        for (int j = 0; j < N; j++)
        {
            cout << "  ";
            switch (board[i][j])
            {
            case -1:
                cout << '.';
                break;

            case 0:
                cout << 'k';

            default:
                if (steps == board[i][j])
                    cout << 'K';
                else
                    cout << board[i][j];
                break;
            }
        }
    }
}

int KnightsPath::getSteps() const
{
    return steps;
}

bool KnightsPath::isValid(int r, int c) const
{
    return false;
}

bool KnightsPath::hasMoreMoves() const
{
    return false;
}

bool KnightsPath::move(int r, int c)
{
    return false;
}