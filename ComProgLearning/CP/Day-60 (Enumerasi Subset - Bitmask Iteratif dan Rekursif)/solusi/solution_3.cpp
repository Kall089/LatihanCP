/*
============================================================
  Solution 3: Print Semua Subset dari n Elemen
============================================================
Pendekatan: Loop mask dari 0 sampai (1<<n)-1.
Untuk setiap mask, decode elemen-elemennya dengan mengecek tiap bit.

Kompleksitas: O(n × 2^n)
*/

#include <bits/stdc++.h>
using namespace std;

string toBinary(int mask, int n) {
    string s = "";
    for (int i = n - 1; i >= 0; i--) {
        s += ((mask >> i) & 1) ? '1' : '0';
    }
    return s;
}

void printSubset(int mask, int n, vector<int>& a) {
    cout << toBinary(mask, n) << " : { ";
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) cout << a[i] << " ";
    }
    cout << "}\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int total = 1 << n;

    if (n <= 4) {
        for (int mask = 0; mask < total; mask++) {
            printSubset(mask, n, a);
        }
    } else {
        for (int mask = 0; mask < 5; mask++) {
            printSubset(mask, n, a);
        }
        cout << "...\n";
        for (int mask = total - 5; mask < total; mask++) {
            printSubset(mask, n, a);
        }
    }

    cout << "Total subset: " << total << "\n";
    return 0;
}
