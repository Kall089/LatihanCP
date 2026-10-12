#include <iostream>

using namespace std;

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, m;
    if (!(cin >> n >> m))
        return 0;

    if ((2 * m) % n != 0)
    {
        cout << "TIDAK\n";
        return 0;
    }

    long long K = (2 * m) / n;
    long long a, d;

    if (K % 2 == 0)
    {
        d = 0;
        a = K / 2;
    }

    else
    {

        if ((n - 1) % 2 != 0)
        {
            d = 1;
            a = (K - (n - 1)) / 2;
        }
        else
        {
            cout << "TIDAK\n";
            return 0;
        }
    }

    cout << "YA\n";
    for (int i = 0; i < n; i++)
    {
        long long val = a + i * d;
        cout << val << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}