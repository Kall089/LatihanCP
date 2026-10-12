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

    pair<long long, int> max_val(a[0], 0);
    pair<long long, int> min_val(a[0], 0);

    if ((n == 2 && (a[0] + a[1]) % 2 != 0))
    {
        cout << "TIDAK SESUAI";
        return 0;
    }

    if (n == 1)
    {
        cout << "SESUAI";
        return 0;
    }
    else if (n == 2 && (a[0] + a[1]) % 2 == 0)
    {

        if (a[0] > a[1])
        {
            max_val.first = a[0];
            max_val.second = 0;
        }
        else
        {
            max_val.first = a[1];
            max_val.second = 1;
        }

        if (a[0] < a[1])
        {
            min_val.first = a[0];
            min_val.second = 0;
        }
        else
        {
            min_val.first = a[1];
            min_val.second = 1;
        }

        int hitung2 = max_val.first - min_val.first;
        hitung2 /= 2;

        if (hitung2 == 0)
        {
            cout << "SESUAI";
            return 0;
        }

        cout << hitung2 << " " << max_val.second + 1 << " " << min_val.second + 1;
        return 0;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (max_val.first < a[i])
            {
                max_val.first = a[i];
                max_val.second = i;
            }

            if (min_val.first > a[i])
            {
                min_val.first = a[i];
                min_val.second = i;
            }
        }
    }

    if (max_val.first == min_val.first)
    {
        cout << "SESUAI\n";
        return 0;
    }

    vector<long long> x = a;
    sort(x.rbegin(), x.rend());

    int f = x[0] - x[1];

    int hitung = max_val.first - min_val.first;

    int selisih = hitung - f;

    a[max_val.second] -= selisih;
    a[min_val.second] += selisih;

    for (int i = 1; i < n; i++)
    {
        if (a[i - 1] != a[i])
        {
            cout << "TIDAK SESUAI";
            return 0;
        }
    }
    cout << selisih << " " << max_val.second + 1 << " " << min_val.second + 1;
}