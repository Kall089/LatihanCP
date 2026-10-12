#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] == 1)
        {
            count++;
        }
    }

    vector<int> dp(n);

    for (int i = 0; i < n; i++)
    {
        if (a[i] == 0)
        {
            a[i] = 1;
        }
        else
        {
            a[i] = -1;
        }
    }

    int best = a[0];
    int curr = a[0];

    for (int i = 1; i < n; i++)
    {
        curr = max(a[i], a[i] + curr);
        best = max(curr, best);
    }

    cout << best + count;
}