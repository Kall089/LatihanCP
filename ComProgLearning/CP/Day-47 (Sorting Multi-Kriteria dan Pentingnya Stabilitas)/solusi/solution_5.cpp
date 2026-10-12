// Day 16 — Custom Comparator
// File  : solution_5.cpp

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);

    sort(idx.begin(), idx.end(),
        [&A](int i, int j){ return A[i] < A[j]; });

    for (int i = 0; i < n; i++) cout << idx[i] << " \n"[i==n-1];

    return 0;
}
