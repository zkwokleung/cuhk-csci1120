// name: SZE-TO Kwok Leung
// email: 1155149068@link.cuhk.edu.hk
// student ID: 1155149068

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

#pragma region Required Functions
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
    grid += p * pow(10, pos - 1);

    if (p == 1)
    {
        // put below
        grid += p * pow(10, pos + 3);
    }
    else
    {
        // put right
        grid += p * pow(10, pos);
    }
}
#pragma endregion

// Check if there is not more move for player p
bool isGameOver(long long grid, int p)
{
    for (int i = 1; i <= 16; i++)
    {
        // If there is a placeable block for the player, the game is not over
        if (gridState(grid, i) == 0 && isPlaceable(grid, i, p))
            return false;
    }

    // Not more placeable block for the player, game over
    return true;
}

int getInputFromPlayer(long long grid, int p)
{
    int ipt;
    cout << "Player " << p << "'s move: ";
    cin >> ipt;

    // Validate input
    if (!isPlaceable(grid, ipt, p))
    {
        cout << "Invalid! Try again." << endl;

        // Invalid, recursively call until received a valid input
        return getInputFromPlayer(grid, p);
    }

    // Valid input
    return ipt;
}

int main()
{
    // Game Variables
    long long grid = 0;
    int currentPlayer = 1, ipt;

    // Game Loop
    while (!isGameOver(grid, currentPlayer))
    {
        printGrid(grid);
        ipt = getInputFromPlayer(grid, currentPlayer);
        putToGrid(grid, ipt, currentPlayer);
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    // After game over
    printGrid(grid);
    cout << "Player " << ((currentPlayer == 1) ? 2 : 1) << " wins!";

    // #pragma region Test
    //     grid = 0;
    //     // cout << gridState(grid, 12); // 5
    //     putToGrid(grid, 1, 1);
    //     putToGrid(grid, 15, 2);
    //     printGrid(grid);
    // #pragma endregion

    return 0;
}