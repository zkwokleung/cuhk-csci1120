#include <iostream>

using namespace std;

// Generic Functions
long long pow(int x, int n)
{
    long long res = 1;
    for (int i = 0; i < n; i++)
        res *= x;

    return res;
}

// Function prototypes
int gridState(long long grid, int pos);
void printGrid(long long grid);
bool isPlaceable(long long grid, int pos, int p);
void putToGrid(long long &grid, int pos, int p);

// Function implementation
int gridState(long long grid, int pos)
{
    return grid / (long long)pow(10, 16 - pos) % 10;
}

void printGrid(long long grid)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            switch (gridState(grid, 4 * i + j))
            {
            case 0:
                cout << ".";
                break;
            case 1:
                cout << "A";
                break;
            case 2:
                cout << "B";
                break;
            default:
                cout << "E";
                break;
            }
            if (j != 4)
                cout << " ";
        }
        cout << endl;
    }
}

bool isPlaceable(long long grid, int pos, int p)
{
    // invalid position
    if (pos < 1 || pos > 16)
        return false;

    // position is not 0
    if (gridState(grid, pos) != 0)
        return false;

    // invalid player
    if (p != 1 && p != 2)
        return false;

    if (p == 1)
    {
        // check vertical
        // if is last row
        if (pos > 12)
            return false;

        // check the block below
        if (gridState(grid, pos + 4) != 0)
            return false;
    }
    else
    {
        // check horizontal
        // if is last col
        if (pos % 4 == 0)
            return false;

        // check the block to the right
        if (gridState(grid, pos + 1) != 0)
            return false;
    }

    // pass all checking
    return true;
}

void putToGrid(long long &grid, int pos, int p)
{
    // This function assume all input is valid
    grid += p * pow(10, 16 - pos);

    if (p == 1)
    {
        // put below
        grid += p * pow(10, 16 - pos - 4);
    }
    else
    {
        // put right
        grid += p * pow(10, 16 - pos - 1);
    }
}

int main(int argc, char const *argv[])
{
    long long grid = 0;
    putToGrid(grid, 1, 1);
    putToGrid(grid, 2, 2);
    printGrid(grid);

    cout << "gridState(grid, 1) " << gridState(grid, 1) << endl;
    cout << "isPlaceable(grid, 1, 1) " << isPlaceable(grid, 1, 1) << endl;
    cout << "isPlaceable(grid, 4, 1) " << isPlaceable(grid, 4, 1) << endl;
    cout << "isPlaceable(grid, 4, 2) " << isPlaceable(grid, 4, 2) << endl;
    cout << "isPlaceable(grid, 16, 1) " << isPlaceable(grid, 16, 1) << endl;
    cout << "isPlaceable(grid, 16,2) " << isPlaceable(grid, 16, 2) << endl;

    cout << "grid " << grid << endl;

    cout << "gridState()";
    for (int i = 1; i <= 16; i++)
    {
        cout << gridState(grid, i);
    }
    cout << endl;

    return 0;
}
