/*
============================================================
✅ Solution 6: Empat Bilangan Berjumlah Nol
============================================================
Approach: Meet in the middle tanpa bitmask (4-SUM)
Complexity: Time O(N^2 log N) | Space O(N^2)
Key Insight: Meet in the middle bukan teknik tentang BITMASK -- ia teknik
             tentang MEMBAGI masalah menjadi dua bagian yang bisa
             dikerjakan, lalu menggabungkannya dengan pencarian.
             Di sini tidak ada subset sama sekali, tetapi semangatnya
             identik: N^4 menjadi N^2 + N^2.

📖 PENJELASAN PENDEKATAN:
1. Bangkitkan seluruh N^2 jumlah A[i] + B[j], simpan dalam array.
2. Urutkan array itu.
3. Untuk setiap dari N^2 jumlah C[k] + D[l], hitung berapa banyak
   -(C[k] + D[l]) yang ada di dalam array terurut.
4. Jumlahkan.

   N = 1000 memberi N^2 = 10^6 elemen -- 8 MB, aman.
   Total operasi: 10^6 untuk membangkitkan, 10^6 * 20 untuk sort,
   10^6 * 20 untuk mencari. Sekitar 4*10^7 -- lolos dengan nyaman.
   Bandingkan N^4 = 10^12, yang mustahil.

⚠️ MENGHITUNG KEMUNCULAN, BUKAN KEBERADAAN.
   Sama seperti Solution 2: upper_bound - lower_bound. Memakai
   binary_search hanya memberi ya/tidak, dan jawabannya salah karena
   banyak pasangan bisa punya jumlah yang sama.

⚠️ SORTING vs HASH MAP:
   Hash map memberi O(N^2) rata-rata alih-alih O(N^2 log N), sekitar
   20 kali lebih sedikit operasi pencarian. Tetapi:
   - unordered_map di Codeforces bisa dijadikan O(n) per operasi oleh
     masukan anti-hash yang dirancang khusus.
   - map (pohon merah-hitam) punya konstanta yang JAUH lebih besar daripada
     vector terurut, sehingga sering lebih lambat daripada sorting.
   Untuk soal ini, sorting + binary search adalah pilihan paling aman:
   dijamin O(log), konstanta kecil, tidak bisa di-hack.

⚠️ TIPE DATA: nilai sampai 2^28, sehingga A[i] + B[j] sampai 2^29 -- muat
   di int. Tetapi JAWABANNYA bisa mencapai N^4 = 10^12, sehingga penghitung
   WAJIB long long. Ini kesalahan yang mudah terjadi: jumlahnya kecil,
   tetapi hitungannya besar.

⚠️ MEMORI: N^2 = 10^6 long long = 8 MB. Kalau N bisa mencapai 4000,
   N^2 = 1.6*10^7 dan memorinya 128 MB -- perhitungan memori sama pentingnya
   dengan perhitungan waktu.

VERIFIKASI SAMPEL 2 (N = 1): 1 + (-1) + 1 + (-1) = 0, jadi tepat satu
cara.   ✓

🔄 ALTERNATIVE APPROACHES:
- Hash map: lebih cepat rata-rata, berisiko di-hack.
- Untuk 6 variabel (SPOJ ABCDEF), pola yang sama berlaku: bagi menjadi
  3 + 3, menghasilkan O(N^3 log N).
- Kalau hanya butuh KEBERADAAN (bukan hitungan), bitset kadang lebih cepat.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<ll> A(n), B(n), C(n), D(n);
    for (int i = 0; i < n; i++) cin >> A[i] >> B[i] >> C[i] >> D[i];

    // Paruh pertama: seluruh A[i] + B[j]
    vector<ll> AB;
    AB.reserve((size_t)n * n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) AB.push_back(A[i] + B[j]);

    sort(AB.begin(), AB.end());

    // Paruh kedua: untuk tiap C[k] + D[l], cari pasangannya
    ll total = 0;                                    // bisa 10^12 -> long long
    for (int k = 0; k < n; k++)
        for (int l = 0; l < n; l++) {
            ll butuh = -(C[k] + D[l]);
            total += upper_bound(AB.begin(), AB.end(), butuh)
                   - lower_bound(AB.begin(), AB.end(), butuh);
        }

    cout << total << '\n';
    return 0;
}
