/*
============================================================
✅ Solution 2: Menyunting Nama Arsip (Edit Distance O(min(N, M)) Space)
============================================================
Approach: 2-Row Rolling Array DP with Dimension Swapping
Complexity: Time O(|A| * |B|) | Space O(min(|A|, |B|))
Key Insight:
1. Menangani Tanda '-' sebagai String Kosong:
   Jika input berupa "-", ubah menjadi string kosong `""`.

2. Optimasi Dimensi Kolom:
   Biaya edit distance simetris terhadap urutan string: dist(A, B) = dist(B, A).
   Oleh karena itu, jika |B| > |A|, kita cukup menukar `swap(a, b)`.
   Dengan demikian, baris array DP berukuran M + 1 di mana M = min(|A|, |B|) <= 4000.
   Memori yang dibutuhkan: 2 * 4001 * 4 byte ~ 32 KB (sangat hemat di dalam 64 MB).

3. Pola 2 Baris Bergantian (prev dan cur):
   - prev[j] menyimpan jarak edit dari baris i - 1.
   - cur[j] menyimpan jarak edit dari baris i yang sedang dihitung.
   - Basis i = 0: prev[j] = j untuk j = 0..M.
   - Untuk baris i:
     cur[0] = i;
     cur[j] = min({
         prev[j] + 1,                     // Penghapusan karakter dari A
         cur[j - 1] + 1,                  // Penyisipan karakter ke A
         prev[j - 1] + (a[i-1] != b[j-1]) // Karakter sama atau diganti
     });
   - Setelah selesai satu baris: `prev.swap(cur)`.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    if (!(cin >> a >> b)) return 0;

    if (a == "-") a = "";
    if (b == "-") b = "";

    // Pastikan string b adalah yang lebih pendek agar memori minimal
    if (b.size() > a.size()) {
        swap(a, b);
    }

    int n = a.size();
    int m = b.size();

    // prev[j]: baris sebelumnya (i - 1)
    // cur[j]:  baris saat ini (i)
    vector<int> prev(m + 1);
    vector<int> cur(m + 1);

    // Inisialisasi basis i = 0: mengubah string kosong menjadi b[0..j-1] butuh j penyisipan
    for (int j = 0; j <= m; j++) {
        prev[j] = j;
    }

    for (int i = 1; i <= n; i++) {
        cur[0] = i; // mengubah a[0..i-1] menjadi string kosong butuh i penghapusan
        for (int j = 1; j <= m; j++) {
            int cost = (a[i - 1] == b[j - 1] ? 0 : 1);
            cur[j] = min({
                prev[j] + 1,          // Delete
                cur[j - 1] + 1,       // Insert
                prev[j - 1] + cost    // Match / Replace
            });
        }
        prev.swap(cur);
    }

    cout << prev[m] << "\n";

    return 0;
}
