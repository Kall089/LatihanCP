/*
============================================================
✅ Solution 4: Periode Terkecil
============================================================
Approach: Menurunkan periode dari border terpanjang
Complexity: Time O(n) | Space O(n)
Key Insight:
Kenapa periode = n - pi[n-1]? Border terpanjang berarti pi[n-1] huruf pertama
sama persis dengan pi[n-1] huruf terakhir. Kalau kita menggeser string ke
kanan sejauh (n - pi[n-1]), bagian yang bertindihan akan cocok sempurna.
Pergeseran terkecil yang membuat string cocok dengan dirinya sendiri itulah
definisi periode.

Perlu dibedakan dua hal:
  - PERIODE: pergeseran terkecil yang konsisten (pengulangan boleh terpotong)
  - PENGULANGAN UTUH: n habis dibagi periode

"aabaa" punya periode 3 yang sah, tetapi bukan pengulangan utuh karena
5 % 3 != 0.

Jebakan yang mudah terlewat: string tanpa border seperti "abcd" berperiode 4
(sama dengan panjangnya), dan 4 % 4 == 0. Tanpa syarat periode < n, kode akan
salah menjawab "YA". Karena itu syaratnya harus dua-duanya.
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

    int n = s.size();
    vector<int> pi = bangunPi(s);

    // Border terpanjang adalah bagian yang tumpang tindih antara awal & akhir.
    // Sisanya, n - border, adalah panjang satu putaran.
    int periode = n - pi.back();
    // Syaratnya DUA: potongannya harus lebih pendek dari string aslinya
    // (kalau periode == n, string cuma "mengulang dirinya sendiri" satu kali),
    // DAN panjangnya harus habis dibagi periode.
    bool utuh = (periode < n && n % periode == 0);

    cout << periode << " " << (utuh ? "YA" : "TIDAK") << "\n";

    return 0;
}
