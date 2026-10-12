/*
============================================================
✅ SOLUSI Exercise 2: Total Waktu Server Sibuk
============================================================
Difficulty: Easy | Kompleksitas: O(n log n)

── IDE UTAMA ────────────────────────────────────────────────
Gabungkan dulu (Exercise 1), baru jumlahkan panjang tiap blok.

── KENAPA TIDAK BOLEH LANGSUNG DIJUMLAHKAN ─────────────────
Sampel 1: [1,5] [3,7] [10,12]
  penjumlahan langsung : 4 + 4 + 2 = 10
  jawaban benar        : [1,7] dan [10,12] -> 6 + 2 = 8
Selisih 2 adalah bagian [3,5] yang terhitung dua kali.

── PENDEKATAN ALTERNATIF: DIFFERENCE ARRAY ─────────────────
Kompres seluruh koordinat (Day 38), lalu untuk tiap permintaan
lakukan d[id(s)]++ dan d[id(e)]--. Setelah prefix sum, segmen
antara koordinat ke-j dan ke-(j+1) sibuk bila nilainya > 0;
tambahkan panjang segmen itu.
Kompleksitasnya sama, O(n log n), didominasi kompresi.

Kapan memilih mana:
  butuh daftar blok hasil            -> merging
  butuh "berapa lapis tumpang tindih" -> difference array
  banyak update lalu satu query       -> difference array

Menulis KEDUANYA lalu membandingkan hasilnya pada masukan acak
adalah cara paling cepat menemukan bug kasus tepi. Kalau
hasilnya berbeda, hampir selalu masalahnya bilangan bulat vs
kontinu.

── JEBAKAN ─────────────────────────────────────────────────
1. Total bisa mencapai 10^9 — muat di int, tetapi hanya nyaris.
   Pakai long long tanpa berpikir dua kali.
2. Permintaan yang identik (sampel 2) harus dihitung sekali.
   Kode penggabungan menanganinya otomatis.
3. Rentangnya [s, e) — durasi e - s, bukan e - s + 1.
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
    vector<pair<ll, ll>> a(n);
    for (auto& [s, e] : a) cin >> s >> e;

    sort(a.begin(), a.end());

    ll total = 0;
    ll curL = a[0].first, curR = a[0].second;
    for (int i = 1; i < n; i++) {
        auto [s, e] = a[i];
        if (s <= curR) {
            curR = max(curR, e);           // masih menyambung
        } else {
            total += curR - curL;          // blok selesai
            curL = s; curR = e;
        }
    }
    total += curR - curL;                  // blok terakhir

    cout << total << '\n';
    return 0;
}
