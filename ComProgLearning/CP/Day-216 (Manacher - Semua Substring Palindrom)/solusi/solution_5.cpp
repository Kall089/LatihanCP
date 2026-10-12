/*
============================================================
✅ Solution 5: Derajat Palindrom (CF 7D)
============================================================
Approach: Manacher untuk menandai semua awalan palindromik + DP k[i] = k[i/2] + 1
Complexity: Time O(n) | Space O(n)
Key Insight: Definisi derajat bersifat rekursif dan HANYA bergantung pada
             awalan. Jadi yang kita perlukan bukan seluruh informasi palindrom,
             melainkan satu bit per panjang: "apakah awalan sepanjang i
             merupakan palindrom". Manacher memberi itu dalam satu kali jalan.

📖 PENJELASAN PENDEKATAN:
1. Manacher pada S. Untuk awalan sepanjang i (yaitu l = 0, r = i - 1),
   indeks pusatnya adalah l + r + 1 = i. Jadi:
       awalan sepanjang i palindrom  <=>  p[i] >= i
   Rumus yang sangat rapi — konsekuensi langsung dari transformasi '#'.
2. k[0] = 0. Untuk i = 1..n:
       k[i] = (awalan i palindrom) ? k[i / 2] + 1 : 0
3. Jawabannya jumlah seluruh k[i].

VERIFIKASI "abacaba":
   i=1 "a"       pal -> k = k[0]+1 = 1
   i=2 "ab"      tidak -> 0
   i=3 "aba"     pal -> k = k[1]+1 = 2
   i=4 "abac"    tidak -> 0
   i=5 "abaca"   tidak -> 0
   i=6 "abacab"  tidak -> 0
   i=7 "abacaba" pal -> k = k[3]+1 = 3
   total = 1+2+3 = 6  ✓

⚠️ ALFABET: soal aslinya mengizinkan huruf besar, huruf kecil, dan angka.
   Separator '#' aman untuk itu, tetapi kalau soal mengizinkan karakter ASCII
   apa pun, ganti ke '\1'. Di sini kita pakai '\1' agar aman tanpa berpikir.

⚠️ n bisa 5*10^6, jadi hindari membuat string tambahan lebih dari sekali dan
   pakai I/O cepat. Total array 2n+1 int = 40 MB pada n = 5*10^6 — kalau limit
   memori ketat, pakai versi dua array (d1/d2) yang hanya butuh 2n int.

🔄 ALTERNATIVE APPROACHES:
- Hashing maju/mundur: cek "awalan i palindrom" dalam O(1), total O(n).
  Lebih hemat memori tetapi probabilistik (soal ini punya anti-hash test).
- Z-function pada rev(S) + sep + S: memberi awalan palindromik TERPANJANG saja,
  belum cukup — kita butuh SEMUA panjang.
- Eertree: bisa, tapi berlebihan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> manacher(const string& s, char SEP) {
    string t(1, SEP);
    for (char c : s) { t += c; t += SEP; }
    int n = t.size();
    vector<int> p(n, 0);
    int c = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (i < r) p[i] = min(r - i, p[2 * c - i]);
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n
               && t[i - p[i] - 1] == t[i + p[i] + 1]) p[i]++;
        if (i + p[i] > r) { c = i; r = i + p[i]; }
    }
    return p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();

    vector<int> p = manacher(s, '\1');

    vector<int> k(n + 1, 0);
    ll total = 0;
    for (int i = 1; i <= n; i++) {
        if (p[i] >= i) k[i] = k[i / 2] + 1;   // awalan sepanjang i palindrom
        total += k[i];
    }

    cout << total << '\n';
    return 0;
}
