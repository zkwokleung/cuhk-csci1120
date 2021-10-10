// name: SZE-TO Kwok Leung
// student id: 1155149068
// email: 1155149068@link.cuhk.edu.hk

#include <iostream>
using namespace std;

int main()
{
    int dens[6], money, price, pendingChange, changes[6];

    // Denominations
    cout << "Enter six decreasing denominations: ";
    for (int i = 0; i < 6; i++)
    {
        cin >> dens[i];
    }

    // money
    cout << "Insert money ($): ";
    cin >> money;

    // price
    cout << "Item price ($): ";
    cin >> price;

    // Change
    pendingChange = money - price;
    cout << "Change is $" << pendingChange << endl;

    // Combination
    for (int i = 0; i < 6; i++)
    {
        changes[i] = pendingChange / dens[i];
        pendingChange %= dens[i];
    }

    if (pendingChange != 0)
    {
        // If the changes is not 0 at the end, assume there is no combination for the change
        cout << "Cannot find combination!" << endl;
    }
    else
    {
        // Display the combination
        for (int i = 0; i < 6; i++)
        {
            cout << "$" << dens[i] << " x " << changes[i] << endl;
        }
    }

    return 0;
}