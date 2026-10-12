/*
============================================================
✅ SOLUSI Exercise 6: Knapsack dengan Kapasitas Raksasa
============================================================
Difficulty: Hard | Kompleksitas: O(n * V) dengan V = sum(v[i]) <= 10^5

── MEMBACA BATASAN SEBAGAI PETUNJUK ────────────────────────
  W <= 10^9        -> tabel berindeks kapasitas MUSTAHIL
  sum(v) <= 10^5   -> batasan mencolok, hampir pasti disengaja
Ketika salah satu dimensi terlalu besar dan dimensi lain
sangat kecil, tukar perannya.

── MEMBALIK DP ─────────────────────────────────────────────
DP knapsack biasa:
  dp[c] = NILAI maksimum dengan kapasitas c
DP yang dibalik:
  dp[val] = BERAT minimum untuk mencapai nilai tepat val

Transisinya cerminan langsung:
  dp[val] = min(dp[val], dp[val - v[i]] + w[i])
Loop val MUNDUR agar tiap barang dipakai sekali — aturan yang
sama persis dengan knapsack biasa, hanya indeksnya berbeda.

Jawabannya: nilai terbesar val yang dp[val] <= W.

── NILAI AWAL DAN SENTINEL ─────────────────────────────────
  dp[0] = 0            (nilai 0 dicapai dengan berat 0)
  dp[val] = INF        untuk val > 0

INF harus dipilih hati-hati: kita akan menghitung
dp[val - v[i]] + w[i], dan w[i] sampai 10^9. Kalau INF =
LLONG_MAX, penjumlahan itu MELUAP dan menghasilkan bilangan
negatif — yang lalu terlihat "lebih kecil" dan mencemari tabel.
Pakai INF yang aman, misalnya 4*10^18 / 4, atau lebih sederhana:
periksa dp[val - v[i]] != INF sebelum menjumlahkan.
Kode di bawah memakai cara kedua karena lebih eksplisit.

── KENAPA JAWABANNYA PASTI ADA ─────────────────────────────
dp[0] = 0 <= W selalu, jadi jawaban minimal 0. Kalau tidak ada
barang yang muat sendirian, jawabannya memang 0.

── PEMERIKSAAN KEWARASAN ───────────────────────────────────
Hitung juga batas atas fractional dari seluruh barang. Jawaban
0/1 tidak boleh melebihinya. Pemeriksaan ini murah dan sering
menangkap bug indeks. Kode di bawah menyertakannya sebagai
assert yang bisa kamu aktifkan saat menguji.

── SAMPEL 2 ────────────────────────────────────────────────
Dua barang berberat 10^9 dengan W = 10^9: hanya satu yang muat,
jawabannya 1000. Ini menguji apakah kamu benar-benar memakai
berat, bukan sekadar menjumlahkan nilai.

── KAPAN MEMILIH DIMENSI MANA ──────────────────────────────
  W kecil, nilai besar   -> dp[kapasitas] = nilai maksimum
  nilai kecil, W besar   -> dp[nilai] = berat minimum
  keduanya besar, n <= 40 -> meet in the middle (Day 54)
  keduanya besar, n besar -> kemungkinan bukan knapsack

── JEBAKAN ─────────────────────────────────────────────────
1. Overflow pada sentinel INF.
2. Loop val MAJU (menjadi unbounded knapsack).
3. Ukuran tabel: sum(v) + 1, bukan max(v) + 1.
4. Membaca jawaban sebagai dp[V] alih-alih val terbesar yang
   dp[val] <= W.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll W;
    if (!(cin >> n >> W)) return 0;
    vector<ll> w(n), v(n);
    ll V = 0;
    for (int i = 0; i < n; i++) { cin >> w[i] >> v[i]; V += v[i]; }

    const ll INF = LLONG_MAX;
    vector<ll> dp(V + 1, INF);
    dp[0] = 0;                                    // nilai 0 -> berat 0

    for (int i = 0; i < n; i++)
        for (ll val = V; val >= v[i]; val--)      // MUNDUR: tiap barang sekali
            if (dp[val - v[i]] != INF)            // hindari overflow
                dp[val] = min(dp[val], dp[val - v[i]] + w[i]);

    ll jawab = 0;
    for (ll val = V; val >= 0; val--)
        if (dp[val] <= W) { jawab = val; break; }

    cout << jawab << '\n';
    return 0;
}
