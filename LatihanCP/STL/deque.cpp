#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < b; i++)

using namespace std;

int main()
{
    deque<int> dq(10);

    rep(i, 0, 10)
    {
        dq[i] = i * i;
    }

    for (auto x : dq)
    {
        cout << x << ", ";
    }
}