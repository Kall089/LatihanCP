/*
============================================================
✅ Solution 6: Rentang Seimbang Terpanjang
============================================================
Approach: Trik +1/-1 + map posisi kemunculan PERTAMA
Complexity: Time O(n log n) | Space O(n)
Key Insight: "Sama banyak antara dua jenis" hampir selalu bisa diubah menjadi
             "jumlahnya nol" dengan memberi bobot +1 dan -1. Setelah itu,
             substring seimbang berarti dua prefix yang NILAINYA SAMA, dan
             mencari yang terpanjang berarti memasangkan setiap prefix dengan
             kemunculan PERTAMA nilai yang sama.

📖 PENJELASAN PENDEKATAN:
1. Petakan '1' -> +1 dan '0' -> -1.
2. pre[0] = 0. Substring s[l..r] seimbang <=> pre[r+1] == pre[l].
3. Simpan map dari nilai prefix ke indeks kemunculan PERTAMA.
   Saat bertemu nilai yang sudah ada, panjangnya = i - pertama[nilai].
   JANGAN memperbarui entri yang sudah ada -- memperbaruinya akan membuatmu
   selalu mendapat substring terpendek, bukan terpanjang.
4. Inisialisasi pertama[0] = 0 supaya substring yang dimulai dari indeks 0
   ikut terhitung. Ini analog dengan freq[0] = 1 di Solution 3.

VERIFIKASI SAMPEL 1 (s = "110100"):
   bobot : +1 +1 -1 +1 -1 -1
   pre   : 0  1  2  1  2  1  0
   i=6 -> pre=0, pertama[0]=0 -> panjang 6   <- terpanjang
   Seluruh string memang punya tiga '1' dan tiga '0'.  ✓

CATATAN: nilai prefix berkisar antara -n dan n, jadi kamu juga bisa memakai
array berukuran 2n+1 dengan offset n alih-alih map. Itu O(n) murni dan lebih
cepat; map dipakai di sini karena lebih jelas dibaca.

🔄 ALTERNATIVE APPROACHES:
- Array dengan offset n: O(n), lebih cepat, sedikit lebih rawan off-by-one.
- Naif O(n^2): cukup untuk n <= 5000.
- Kalau yang diminta BANYAKNYA substring seimbang (bukan yang terpanjang),
  ganti "posisi pertama" menjadi "frekuensi" -- persis Solution 3 dengan K = 0.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string s;
    cin >> n >> s;
    n = s.size();

    map<int, int> pertama;
    pertama[0] = 0;                    // prefix kosong ada di posisi 0

    int cur = 0, best = 0;
    for (int i = 0; i < n; i++) {
        cur += (s[i] == '1') ? 1 : -1;

        auto it = pertama.find(cur);
        if (it != pertama.end())
            best = max(best, (i + 1) - it->second);
        else
            pertama[cur] = i + 1;      // catat hanya kemunculan PERTAMA
    }

    cout << best << '\n';
    return 0;
}
