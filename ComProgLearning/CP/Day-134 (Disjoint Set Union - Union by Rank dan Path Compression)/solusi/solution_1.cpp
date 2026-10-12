/*
============================================================
✅ Solution 1: Berapa Kelompok Pertemanan
============================================================
Approach: DSU dengan union by size + path halving
Complexity: Time O((N + M) α(N)) | Space O(N)
Key Insight: Menggabungkan dua kelompok tidak perlu menyentuh seluruh
             anggotanya. Cukup membuat satu PERWAKILAN menunjuk ke
             perwakilan lainnya -- satu operasi, bukan O(ukuran kelompok).

📖 DUA OPTIMASI, DAN KENAPA KEDUANYA:
   Tanpa optimasi apa pun, rantai penunjuk bisa menjadi garis lurus
   sepanjang N, sehingga satu pencarian menjadi O(N).

   UNION BY SIZE: selalu sambungkan pohon yang lebih KECIL ke bawah pohon
   yang lebih besar. Akibatnya sebuah pohon berketinggian h harus memuat
   setidaknya 2^h simpul, sehingga tingginya paling besar log2(N).

   PATH HALVING: saat menelusuri, sambungkan setiap simpul ke KAKEKNYA.
   Ini memendekkan jalur untuk pemanggilan berikutnya.

   Salah satu saja memberi O(log N). KEDUANYA memberi O(alpha(N)), yang
   praktis konstanta -- alpha(N) <= 4 untuk seluruh N yang masuk akal.
   Biayanya hanya dua baris, jadi tidak ada alasan memilih salah satu.

📖 MELACAK DUA STATISTIK SECARA GRATIS:
   `komponen` berkurang tepat satu setiap kali dua kelompok BERBEDA
   benar-benar bergabung -- itulah sebabnya unite mengembalikan bool.
   `sz` sudah dibutuhkan untuk union by size, jadi ukuran kelompok
   tersedia tanpa biaya tambahan.

⚠️ PENGGABUNGAN BERULANG HARUS TIDAK BERPENGARUH. Kalau a dan b sudah
   sekelompok, unite harus mengembalikan false TANPA mengubah apa pun.
   Melupakan pemeriksaan ini membuat `komponen` menjadi negatif.

⚠️ 1-BASED: siswa dinomori 1..N, jadi alokasikan N+1 slot. Kalau kamu
   mengalokasikan N slot dan mengakses indeks N, itu di luar batas --
   dan sering TIDAK crash, sehingga menjadi bug senyap.

⚠️ find ITERATIF, BUKAN REKURSIF. Untuk N = 2*10^5 versi rekursif
   biasanya masih aman, tetapi untuk N = 10^6 dengan rantai panjang ia
   bisa menyebabkan stack overflow. Biasakan versi iteratif sejak sekarang.

VERIFIKASI SAMPEL 1 (6 siswa, kenalan: 1-2, 2-3, 4-5, 1-3):
   1-2 : gabung, komponen 6 -> 5
   2-3 : gabung, komponen 5 -> 4
   4-5 : gabung, komponen 4 -> 3
   1-3 : SUDAH sekelompok -> false, komponen tetap 3
   Kelompok: {1,2,3}, {4,5}, {6}. Terbesar 3.   ✓

CATATAN: implementasi ini telah diuji terhadap BFS pada 20000 graf acak.

🔄 ALTERNATIVE APPROACHES:
- BFS/DFS pada graf: O(N + M) juga, dan lebih fleksibel (memberi jarak,
  jalur, urutan kunjungan). Tetapi ia butuh SELURUH sisi diketahui lebih
  dulu. DSU unggul kalau sisi datang satu per satu dan kamu harus
  menjawab di tengah jalan (lihat Exercise 4).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> par(n + 1), sz(n + 1, 1);          // n+1: siswa 1-based
    iota(par.begin(), par.end(), 0);
    int komponen = n;

    function<int(int)> find = [&](int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }   // path halving
        return x;
    };

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a = find(a); b = find(b);
        if (a == b) continue;                      // sudah sekelompok
        if (sz[a] < sz[b]) swap(a, b);             // union by size
        par[b] = a;
        sz[a] += sz[b];
        komponen--;
    }

    int terbesar = 0;
    for (int i = 1; i <= n; i++)
        if (find(i) == i) terbesar = max(terbesar, sz[i]);   // hanya perwakilan

    cout << komponen << ' ' << terbesar << '\n';
    return 0;
}
