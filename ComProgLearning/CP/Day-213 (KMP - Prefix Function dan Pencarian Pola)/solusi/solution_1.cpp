/*
============================================================
✅ Solution 1: Bangun Tabel Pi
============================================================
Approach: Failure function (prefix function) KMP
Complexity: Time O(n) amortized | Space O(n)
Key Insight:
Nilai pi[i] dibangun dari pi[i-1], bukan dihitung ulang dari nol. Kita mulai
dengan panjang kecocokan sebelumnya, lalu mundur lewat rantai border sampai
menemukan huruf yang cocok.

Walaupun ada while di dalam for, kompleksitasnya tetap O(n). Alasannya:
nilai j naik paling banyak 1 pada tiap iterasi luar (total kenaikan <= n),
sedangkan tiap putaran while menurunkan j minimal 1. Karena j tidak pernah
negatif, total putaran while sepanjang program juga <= n.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    // Bangun tabel pi: pi[i] = panjang awalan terpanjang p[0..i]
    // yang sekaligus menjadi akhirannya (bukan seluruh potongan).
    auto bangunPi = [](const string& p) {
        int m = p.size();
        vector<int> pi(m, 0);
        for (int i = 1; i < m; i++) {
            int j = pi[i - 1];
            while (j > 0 && p[i] != p[j]) j = pi[j - 1];   // mundur ke border lebih pendek
            if (p[i] == p[j]) j++;
            pi[i] = j;
        }
        return pi;
    };

    vector<int> pi = bangunPi(s);
    for (int i = 0; i < (int)pi.size(); i++)
        cout << pi[i] << " \n"[i + 1 == (int)pi.size()];

    return 0;
}
