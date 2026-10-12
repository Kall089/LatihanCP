/*
============================================================
✅ Solution 6: Kamus Alien (Rekonstruksi Urutan Huruf)
============================================================
Approach: bangun graf dari pasangan kata bersebelahan + Kahn leksikografis
Complexity: Time O(total_panjang + 26^2 log 26) | Space O(26^2)
Key Insight: Dua kata bersebelahan dalam kamus hanya memberi SATU informasi:
             huruf pertama yang berbeda menentukan urutannya. Setelah posisi
             itu, tidak ada yang bisa disimpulkan sama sekali.

📖 TIGA LANGKAH:
   1. Kumpulkan himpunan huruf yang MUNCUL (jawaban harus memuat semuanya).
   2. Untuk tiap pasangan (w[i], w[i+1]): jalan bersamaan sampai beda pertama
      -> edge a -> b, lalu BREAK.
   3. Kahn dengan min-heap supaya leksikografis terkecil (menurut alfabet
      Latin) di antara semua jawaban yang sah.

⚠️ KASUS PREFIKS -- INI YANG PALING SERING TERLEWAT.
   Kalau dua kata identik sampai akhir kata yang lebih pendek, dan kata yang
   LEBIH PANJANG muncul DULUAN ("abcd" lalu "ab"), data mustahil di kamus mana
   pun. Harus langsung dijawab tidak konsisten. Sampel 2 menguji ini.
   Kebalikannya ("ab" lalu "abcd") sah dan TIDAK memberi edge apa pun.

⚠️ BREAK SETELAH EDGE PERTAMA. Menambahkan edge untuk setiap posisi yang
   berbeda adalah kesalahan besar: kamus tidak menjamin apa pun setelah huruf
   pembeda pertama.

⚠️ HURUF YANG TIDAK PUNYA BATASAN TETAP HARUS DICETAK. Sampel 3: hanya ada
   edge x -> y, tetapi 'z' muncul di kedua kata, jadi ia bagian dari alfabet.
   indeg-nya 0 sejak awal, dan min-heap menaruhnya di akhir karena 'x' < 'z'.

⚠️ EDGE GANDA. Kalau pasangan yang sama muncul berkali-kali, indeg akan
   dihitung berlebih. Pakai matriks bool 26x26 untuk menyaring duplikat --
   kalau tidak, indeg tidak pernah mencapai 0 dan jawabannya salah "tidak
   konsisten".

VERIFIKASI SAMPEL 1 (wrt, wrf, er, ett, rftt):
   wrt vs wrf -> beda di posisi 2: t -> f
   wrf vs er  -> beda di posisi 0: w -> e
   er  vs ett -> beda di posisi 1: r -> t
   ett vs rftt-> beda di posisi 0: e -> r
   huruf: w e r t f
   indeg: w0 e1 r1 t1 f1 ; heap {w} -> w, e, r, t, f  ->  "wertf"  ✓

🔄 ALTERNATIVE APPROACHES:
- DFS post-order + reverse: bekerja, tapi menghasilkan urutan sah SEMBARANG,
  bukan yang leksikografis terkecil.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<string> w(n);
    for (auto& s : w) cin >> s;

    vector<char> ada(26, 0);
    for (auto& s : w) for (char c : s) ada[c - 'a'] = 1;

    static bool edge[26][26] = {};
    vector<int> indeg(26, 0);
    bool valid = true;

    for (int i = 0; i + 1 < n && valid; i++) {
        const string &a = w[i], &b = w[i + 1];
        int len = min(a.size(), b.size()), j = 0;
        while (j < len && a[j] == b[j]) j++;
        if (j == len) {
            // identik sampai akhir yang pendek
            if (a.size() > b.size()) valid = false;   // "abcd" lalu "ab" -> mustahil
        } else {
            int x = a[j] - 'a', y = b[j] - 'a';
            if (!edge[x][y]) { edge[x][y] = true; indeg[y]++; }
        }
    }

    if (!valid) { cout << '\n'; return 0; }

    int total = 0;
    for (int c = 0; c < 26; c++) total += ada[c];

    priority_queue<int, vector<int>, greater<int>> q;
    for (int c = 0; c < 26; c++) if (ada[c] && indeg[c] == 0) q.push(c);

    string res;
    while (!q.empty()) {
        int u = q.top(); q.pop();
        res += char('a' + u);
        for (int v = 0; v < 26; v++)
            if (edge[u][v] && --indeg[v] == 0) q.push(v);
    }

    cout << ((int)res.size() == total ? res : string()) << '\n';
    return 0;
}
