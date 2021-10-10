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
    return grid / (long long)pow(10, pos - 1) % 10;
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
    long long dom = p * pow(10, pos - 1);

    if (p == 1)
    {
        // put below
        dom += p * pow(10, pos + 3);
    }
    else
    {
        // put right
        dom += p * pow(10, pos);
    }
    grid += dom;
}

int main()
{
    long long grid = 0;

#pragma region Test
    grid = 0;
    // cout << gridState(grid, 12); // 5
    putToGrid(grid, 1, 1);
    putToGrid(grid, 15, 2);
    printGrid(grid);
#pragma endregion

    return 0;
}