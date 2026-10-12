#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < t * 2 - 1; j++)
        {
            if (j >= (t - 1 - i) && j <= (t - 1 + i))
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }

    cout << endl;

    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < t * 2 - 1; j++)
        {
            if (j >= (i) && j <= (t - i + 1))
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}