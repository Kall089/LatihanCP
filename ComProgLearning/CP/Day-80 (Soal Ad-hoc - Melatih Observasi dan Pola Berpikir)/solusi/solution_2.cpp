/*
============================================================
✅ SOLUSI Exercise 2: Jumlah Seluruh Subarray
============================================================
Difficulty: Easy | Kompleksitas: O(n) waktu, O(1) memori tambahan

── MEMBALIK URUTAN PENJUMLAHAN ─────────────────────────────
Alih-alih bertanya "berapa sumbangan tiap SUBARRAY", tanyakan
"berapa kali tiap ELEMEN ikut terhitung".

Elemen di posisi i (0-indexed) termuat dalam sebuah subarray
[l, r] tepat ketika l <= i <= r. Jadi:
  pilihan ujung kiri  : i + 1     (l dari 0 sampai i)
  pilihan ujung kanan : n - i     (r dari i sampai n-1)
  banyaknya subarray  : (i + 1) * (n - i)

Jawabannya sum a[i] * (i+1) * (n-i).
O(n) alih-alih O(n^2).

── VERIFIKASI DENGAN TANGAN ────────────────────────────────
Sampel {1, 2, 3}, n = 3:
  a[0]=1 : 1 * 3 = 3 kali   -> 3
  a[1]=2 : 2 * 2 = 4 kali   -> 8
  a[2]=3 : 3 * 1 = 3 kali   -> 9
  total 20  ✓
Selalu verifikasi rumus sumbangan dengan tangan pada contoh
kecil sebelum menulis kode. Salah satu faktor adalah kesalahan
yang sangat mudah dibuat dan sangat sulit terlihat.

── POLA UMUM ───────────────────────────────────────────────
"Jumlahkan sesuatu atas SEMUA subarray/pasangan/himpunan
bagian" hampir selalu diselesaikan dengan membalik urutan
penjumlahan.

  seluruh subarray            : (i+1) * (n-i)
  seluruh himpunan bagian     : 2^(n-1) per elemen
  seluruh pasangan |a_i - a_j|: urutkan, lalu a_i*i - prefix(i)
  maksimum tiap subarray      : butuh monotonic stack (Day 36)

Pola pikirnya: JANGAN iterasi objeknya, iterasi elemennya.

── MODULO BERTAHAP ─────────────────────────────────────────
(i+1) * (n-i) bisa mencapai 2.5 * 10^11 untuk n = 10^6, dan
dikali a[i] = 10^9 menjadi 2.5 * 10^20 — MELAMPAUI long long.
Karena itu ambil modulo pada hasil kali PERTAMA sebelum
mengalikan dengan a[i].

── JEBAKAN ─────────────────────────────────────────────────
1. Overflow karena mengalikan ketiganya sekaligus.
2. Salah rumus: (i+1)*(n-i) sering tertukar dengan i*(n-i-1).
3. Lupa modulo pada penjumlahan akhir.
4. Memakai int untuk indeks pada perkalian.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    if (!(cin >> n)) return 0;

    ll total = 0;
    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        ll banyak = ((i + 1) % MOD) * ((n - i) % MOD) % MOD;   // mod DULU
        total = (total + banyak % MOD * (x % MOD)) % MOD;
    }

    cout << total << '\n';
    return 0;
}
