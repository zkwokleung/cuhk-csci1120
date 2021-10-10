// name: SZE-TO Kwok Leung
// sID: 1155149068
// e-mail: 1155149068@link.cuhk.edu.hk

#include <iostream>
#include <cmath>

using namespace std;

void printHead(int h, int w)
{
    // Margin of wings + tip margin
    for (int i = 0; i < w + h + 1; i++)
        cout << " ";

    // Tip
    cout << "|" << endl;

    // Head
    for (int i = 0; i < h; i++)
    {
        // Wing margin + Head Margin
        for (int j = 0; j < w + h - i; j++)
            cout << " ";

        cout << "/";

        // Head Inner
        for (int j = 0; j < 1 + i * 2; j++)
            cout << "*";

        cout << "\\" << endl;
    }
}

void printBodyAndWing(int h, int b, int w)
{
    // Body Line
    // Wing margin
    for (int i = 0; i < w; i++)
        cout << " ";

    cout << "+";
    for (int i = 0; i < h * 2 + 1; i++)
        cout << "-";
    cout << "+" << endl;

    // Body
    for (int i = 0; i < b; i++)
    {
        if (i + 1 > b / 2)
        {
            for (int j = 0; j < w; j++)
            {
                cout << "/";
            }
        }
        else
        {
            // Wing margin
            for (int j = 0; j < w; j++)
                cout << " ";
        }

        // Frame
        cout << "|";

        // Inner
        for (int j = 0; j < h * 2 + 1; j++)
        {
            cout << ".";
        }

        // Frame
        cout << "|";

        // Wing
        if (i + 1 > b / 2)
        {
            for (int j = 0; j < w; j++)
            {
                cout << "\\";
            }
        }
        cout << endl;
    }

    // Body Line
    // Wing margin
    for (int j = 0; j < w; j++)
        cout << " ";

    cout << "+";
    for (int i = 0; i < h * 2 + 1; i++)
        cout << "-";
    cout << "+" << endl;
}

void printTail(int h, int w, int t)
{
    // Top triangle
    for (int i = t / 2; i < t; i++)
    {
        // Wing Margin + frame margin + center margin + triangle margin
        for (int j = 0; j < w + 1 + h - i; j++)
        {
            cout << " ";
        }

        // Stars
        for (int j = 0; j < 1 + 2 * i; j++)
        {
            cout << "*";
        }
        cout << endl;
    }

    // Bottom Triangle
    for (int i = t - 1; i >= 0; i--)
    {
        // Wing Margin + frame margin + triangle margin
        for (int j = 0; j < w + 1 + h - i; j++)
        {
            cout << " ";
        }

        // Stars
        for (int j = 0; j < 1 + 2 * i; j++)
        {
            cout << "*";
        }
        cout << endl;
    }
}

int main()
{
    int h, b, w, t;

    do
    {
        cout << "Enter h, b, w, t: ";
        cin >> h >> b >> w >> t;
    } while (h < 1 || b < 2 || w < 1 || t < 2 || 2 * t - 1 > 2 * h + 3);

    printHead(h, w);
    printBodyAndWing(h, b, w);
    printTail(h, w, t);

    return 0;
}
