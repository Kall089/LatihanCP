#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int r = n % 4;
        if (r == 0)
            cout << 0 << '\n';
        else if (r == 1)
            cout << 1 << '\n';
        else if (r == 2)
            cout << 2 << '\n';
        else
            cout << 1 << '\n';
    }
}
