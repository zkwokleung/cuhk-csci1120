// name: SZE-TO Kwok Leung
// sid: 1155149068
// email: 1155149068@link.cuhk.edu.hk

#include <iostream>

using namespace std;

#pragma region Constants
const int N = 6; // board size
const int P = 8; // number of pieces per player
const int L = 3; // numberof pieces required to form a line
#pragma endregion

#pragma region Function Prototypes
bool is_valid_move(char board[][N], char player, int y, int x);
int pieces_on_board(char board[][N], char player);
bool pieces_in_line(char board[][N], char player);
void move(char board[][N], char player, int y, int x);
void print(char board[][N]);
#pragma endregion

#pragma region My functions implementation
// Read input from user and store them inside x, y
void get_input(char board[][N], char player, int *y, int *x)
{
    char ipt_x;
    int ipt_y;
    cout << "Player " << player << "'s turn: ";
    cin >> ipt_x >> ipt_y;
    *x = (ipt_x >= 'a') ? ipt_x - 'a' : ipt_x - 'A';
    *y = ipt_y - 1;

    // cout << "DEBUG: tmp_x= " << tmp_x << ", tmp_y = " << tmp_y << endl;
    // cout << "DEBUG: x= " << *x << ", y = " << *y << endl;

    // Check input validity
    if (!is_valid_move(board, player, *y, *x))
    {
        cout << "Invalid move!" << endl;
        // Recursively call until the input is valid
        get_input(board, player, y, x);
    }
}

// Knock back the piecce in direction of (dir_x, dir_y)
void knock_back(char board[][N], int tar_y, int tar_x, int dir_y, int dir_x)
{
    int to_x = tar_x + dir_x, to_y = tar_y + dir_y;
    // cout << "DEBUG: tar: (" << tar_x << ", " << tar_y << "); dir: (" << dir_x << ", " << dir_y << "); to: (" << to_x << ", " << to_y << ")" << endl;
    if (to_x < 0 || to_x >= N || to_y < 0 || to_y >= N)
    {
        // Return the piece
        if (tar_y >= 0 && tar_x >= 0 && tar_y < N && tar_x < N && board[tar_y][tar_x] != '.')
            board[tar_y][tar_x] = '.';
    }
    else
    {
        // Check if there is anything blocking
        if (board[to_y][to_x] == '.')
        {
            // Knock back the piece to (to_x, to_y)
            board[to_y][to_x] = board[tar_y][tar_x];
            board[tar_y][tar_x] = '.';
        }
        else
        {
            // Do nothing
        }
    }
}

// Return the winner. Will return 0 if no winner, and return D if draw
char get_winner(char board[][N])
{
    bool X = pieces_on_board(board, 'X') == P || pieces_in_line(board, 'X');
    bool O = pieces_on_board(board, 'O') == P || pieces_in_line(board, 'O');

    if (X && O)
        return 'D';

    if (X)
        return 'X';

    if (O)
        return 'O';

    return 0;
}
#pragma endregion

#pragma region Required functions implementations
bool is_valid_move(char board[][N], char player, int y, int x)
{
    return y >= 0 && x >= 0 && y < N && x < N && board[y][x] == '.';
}

int pieces_on_board(char board[][N], char player)
{
    int count = 0;
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            if (board[row][col] == player)
                count++;

    return count;
}

bool pieces_in_line(char board[][N], char player)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // Horizontal
            if (j + 2 < N && board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player)
                return true;

            // Vertical
            if (i + 2 < N && board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player)
                return true;

            if (i - 1 >= 0 && j - 1 >= 0 && i + 1 < N && j + 1 < N)
            {
                // Diagonal right
                if (board[i - 1][j - 1] == player && board[i][j] == player && board[i + 1][j + 1] == player)
                    return true;

                // Diagonal left
                if (board[i - 1][j + 1] == player && board[i][j] == player && board[i + 1][j - 1] == player)
                    return true;
            }
        }
    }

    return false;
}

void move(char board[][N], char player, int y, int x)
{
    if (!is_valid_move(board, player, y, x))
        return;

    // Place
    board[y][x] = player;

    // Knock back in eight different direction
    for (int dir_y = -1; dir_y <= 1; dir_y++)
    {
        for (int dir_x = -1; dir_x <= 1; dir_x++)
        {
            if (dir_y == 0 && dir_x == 0)
                continue;

            knock_back(board, y + dir_y, x + dir_x, dir_y, dir_x);
        }
    }
}

void print(char board[][N])
{
    // Margin
    cout << "   ";
    // Header
    for (int i = 0; i < N; i++)
    {
        cout << char(i + 'A');
        if (i < N - 1)
            cout << ' ';
    }
    cout << endl;

    for (int row = 0; row < N; row++)
    {
        // Margin for 2 digit rows
        if (row + 1 < 10)
            cout << ' ';

        cout << row + 1 << ' ';
        for (int col = 0; col < N; col++)
        {
            cout << board[row][col] << ' ';
        }
        cout << endl;
    }
}
#pragma endregion

int main(void)
{
    char board[N][N], currentPlayer = 'X', winner = 0;
    int round = 0, ipt_x, ipt_y;

    // Board initialize
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            board[row][col] = '.';

    // Game Loop
    while (!winner)
    {
        cout << "Round " << ++round << ":" << endl;
        print(board);
        get_input(board, currentPlayer, &ipt_y, &ipt_x);
        move(board, currentPlayer, ipt_y, ipt_x);
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

        winner = get_winner(board);
    }

    // End game message
    cout << "Game over:" << endl;
    print(board);
    if (winner == 'D')
        cout << "Draw game!" << endl;
    else
        cout << "Player " << winner << " wins!" << endl;

#pragma region Test
        // for (int k = 0; k < N; k++)
        // {
        //     // Break the checking if there is no more than L block to check
        //     if (N - k < L)
        //         break;
        //     for (int i = k, j = 0; i < N && j < N; i++, j++)
        //     {
        //         if (N - k < L)
        //             break;
        //         board[j][i] = char(k + '0');
        //         print(board);
        //     }
        //     cout << endl;
        // }
        // cout << "=============" << endl;
        // for (int k = 0; k < N; k++)
        // {
        //     // Break the checking if there is no more than L block to check
        //     if (N - k < L)
        //         break;
        //     for (int i = k, j = 0; i < N && j < N; i++, j++)
        //     {
        //         board[i][j] = char(k + '0');
        //         print(board);
        //     }
        //     cout << endl;
        // }

        // Diagonal right
        // for (int k = 0; k < N; k++)
        // {
        //     // Break the checking if there is no more than L block to check
        //     if (N - k < L)
        //         break;
        //     for (int i = k, j = 0; i < N && j < N; i++, j++)
        //     {
        //         board[i][j] = k + '0';
        //     }
        // }
        // print(board);

        // Diagonal left
        // for (int k = N - 1; k >= 0; k--)
        // {
        //     // Break the checking if there is no more than L block to check
        //     if (k + 1 < L)
        //         break;
        //     for (int i = k, j = 0; i >= 0 && j < N; i--, j++)
        //     {
        //         board[i][j] = k + '0';
        //     }
        // }
        // print(board);

        // move(board, 'O', 0, 0);
        // print(board);
        // move(board, 'O', 2, 2);
        // print(board);
        // move(board, 'X', 1, 1);
        // print(board);
        // move(board, 'X', 1, 3);
        // print(board);
        // move(board, 'X', 4, 4);
        // print(board);
        // move(board, 'X', 3, 1);
        // print(board);

        // board[3 - 1][3 + 1] = 'X';
        // board[3][3] = 'X';
        // board[3 + 1][3 - 1] = 'X';

        // board[5][5] = 'X';
        // board[4][4] = 'X';
        // board[3][3] = 'X';
        // print(board);
        // cout << pieces_in_line(board, 'X') << endl;
#pragma endregion

    return 0;
}
