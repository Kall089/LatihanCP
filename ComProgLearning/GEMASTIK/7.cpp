#include <bits/stdc++.h>
using namespace std;

int main()
{
    double L, W, A;
    cin >> L >> W >> A;

    while (L * W > A)
    {
        W /= 2;
        if (L * W == A)
        {
            cout << "YA";

            return 0;
        }
        L /= 2;
        if (L * W == A)
        {
            cout << "YA";
            return 0;
        }
    }

    cout << "TIDAK";
}
