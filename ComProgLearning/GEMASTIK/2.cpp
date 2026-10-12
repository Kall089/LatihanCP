#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    int left = 0;
    int right = left;

    while (right < a.size())
    {
        while (right + 1 < a.size() && a[right + 1] - a[right] == 1)
        {
            right++;
        }

        if (left == right)
        {
            cout << a[left];
        }
        else
        {
            cout << a[left] << "-" << a[right];
        }

        if (right + 1 < a.size())
        {
            cout << ",";
        }

        left = right + 1;
        right = left;
    }
}