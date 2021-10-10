#include <iostream>

using namespace std;

// Function prototypes
int gridState(long long grid, int pos);
void printGrid(long long grid);
bool isPlaceable(long long grid, int pos, int p);
void putToGrid(long long& grid, int pos, int p);

// Function implementation
int gridState(long long grid, int pos)
{
    return grid / (long long) pow(10, pos - 1) % 10;
}

void printGrid(long long grid) {
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j <= 4; j++) {
            switch (gridState(grid, 4* i + j))
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

int main()
{
    long long grid = 0;

#pragma region Test
    grid = 1120201102010201;
   // cout << gridState(grid, 12); // 5
    printGrid(grid);
#pragma endregion

    return 0;
}