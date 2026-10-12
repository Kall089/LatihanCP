/*
============================================================
✅ Solution 2: Berapa Elemen dalam Rentang Nilai
============================================================
Approach: Urutkan sekali, lalu selisih dua bound per query
Complexity: Time O(n log n + q log n) | Space O(n)
Key Insight: Setelah array terurut, "berapa elemen bernilai di [L, R]"
             menjadi satu pengurangan. Kuncinya memilih bound yang TEPAT:
             lower untuk batas kiri, upper untuk batas kanan.

📖 RUMUSNYA:
    jumlah = upperBound(R) - lowerBound(L)

    lowerBound(L) = indeks pertama yang >= L   -> elemen sebelum ini < L, dibuang
    upperBound(R) = indeks pertama yang >  R   -> elemen dari sini > R, dibuang
    Yang tersisa di antara keduanya adalah tepat elemen pada [L, R].

⚠️ KENAPA BUKAN lowerBound(R) UNTUK BATAS KANAN:
    lowerBound(R) menunjuk ke kemunculan PERTAMA nilai R, sehingga seluruh
    salinan R lainnya tidak terhitung. Pada sampel, rentang [3,5] dengan
    array [1,3,3,3,5,7]: lowerBound(5) = 4, sedangkan upperBound(5) = 5.
    Memakai yang salah menghasilkan 3, padahal jawabannya 4.
    Aturan mudahnya: batas yang INKLUSIF di kanan selalu memakai upper.

⚠️ LANGKAH PERSIAPAN YANG WAJIB: array HARUS diurutkan dulu.
    Binary search pada data tak terurut tidak menghasilkan error apa pun --
    ia hanya mengembalikan angka sembarang. Ini bug senyap yang sulit
    dilacak karena programnya "berjalan normal".

⚠️ RENTANG NILAI, BUKAN RENTANG POSISI. Kalau soal menanyakan "berapa elemen
    di POSISI l..r yang nilainya di [L, R]", ini masalah yang jauh lebih
    sulit -- butuh merge sort tree (Day 179) atau wavelet tree (Day 194).
    Membaca soal dengan teliti menghemat banyak waktu.

⚠️ L > R: soal ini menjamin L <= R, tetapi kalau tidak dijamin, rumusnya
    akan menghasilkan angka negatif. Tambahkan penjagaan.

🔄 ALTERNATIVE APPROACHES:
- Array frekuensi + prefix sum (Day 40): O(V) preprocessing, O(1) per query.
  Lebih cepat kalau rentang NILAI kecil, tetapi mustahil kalau nilai sampai
  10^9 seperti di sini.
- Kompresi koordinat (Day 38) + prefix sum: O(n log n) preprocessing,
  O(log n) per query. Setara dengan solusi ini.
- Fenwick Tree: hanya perlu kalau ada UPDATE di antara query.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    sort(a.begin(), a.end());              // WAJIB, dan mudah terlupa

    string out;
    while (q--) {
        int L, R;
        cin >> L >> R;
        int lb = lower_bound(a.begin(), a.end(), L) - a.begin();
        int ub = upper_bound(a.begin(), a.end(), R) - a.begin();
        out += to_string(ub - lb);
        out += '\n';
    }
    cout << out;

    return 0;
}
