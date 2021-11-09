// name: SZE-TO Kwok Leung
// sID: 1155149068
// email: 1155149068@link.cuhk.edu.hk

#include <iostream>
#include "KnightsPath.h"

using namespace std;

void get_statring_input(int *col, int *row)
{
    char tmp_col;
    int tmp_row;
    cout << "Enter starting position (col row): ";
    cin >> tmp_col >> tmp_row;

    // Check if the input is within range and if it is a valid move
    if (tmp_col - 'A' < 0 || tmp_col - 'A' >= KnightsPath::N ||
        tmp_row < 0 || tmp_row >= KnightsPath::N)
    {
        // Recursively call until received a valid input
        cout << "Invalid. Try again!" << endl;
        get_statring_input(col, row);
    }
    else
    {
        *col = tmp_col - 'A';
        *row = tmp_row;
    }
}

void get_move_input(KnightsPath kp, int *row, int *col)
{
    char tmp_col;
    int tmp_row;
    cout << "Move the knight (col row): ";
    cin >> tmp_col >> tmp_row;

    // Check if the input is within range and if it is a valid move
    if (kp.isValid(tmp_row, tmp_col - 'A'))
    {
        *col = tmp_col - 'A';
        *row = tmp_row;
    }
    else
    {
        // Recursively call until received a valid input
        cout << "Invalid move. Try again!" << endl;
        get_move_input(kp, col, row);
    }
}

int main(void)
{
    int r = 0, c = 0;

    // Starting position
    get_statring_input(&c, &r);
    // Initialize
    KnightsPath kp = KnightsPath(r, c);

    // Game loop
    do
    {
        kp.print();
        get_move_input(kp, &r, &c);
        kp.move(r, c);
    } while (kp.hasMoreMoves());

    // End game message
    kp.print();
    cout << "Finished! No more moves!" << endl;
    if (kp.getSteps() > (KnightsPath::N * KnightsPath::N / 2))
        cout << "Well done!";
    else
        cout << "Still drunk? Walk wiser!";

    return 0;
}
