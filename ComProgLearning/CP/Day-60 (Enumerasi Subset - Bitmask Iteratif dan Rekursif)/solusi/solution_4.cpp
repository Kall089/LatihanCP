/*
============================================================
  Solution 4: Subset Sum
============================================================
Pendekatan: Enumerate semua 2^n subset (kecuali empty).
Untuk tiap subset, hitung sum elemen-elemennya.
Simpan semua mask yang memenuhi sum == K.

Kompleksitas: O(n × 2^n)
Alternatif lebih cepat: DP subset sum dalam O(n × K) jika K tidak terlalu besar.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long K;
    cin >> n >> K;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> answers;

    for (int mask = 1; mask < (1 << n); mask++) {
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) sum += a[i];
        }
        if (sum == K) answers.push_back(mask);
    }

    if (answers.empty()) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int mask : answers) {
            cout << "{ ";
            for (int i = 0; i < n; i++) {
                if ((mask >> i) & 1) cout << a[i] << " ";
            }
            cout << "}\n";
        }
    }

    return 0;
}
