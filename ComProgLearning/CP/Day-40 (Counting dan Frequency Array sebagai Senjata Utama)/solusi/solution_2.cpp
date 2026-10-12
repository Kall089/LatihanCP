/*
============================================================
✅ Solution 2: Anagram Beruntun
============================================================
Approach: Array 26 huruf, satu sapuan tambah lalu satu sapuan kurang
Complexity: Time O(|s| + |t|) per kasus | Space O(1)
Key Insight: Dua string adalah anagram persis ketika vektor frekuensi
             hurufnya identik. Karena alfabetnya hanya 26, "vektor
             frekuensi" itu cukup 26 int -- konstanta, bukan O(n).

📖 PENJELASAN PENDEKATAN:
1. Kalau panjangnya berbeda, langsung NO. Pemeriksaan ini O(1) dan
   menangkap kasus ketiga pada sampel tanpa kerja apa pun.
2. Hitung huruf s: c[ch]++.
3. Sapu t sambil MENGURANGI: kalau --c[ch] < 0, berarti t memakai huruf
   itu lebih banyak daripada yang tersedia -> bukan anagram.
4. Kalau tidak pernah negatif dan panjangnya sama, pasti anagram.

KENAPA LANGKAH 4 CUKUP TANPA PEMERIKSAAN AKHIR:
   Total penambahan = |s|, total pengurangan = |t|, dan |s| == |t|.
   Kalau tidak ada slot yang menjadi negatif, maka jumlah seluruh slot
   tetap nol, yang berarti setiap slot tepat nol. Tidak ada sisa yang
   perlu diperiksa.

⚠️ MULTI TEST CASE: array 26 elemen dideklarasikan DI DALAM loop supaya
   otomatis bersih setiap kasus. Untuk array sekecil ini biayanya nol.
   Kebiasaan ini menjadi masalah hanya kalau arraynya besar -- lihat
   Solution 6 untuk cara menanganinya.

🔄 ALTERNATIVE APPROACHES:
- Urutkan kedua string lalu bandingkan: O(n log n), lebih lambat tetapi
  lebih pendek dan bekerja untuk alfabet apa pun.
- Hash multiset (jumlah dari fungsi acak per huruf): O(n), berguna kalau
  alfabetnya sangat besar, tetapi probabilistik.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    string out;

    while (T--) {
        string s, t;
        cin >> s >> t;

        if (s.size() != t.size()) {        // pemeriksaan termurah, paling awal
            out += "NO\n";
            continue;
        }

        int c[26] = {0};                   // kecil, aman dibuat ulang tiap kasus
        for (char ch : s) c[ch - 'a']++;

        bool ok = true;
        for (char ch : t)
            if (--c[ch - 'a'] < 0) { ok = false; break; }

        out += ok ? "YES\n" : "NO\n";
    }

    cout << out;
    return 0;
}
