// name: SZE-TO Kwok Leung
// sID: 1155149068
// email: 1155149068@link.cuhk.edu.hk

#include <iostream>
#include "KnightsPath.h"

using namespace std;

// Get input without any checking
void get_input(int *row, int *col)
{
    char tmp_col;
    int tmp_row;
    cin >> tmp_col >> tmp_row;
    *col = tmp_col - 'A';
    *row = tmp_row;
}

int main(void)
{
    int r = 0, c = 0;
    bool flag = false; // A continue flag for input reading part.

    // Starting position
    do
    {
        flag = false;

        cout << "Enter starting position (col row): ";
        get_input(&r, &c);
        if (c < 0 || c >= KnightsPath::N ||
            r < 0 || r >= KnightsPath::N)
        {
            cout << "Invalid. Try again!" << endl;
            flag = true;
        }
    } while (flag);

    // Initialize
    KnightsPath kp = KnightsPath(r, c);

    // Game loop
    do
    {
        kp.print();
        do
        {
            flag = false;
            cout << "Move the knight (col row): ";
            get_input(&r, &c);
            if (!kp.move(r, c))
            {
                cout << "Invalid move. Try again!" << endl;
                flag = true;
            }
        } while (flag);
    } while (kp.hasMoreMoves());

    // End game message
    kp.print();
    cout << "Finished! No more moves!" << endl;
    if (kp.getSteps() >= (KnightsPath::N * KnightsPath::N / 2))
        cout << "Well done!";
    else
        cout << "Still drunk? Walk wiser!";

    return 0;
}
