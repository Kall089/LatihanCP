#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < b; i++)
#define ll long long
#define vll vector<long long>

using namespace std;

vll prefixSum(vll &arr)
{
    int n = arr.size();

    vll prefix(n + 1, 0);

    rep(i, 0, n)
    {
        prefix[i + 1] = prefix[i] + arr[i];
    }

    return prefix;
}

int rangeSum(vll prefix, int l, int r)
{
    return prefix[r + 1] - prefix[l];
}

void solve()
{
    int n;
    cin >> n;
    vll arr(n);

    rep(i, 0, n)
    {
        cin >> arr[i];
    }

    int l, r;
    cin >> l >> r;
    vll prefix = prefixSum(arr);

    cout << rangeSum(prefix, l, r);
}

int main()
{
    solve();
}