/*
============================================================
✅ Solution 2: Cari Semua Posisi Pola
============================================================
Approach: KMP pattern matching
Complexity: Time O(n + m) | Space O(m)
Key Insight:
Perbedaan mendasar dengan pencarian naif: indeks teks i tidak pernah mundur.
Saat terjadi ketidakcocokan, kita tidak membuang seluruh kecocokan yang sudah
didapat, melainkan menyusutkannya ke border terpanjang lewat j = pi[j-1].

Baris j = pi[j-1] setelah pola ditemukan sering dilupakan. Kalau diganti
j = 0, kemunculan yang tumpang tindih akan hilang: mencari "aa" di "aaaa"
akan menjawab 2, padahal seharusnya 3.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string t, p;
    if (!(cin >> t >> p)) return 0;

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

    int n = t.size(), m = p.size();
    vector<int> pi = bangunPi(p), hasil;

    int j = 0;
    for (int i = 0; i < n; i++) {          // i tidak pernah mundur
        while (j > 0 && t[i] != p[j]) j = pi[j - 1];
        if (t[i] == p[j]) j++;
        if (j == m) {
            hasil.push_back(i - m + 2);    // 1-based
            j = pi[j - 1];                 // BUKAN 0, agar overlap terhitung
        }
    }

    if (hasil.empty()) { cout << -1 << "\n"; return 0; }
    for (int i = 0; i < (int)hasil.size(); i++)
        cout << hasil[i] << " \n"[i + 1 == (int)hasil.size()];

    return 0;
}
