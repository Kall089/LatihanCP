/*
============================================================
✅ Solution 1: Bangun Z-Array
============================================================
Approach: Z-box (interval kecocokan paling kanan)
Complexity: Time O(n) | Space O(n)
Key Insight: Simpan SATU interval [l, r) yang paling jauh menjangkau kanan
             dan sudah terbukti identik dengan awalan S. Setiap i di dalam
             interval itu punya kembaran di i - l yang jawabannya sudah
             dihitung, sehingga bisa disalin alih-alih dibandingkan ulang.

📖 PENJELASAN PENDEKATAN:
1. l = r = 0. Interval kosong.
2. Untuk tiap i:
   a. Jika i < r, kita sudah punya BUKTI bahwa S[i..r-1] == S[i-l..r-l-1].
      Jadi z[i] minimal min(r - i, z[i - l]).
      Batas r - i wajib: di luar z-box kita tidak punya bukti apa pun.
   b. Perluas dengan perbandingan manual.
   c. Kalau jangkauan baru melewati r, jadikan itu z-box baru.

MENGAPA O(n): setiap iterasi while yang BERHASIL menaikkan i + z[i] melewati r,
yang berarti r bertambah minimal 1. r monoton naik dan terbatas n, jadi total
iterasi while sepanjang seluruh algoritma <= n. Perbandingan yang GAGAL terjadi
paling banyak sekali per i. Total O(n) + O(n).

⚠️ KONVENSI: r di sini EKSKLUSIF (s[l..r-1] yang cocok), sehingga batasnya
min(r - i, ...). Versi inklusif memakai min(r - i + 1, ...). Jangan dicampur.

🔄 ALTERNATIVE APPROACHES:
- Naif: O(n^2), TLE pada "aaaa...a".
- Hashing + binary search per i: O(n log n) dan probabilistik. Kalah telak.
- Suffix array + LCP: O(n log n), jauh lebih berat untuk masalah ini.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> bangunZ(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    vector<int> z = bangunZ(s);

    string out;
    for (size_t i = 0; i < z.size(); i++) {
        out += to_string(z[i]);
        out += (i + 1 == z.size()) ? '\n' : ' ';
    }
    cout << out;

    return 0;
}
