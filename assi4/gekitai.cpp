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
// Knock back the piecce in direction of (dir_x, dir_y)
void knock_back(char board[][N], int tar_y, int tar_x, int dir_y, int dir_x)
{
    int to_x = tar_x + dir_x, to_y = tar_y + dir_y;
    if (to_x < 0 || to_x >= N || to_y < 0 || to_y >= N)
    {
        // Return the piece
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
#pragma endregion

#pragma region Required functions implementations
bool is_valid_move(char board[][N], char player, int y, int x)
{
    return board[y][x] == '.';
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
    int count_H = 0, count_V = 0, count_DU = 0, count_DD = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // Horizontal
            if (board[i][j] == player)
            {
                count_H++;
                if (count_H >= L)
                    return true;
            }
            else
            {
                count_H = 0;
            }

            // Vertical
            if (board[j][i] == player)
            {
                count_V++;
                if (count_V >= L)
                    return true;
            }
            else
            {
                count_H = 0;
            }
        }
    }

    // Diagonal right
    for (int k = 0; k < N; k++)
    {
        // Break the checking if there is no more than L block to check
        if (N - k < L)
            break;
        for (int i = k, j = 0; i < N && j < N; i++, j++)
        {
            // Upper half of the board
            if (board[j][i] == player)
                count_DU++;
            else
                count_DU = 0;

            if (count_DU >= L)
                return true;

            // Lower half of the board
            if (board[i][j] == player)
                count_DD++;
            else
                count_DD = 0;

            if (count_DD >= L)
                return true;
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
            if (dir_y == 0 && x == 0)
                continue;

            knock_back(board, y + dir_y, x + dir_x, dir_y, dir_x);
        }
    }
}

void print(char board[][N])
{
    // Margin
    cout << "  ";
    // Header
    for (int i = 0; i < N; i++)
        cout << char(i + 'A') << " ";
    cout << endl;

    for (int row = 0; row < N; row++)
    {
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
    char board[N][N];
    // Board initialize
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            board[row][col] = '.';
        }
    }

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
#pragma endregion

    return 0;
}
