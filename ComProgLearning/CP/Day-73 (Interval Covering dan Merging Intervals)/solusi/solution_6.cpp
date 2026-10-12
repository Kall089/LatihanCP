/*
============================================================
✅ SOLUSI Exercise 6: Menutupi Setiap Titik K Kali
============================================================
Difficulty: Hard | Kompleksitas: O((n + M) log n) waktu, O(n + M) memori

── DARI K = 1 KE K UMUM ────────────────────────────────────
Dengan K = 1 soal ini persis Exercise 3. Perbedaannya: kita
tidak lagi bertanya "sudah tertutup atau belum", melainkan
"sudah tertutup berapa lapis".

── IDE UTAMA ────────────────────────────────────────────────
Sapu posisi j dari 0 sampai M-1. Pelihara:
  aktif = banyaknya tukang TERPILIH yang mencakup segmen j
  heap  = tukang yang l-nya sudah <= j dan BELUM dipilih,
          diurutkan menurut r TERBESAR

Pada tiap posisi j:
  1. kurangi 'aktif' sebanyak tukang terpilih yang berakhir di j
  2. masukkan ke heap semua tukang dengan l == j
  3. selama aktif < K:
        ambil tukang dengan r terbesar dari heap
        kalau heap kosong atau r <= j  ->  -1
        pilih tukang itu: aktif++, catat bahwa ia berakhir di r

── KENAPA "r TERBESAR" BENAR ───────────────────────────────
Exchange argument. Andaikan solusi optimal O, pada posisi j,
memilih tukang y padahal ada tukang x yang belum dipilih dengan
l_x <= j dan r_x > r_y.
Ganti y dengan x di dalam O. Setiap segmen yang tadinya
ditutupi y pada [j, r_y) juga ditutupi x karena
[j, r_y) ⊆ [j, r_x). Segmen di kiri j tidak terpengaruh karena
kita sudah melewatinya dan syaratnya sudah terpenuhi saat itu.
Jumlah tukang tidak berubah, penutupan tidak berkurang. ∎

Perhatikan bahwa argumen ini mengandalkan sapuan dari KIRI ke
kanan: keputusan di posisi j tidak pernah bisa merusak sesuatu
di kiri j.

── MELACAK 'aktif' TANPA MEMERIKSA SATU PER SATU ───────────
Kalau setiap posisi kita menghitung ulang berapa tukang terpilih
yang masih aktif, kompleksitasnya O(n*M). Sebagai gantinya,
saat memilih tukang dengan ujung r, cukup catat berakhir[r]++.
Pada awal posisi j, lakukan aktif -= berakhir[j].
Ini teknik yang sama dengan difference array (Day 31): kita
mencatat PERUBAHAN, bukan keadaan.

── KENAPA HEAP, BUKAN SORTING BIASA ────────────────────────
Himpunan tukang yang "tersedia" bertambah seiring j maju
(tukang baru masuk saat l == j) dan berkurang saat kita
memilih. Kita selalu butuh maksimum dari himpunan yang berubah
— itu definisi priority queue.

Tukang dengan r <= j yang masih tersisa di heap tidak berguna:
mereka tidak menutupi segmen j pun. Karena heap mengurutkan
menurut r terbesar, kalau puncaknya saja sudah <= j maka
seluruh isi heap tidak berguna -> jawabannya -1.

── JEBAKAN ─────────────────────────────────────────────────
1. Rentangnya SETENGAH TERBUKA [l, r): tukang mencakup segmen
   l sampai r-1. Syarat berguna adalah r > j, bukan r >= j.
2. Lupa mengurangi 'aktif' saat tukang berakhir.
3. Memakai min-heap. Kita butuh r TERBESAR.
4. Array 'berakhir' harus berukuran M+1 karena r bisa sama
   dengan M.
5. Menyangka soal ini bisa diselesaikan dengan menjalankan
   Exercise 3 sebanyak K kali. Tidak bisa — pilihan putaran
   pertama merusak putaran berikutnya, sama seperti Exercise 4
   pada Day 72.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, M, K;
    if (!(cin >> n >> M >> K)) return 0;

    // kelompokkan tukang menurut ujung kirinya
    vector<vector<int>> mulai(M + 1);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        if (l <= M) mulai[l].push_back(r);
    }

    priority_queue<int> heap;          // r terbesar di atas
    vector<int> berakhir(M + 2, 0);    // berakhir[t] = berapa terpilih yang habis di t
    int aktif = 0;
    ll jawab = 0;

    for (int j = 0; j < M; j++) {
        aktif -= berakhir[j];                    // tukang terpilih yang habis di sini
        for (int r : mulai[j]) heap.push(r);     // tukang baru tersedia

        while (aktif < K) {
            if (heap.empty() || heap.top() <= j) {
                cout << -1 << '\n';              // tidak ada yang menutupi segmen j
                return 0;
            }
            int r = heap.top(); heap.pop();
            berakhir[r]++;                       // catat kapan ia habis
            aktif++;
            jawab++;
        }
    }

    cout << jawab << '\n';
    return 0;
}
