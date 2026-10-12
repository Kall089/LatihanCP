#include <iostream>
#include <algorithm>

using namespace std;

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n))
        return 0;

    long long min_x = 2e18;
    long long max_x = -2e18;

    for (int i = 0; i < n; i++)
    {
        long long x;
        cin >> x;
        min_x = min(min_x, x);
        max_x = max(max_x, x);
    }

    long long ans = (min_x + max_x) / 2;

    cout << ans << "\n";

    return 0;
}