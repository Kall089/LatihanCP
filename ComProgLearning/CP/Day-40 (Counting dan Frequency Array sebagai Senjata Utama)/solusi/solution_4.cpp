/*
============================================================
✅ Solution 4: Query Rentang Nilai
============================================================
Approach: Array frekuensi diubah menjadi prefix sum atas NILAI
Complexity: Time O(V + n + q) | Space O(V)
Key Insight: Menggabungkan dua alat yang sudah kamu punya. Frekuensi
             memberi "berapa elemen bernilai tepat v"; prefix sum
             mengubahnya menjadi "berapa elemen bernilai <= v". Setelah
             perubahan makna itu, query rentang menjadi satu pengurangan.

📖 PENJELASAN PENDEKATAN:
1. cnt[a[i]]++ untuk semua elemen.
2. cnt[v] += cnt[v-1] untuk v = 1..MAKS.
   Sekarang cnt[v] berarti "berapa elemen yang nilainya <= v".
3. Jawaban untuk [L, R] = cnt[R] - cnt[L-1].

PERHATIKAN PERGESERAN MAKNA di langkah 2. Sebelum diubah, cnt[v] adalah
"tepat v". Sesudahnya, "paling banyak v". Banyak bug terjadi karena
seseorang lupa bahwa array yang sama sekarang punya arti berbeda -- kalau
kamu masih butuh frekuensi mentahnya, simpan salinan sebelum mengubahnya.

⚠️ INDEKS L-1 saat L = 1 memberi cnt[0], yang bernilai 0 karena tidak ada
   elemen bernilai 0 dalam batasan soal. Ini aman di sini, tetapi kalau
   soal mengizinkan nilai 0, kamu perlu penjagaan tersendiri (atau geser
   seluruh nilai satu langkah ke atas).

⚠️ INI BUKAN QUERY RENTANG POSISI. Soal ini menanyakan rentang NILAI.
   Kalau soal menanyakan "berapa elemen di posisi l..r yang nilainya
   antara L dan R", itu masalah yang jauh lebih sulit -- butuh merge sort
   tree atau wavelet tree (Day 179, 194).

🔄 ALTERNATIVE APPROACHES:
- Urutkan array lalu pakai lower_bound/upper_bound per query:
  O(n log n + q log n). Bekerja untuk nilai berapa pun tanpa batas domain,
  jadi ini pilihan yang lebih umum. Untuk domain kecil, versi array lebih cepat.
- Fenwick Tree: berlebihan kecuali ada update.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAKS = 1000005;
int cnt[MAKS];                 // GLOBAL

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    // Ubah makna: cnt[v] menjadi "berapa elemen bernilai <= v"
    for (int v = 1; v < MAKS; v++) cnt[v] += cnt[v - 1];

    string out;
    while (q--) {
        int L, R;
        cin >> L >> R;
        if (R >= MAKS) R = MAKS - 1;
        int jawab = cnt[R] - (L > 0 ? cnt[L - 1] : 0);
        out += to_string(jawab);
        out += '\n';
    }
    cout << out;

    return 0;
}
