#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<tuple<ll, ll, ll>>> adj(n + 1);

    set<ll> a;

    for (int i = 0; i < n; i++)
    {
        ll L, R, W;
        cin >> L >> R >> W;

        a.insert(L);
        a.insert(R);
     }

    sort(adj.begin(), adj.end());

    vector<ll> vec;

    ll hitung = 0;

    for (ll i : a)
    {
        for (int u = 0; u <= n; u++)
        {
            for (auto [l, r, w] : adj[u])
            {
                if (l == i)
                {
                    vec.push_back(u);
                }

                if (r == i && vec.back() == u)
                {
                    hitung = max(hitung + w, w);
                    vec.pop_back();
                }
            }
        }
    }
    cout << hitung;
}