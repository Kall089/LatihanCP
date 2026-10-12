/*
============================================================
✅ Solution 6: Palindrom Terpanjang
============================================================
Approach: Expand around center (2N-1 pusat)
Complexity: Time O(N^2) | Space O(1)
Key Insight:
Alih-alih memeriksa semua O(N^2) substring lalu mengecek satu per satu
(total O(N^3)), kita berangkat dari PUSATnya. Setiap palindrom pasti
tumbuh simetris dari sebuah pusat, sehingga cukup mencoba 2N-1 pusat
dan melebarkan selama huruf kiri dan kanan masih sama.

Dua jenis pusat wajib dicoba: (i, i) untuk palindrom berpanjang ganjil
dan (i, i+1) untuk yang berpanjang genap. Melupakan yang genap adalah
kesalahan paling sering pada soal ini.
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

    int n = s.size();
    int mulaiTerbaik = 0, panjangTerbaik = 1;

    auto lebarkan = [&](int kiri, int kanan) {
        while (kiri >= 0 && kanan < n && s[kiri] == s[kanan]) { kiri--; kanan++; }
        // setelah loop berhenti, palindromnya adalah [kiri+1 .. kanan-1]
        int panjang = kanan - kiri - 1;
        if (panjang > panjangTerbaik) {      // ">" -> yang paling kiri menang saat seri
            panjangTerbaik = panjang;
            mulaiTerbaik = kiri + 1;
        }
    };

    for (int i = 0; i < n; i++) {
        lebarkan(i, i);        // pusat satu huruf  -> panjang ganjil
        lebarkan(i, i + 1);    // pusat dua huruf   -> panjang genap
    }

    cout << s.substr(mulaiTerbaik, panjangTerbaik) << "\n";

    return 0;
}
