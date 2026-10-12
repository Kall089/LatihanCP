/*
============================================================
✅ Solution 5: Nilai Terkecil ke-K pada Rentang
============================================================
Approach: Parallel binary search atas NILAI + BIT + kompresi koordinat
Complexity: Time O((n + q) log n log n) | Space O(n + q)
Key Insight: Kerangka parallel binary search TIDAK terbatas pada dimensi
             "waktu". Di sini yang di-binary-search adalah NILAI jawaban,
             dan "kejadian ke-t" berarti "memasukkan elemen terkecil ke-t
             ke dalam struktur". Mengenali bahwa kerangkanya sama persis
             adalah inti pelajaran hari ini.

📖 MENERJEMAHKAN "TERKECIL KE-K" MENJADI PREDIKAT MONOTON:
       "nilai terkecil ke-k pada [l, r] <= x"
   <=> "ada setidaknya k elemen pada [l, r] yang nilainya <= x"

   Predikat kedua MONOTON terhadap x: semakin besar x, semakin banyak
   elemen yang memenuhi. Jadi binary search berlaku, dan jawabannya adalah
   x TERKECIL yang membuat predikatnya benar.

📖 MENGHITUNG PREDIKATNYA:
   Urutkan seluruh elemen berdasarkan NILAI. Sapu dari nilai terkecil,
   tandai POSISI setiap elemen di dalam BIT.
   Setelah menandai t elemen terkecil, "berapa elemen pada [l, r] yang
   nilainya termasuk t terkecil" = jumlah posisi aktif di dalam [l, r],
   yang bisa dibaca BIT dalam O(log n).

   Jadi "waktu" dalam kerangka = "sudah berapa nilai terkecil yang dimasukkan".

⚠️ KOMPRESI KOORDINAT DIPERLUKAN karena nilai mencapai 10^9, sedangkan kita
   ingin mengindeksnya dengan peringkat 0..n-1. Setelah selesai, terjemahkan
   peringkat kembali menjadi nilai asli lewat kamusnya (Day 38).

⚠️ ELEMEN DENGAN NILAI SAMA harus ditangani konsisten. Dengan mengurutkan
   berdasarkan (nilai, posisi) dan memasukkannya satu per satu, elemen
   kembar mendapat "waktu" berbeda -- dan itu benar, karena "terkecil ke-k"
   memang menghitung kemunculan, bukan nilai berbeda.

⚠️ STRUKTUR BIT DI SINI BERBEDA dari Exercise 2 dan 3: di sana kita butuh
   range update + point query; di sini point update + range query.
   Keduanya BIT, tetapi peran add dan get bertukar. Perhatikan baik-baik --
   memakai varian yang salah menghasilkan jawaban yang kacau.

VERIFIKASI SAMPEL (a = [1,5,2,6,3]):
   query (1, 3, 2): elemen pada posisi 1..3 adalah {1, 5, 2}; terkecil
       kedua adalah 2.   ✓
   query (2, 5, 3): elemen pada posisi 2..5 adalah {5, 2, 6, 3}; terurut
       {2, 3, 5, 6}; terkecil ketiga adalah 5.   ✓

🔄 ALTERNATIVE APPROACHES:
- Persistent segment tree (Day 186-187): O(log n) per query dan mendukung
  ONLINE. Pendekatan yang lebih baik kalau query tidak boleh offline.
- Wavelet tree (Day 194): O(log n) per query, memori lebih hemat.
- Mo's algorithm (Day 184): O((n+q) sqrt(n) log n), lebih lambat di sini.
- Parallel binary search dipakai karena kerangkanya sudah kamu kuasai dan
  tidak butuh struktur data baru.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<int> bitArr;

void bitAdd(int i, int v) { for (; i <= n; i += i & -i) bitArr[i] += v; }
int bitSum(int i) { int s = 0; for (; i > 0; i -= i & -i) s += bitArr[i]; return s; }
int bitRange(int l, int r) { return bitSum(r) - bitSum(l - 1); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // urutkan elemen berdasarkan (nilai, posisi): urutan pemasukan
    vector<pair<int, int>> urut(n);
    for (int i = 1; i <= n; i++) urut[i - 1] = {a[i], i};
    sort(urut.begin(), urut.end());

    vector<int> ql(q), qr(q), qk(q);
    for (int i = 0; i < q; i++) cin >> ql[i] >> qr[i] >> qk[i];

    // binary search atas "sudah berapa nilai terkecil yang dimasukkan"
    vector<int> lo(q, 1), hi(q, n);
    vector<vector<int>> bucket(n + 2);

    while (true) {
        for (auto& b : bucket) b.clear();
        bool jalan = false;

        for (int i = 0; i < q; i++)
            if (lo[i] < hi[i]) {
                bucket[lo[i] + (hi[i] - lo[i]) / 2].push_back(i);
                jalan = true;
            }
        if (!jalan) break;

        bitArr.assign(n + 2, 0);                 // RESET

        for (int t = 1; t <= n; t++) {
            bitAdd(urut[t - 1].second, 1);       // aktifkan POSISI elemen ke-t

            for (int i : bucket[t]) {
                if (bitRange(ql[i], qr[i]) >= qk[i]) hi[i] = t;
                else                                 lo[i] = t + 1;
            }
        }
    }

    string out;
    for (int i = 0; i < q; i++) {
        out += to_string(urut[lo[i] - 1].first);  // peringkat -> nilai asli
        out += '\n';
    }
    cout << out;

    return 0;
}
