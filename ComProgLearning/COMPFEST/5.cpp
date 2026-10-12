#include <bits/stdc++.h>
using namespace std;

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<long long> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int left = 0, right = n - 1;

    int max_index = 0;
    int jumlah = 0;
    int hasil = 0;

    while (left <= right)
    {
        if (a[left] < a[right] && a[right - 1] <)
        {
            jumlah = a[left];
            max_index = left;
        }
        else
        {
            max_index = right;
        }
    }
}