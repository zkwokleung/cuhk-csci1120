#include <iostream>
#include "human.h"
#include "game.h"
#include "board.h"

using namespace std;

Human::Human(string name, Color color) : Player(name, color) {}

void Human::makeMove(Board *board)
{
    while (true)
    {
        cout << this->getName() << "'s turn: ";
        char c1, c2; // columns letters
        int r1, r2;  // row indexes (begin at 1)
        cin >> c1 >> r1 >> c2 >> r2;
        // if input fails, reset cin's state, skip the buffer and try again
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid. Try again!" << endl;
            continue;
        }

        // ad hoc stop condition (surrender)
        if (c1 == 'Z' && c2 == 'Z' && r1 == 0 && r2 == 0)
        {
            board->getGame()->setState(GAME_OVER);
            // set opponent as winner,
            // by flipping the turn
            board->getGame()->setTurn((getColor() == BLUE) ? RED : BLUE);
            return;
        }

        int y1, x1, y2, x2;
        y1 = x1 = y2 = x2 = -1;
        // Convert r1, c1 and r2, c2 into integers y1, x1, y2, x2
        if ((c1 >= 'A' && c1 <= 'Z'))
            x1 = c1 - 'A';
        else if (c1 >= 'a' && c1 <= 'z')
            x1 = c1 - 'a';

        y1 = r1 - 1;

        if ((c2 >= 'A' && c2 <= 'Z'))
            x2 = c2 - 'A';
        else if (c2 >= 'a' && c2 <= 'z')
            x2 = c2 - 'a';

        y2 = r2 - 1;

        bool valid = board->move(y1, x1, y2, x2);
        if (valid)
            break;
        cout << "Invalid. Try again!" << endl;
    }
}
