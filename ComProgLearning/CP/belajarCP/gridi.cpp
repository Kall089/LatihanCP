#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<pair<int, int>> arr(n);

    for (int i = 0; i < n; i++)
    {
        int s, e;
        cin >> s >> e;

        arr[i] = {e, s};
    }

    sort(arr.begin(), arr.end());

    int waktu = 0, jumlah = 0;

    for (auto [e, s] : arr)
    {
        if (s >= waktu)
        {
            waktu = e;
            jumlah++;
        }
    }

    cout << jumlah;
}