#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> hitung(m + 1, 0);
    int max_val = 0;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;

        for (int j = 0; j < x; j++)
        {
            int y;
            cin >> y;
            hitung[y]++;
        }
    }

    for (int i = 1; i <= m; i++)
    {
        max_val = max(max_val, hitung[i]);
    }

    int hasil = 0;

    for (int i = 1; i <= m; i++)
    {
        if (hitung[i] == max_val)
        {
            hasil++;
        }
    }

    cout << hasil;
}