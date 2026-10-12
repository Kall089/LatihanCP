/*
============================================================
✅ Solution 6: Nilai yang Muncul Tepat K Kali
============================================================
Approach: Dua lapis penghitungan + pembersihan berbasis elemen
Complexity: Time O(total n) | Space O(V)
Key Insight: Dua hal berbeda yang sama pentingnya.
             (1) Pertanyaannya butuh frekuensi DARI frekuensi -- dua lapis
                 penghitungan, pola yang sering terlewat.
             (2) Dengan T sampai 10^5 kasus dan domain 10^6, membersihkan
                 seluruh array setiap kasus adalah 10^11 operasi. Kita hanya
                 boleh membersihkan slot yang benar-benar tersentuh.

📖 PENJELASAN PENDEKATAN:
1. Lapis pertama: cnt[x]++ untuk tiap elemen -> berapa kali tiap NILAI muncul.
2. Lapis kedua: untuk tiap nilai berbeda, naikkan cntCnt[cnt[nilai]]
   -> berapa NILAI yang punya frekuensi tertentu.
   Supaya tiap nilai dihitung sekali saja, kita hanya memprosesnya pada
   kemunculan pertamanya (ditandai lewat pemeriksaan).
3. Jawabannya cntCnt[K].
4. Bersihkan hanya slot yang tersentuh.

⚠️ PEMBERSIHAN ADALAH INTI SOAL INI, bukan penghitungannya.

   SALAH (TLE):
       while (T--) { memset(cnt, 0, sizeof cnt); ... }
       -> 10^5 kasus x 10^6 slot = 10^11 operasi

   BENAR (O(total n)):
       for (int x : a) cnt[x] = 0;
       -> total seluruh pembersihan = total seluruh n <= 10^6

   Ini pola yang layak dijadikan refleks: kalau kamu memakai array besar
   di dalam loop test case, JANGAN PERNAH memset di dalamnya.

   Alternatif elegan yang juga umum: array "cap waktu".
       if (stamp[x] != kasusKe) { stamp[x] = kasusKe; cnt[x] = 0; }
       Dengan ini tidak perlu membersihkan sama sekali -- slot yang capnya
       kedaluwarsa dianggap kosong. Berguna kalau kamu tidak menyimpan
       daftar elemen yang disentuh.

⚠️ cntCnt juga harus dibersihkan, dan indeksnya paling besar n. Bersihkan
   dengan cara yang sama: hanya slot yang mungkin tersentuh.

VERIFIKASI SAMPEL 1:
   kasus 1: a = [1,1,2,2,3], K = 2
            cnt: 1->2, 2->2, 3->1
            cntCnt: 2 muncul untuk dua nilai, 1 muncul untuk satu nilai
            cntCnt[2] = 2  ✓
   kasus 2: a = [7,7,7,7], K = 1
            cnt: 7->4;  cntCnt[4] = 1;  cntCnt[1] = 0  ✓

🔄 ALTERNATIVE APPROACHES:
- map per kasus: otomatis bersih karena dibuat ulang, tetapi ~100x lebih
  lambat per operasi. Untuk total 10^6 elemen, ini berisiko.
- Sort per kasus lalu hitung berturut-turut: O(n log n) total, bekerja juga
  dan tidak perlu memikirkan pembersihan sama sekali. Pilihan yang sah
  kalau kamu ingin kode yang lebih aman meski sedikit lebih lambat.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAKS = 1000005;
int cnt[MAKS];                 // berapa kali tiap NILAI muncul
int cntCnt[MAKS];              // berapa NILAI yang punya frekuensi tertentu

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    string out;

    while (T--) {
        int n, K;
        cin >> n >> K;
        vector<int> a(n);
        for (int& x : a) cin >> x;

        // Lapis 1: frekuensi tiap nilai
        for (int x : a) cnt[x]++;

        // Lapis 2: frekuensi dari frekuensi.
        // Proses tiap nilai berbeda TEPAT SEKALI: kita kenali kemunculan
        // pertama dengan menandai slot menjadi negatif setelah diproses.
        for (int x : a) {
            if (cnt[x] > 0) {
                cntCnt[cnt[x]]++;
                cnt[x] = -cnt[x];        // tandai sudah diproses
            }
        }

        out += to_string(K <= n ? cntCnt[K] : 0);
        out += '\n';

        // Bersihkan HANYA slot yang tersentuh -- O(n), bukan O(MAKS)
        for (int x : a) {
            if (cnt[x] < 0) { cntCnt[-cnt[x]] = 0; cnt[x] = 0; }
        }
    }

    cout << out;
    return 0;
}
