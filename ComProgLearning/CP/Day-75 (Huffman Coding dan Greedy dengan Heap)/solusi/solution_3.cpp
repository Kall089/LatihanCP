/*
============================================================
✅ SOLUSI Exercise 3: Membelah Papan
============================================================
Difficulty: Medium | Kompleksitas: O(n log n)

── PEMETAAN ────────────────────────────────────────────────
Soal ini adalah Exercise 1 yang dibaca MUNDUR.

Putar rekaman proses pemotongan dari akhir ke awal: setiap
pemotongan yang membelah papan sepanjang L menjadi x dan y,
kalau diputar mundur, menjadi penggabungan x dan y menjadi
papan sepanjang L = x + y.

Biayanya pun cocok: memotong papan sepanjang L berbiaya L,
dan L = x + y adalah persis biaya menggabungkan x dan y.

Jadi:
  urutan pemotongan optimal  <=>  urutan penggabungan optimal
  total biaya potong         =    total biaya gabung

Kode-nya identik dengan Exercise 1. Tidak ada algoritma baru
yang perlu ditulis.

── MEMERIKSA DENGAN TANGAN ─────────────────────────────────
Sampel 1: potongan {8, 4, 4}, papan awal sepanjang 16.

  Urutan A: belah 16 -> (8, 8) biaya 16
            belah 8  -> (4, 4) biaya 8
            total 24  ✓ optimal

  Urutan B: belah 16 -> (12, 4) biaya 16
            belah 12 -> (8, 4)  biaya 12
            total 28

Selisihnya nyata. Dalam bahasa penggabungan: urutan A
menggabungkan 4+4 lebih dulu (dua terkecil), urutan B
menggabungkan 8+4 lebih dulu. Huffman memilih A.

── PELAJARAN YANG LEBIH BESAR ──────────────────────────────
Sebelum menulis algoritma baru, selalu tanyakan: "apakah ini
soal yang sudah saya selesaikan, dibaca dari arah lain?"
Soal-soal yang menyebut MEMBELAH, MEMBAGI, atau MENGHANCURKAN
sering kali adalah soal MENGGABUNGKAN yang dibalik.

── JEBAKAN ─────────────────────────────────────────────────
1. Mencoba menyimulasikan pemotongan secara langsung dari
   papan besar. Bisa, tetapi jauh lebih rumit dan mudah salah.
2. Mengira biaya potong adalah panjang HASIL potongan. Bukan —
   biayanya panjang papan yang sedang dipotong.
3. n = 1: tidak ada pemotongan sama sekali, jawabannya 0.
4. Arah heap dan tipe data — sama persis dengan Exercise 1.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;

    // identik dengan Exercise 1: memotong = menggabungkan, dibaca mundur
    priority_queue<ll, vector<ll>, greater<ll>> pq(a.begin(), a.end());

    ll total = 0;
    while (pq.size() > 1) {
        ll x = pq.top(); pq.pop();
        ll y = pq.top(); pq.pop();
        total += x + y;
        pq.push(x + y);
    }

    cout << total << '\n';
    return 0;
}
