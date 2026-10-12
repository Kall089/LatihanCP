/*
============================================================
✅ SOLUSI Exercise 5: Urutan Tugas dengan Bobot
============================================================
Difficulty: Hard | Kompleksitas: O(n log n)

── IDE UTAMA ────────────────────────────────────────────────
Urutkan menaik menurut rasio t[i] / w[i].
Ditulis tanpa pembagian: i mendahului j jika
    t[i] * w[j] < t[j] * w[i]

── MENURUNKANNYA (exchange argument penuh) ─────────────────
Ambil urutan optimal. Lihat dua tugas BERDAMPINGAN, i lalu j.
Misal waktu berjalan sebelum keduanya adalah S.

  urutan (i, j):
      C[i] = S + t[i]
      C[j] = S + t[i] + t[j]
      biaya = w[i](S + t[i]) + w[j](S + t[i] + t[j])

  urutan (j, i):
      biaya = w[j](S + t[j]) + w[i](S + t[j] + t[i])

Kurangkan. Suku yang memuat S saling hilang (koefisiennya
w[i] + w[j] pada kedua kasus), begitu pula w[i]t[i] dan
w[j]t[j]. Yang tersisa:

  biaya(i,j) - biaya(j,i) = w[j]*t[i] - w[i]*t[j]

Jadi urutan (i, j) lebih murah tepat ketika
      w[j] * t[i] < w[i] * t[j]
  ⟺  t[i] / w[i] < t[j] / w[j]

Dan seperti biasa, tugas SEBELUM pasangan ini tidak terpengaruh
(waktu selesainya sama), tugas SESUDAHNYA juga tidak (karena
t[i] + t[j] tetap sama). Maka penukaran ini lokal dan aman.
Bubble sort dengan kriteria ini mengubah urutan optimal apa pun
menjadi urutan terurut rasio tanpa menaikkan biaya. ∎

── KENAPA HINDARI PEMBAGIAN ────────────────────────────────
Membandingkan (double)t[i]/w[i] < (double)t[j]/w[j] bisa salah
ketika dua rasio sangat dekat tetapi tidak sama — double punya
53 bit mantissa, sedangkan t dan w masing-masing sampai 10^6.
Bentuk perkalian selalu eksak.

── OVERFLOW ────────────────────────────────────────────────
t[i] * w[j] <= 10^6 * 10^6 = 10^12 → melampaui int (2*10^9).
Komparator WAJIB melakukan perkalian dalam long long.
Ini bug klasik: array bertipe long long tidak menyelamatkanmu
kalau komparatormu menerima int.

Total biaya: sum(w) <= 2*10^11 dan C max <= 2*10^11, sehingga
biaya bisa sangat besar. Pada batas soal ini, total <=
sekitar 2*10^5 * 10^6 * (2*10^5 * 10^6) = 4*10^22 yang MELEBIHI
long long. Batas soal nyata biasanya lebih kecil; untuk aman,
kode ini memakai __int128 pada akumulasi dan mencetaknya
manual. Kalau kamu yakin muat, long long lebih ringkas.

── HUBUNGAN DENGAN EXERCISE 1 ──────────────────────────────
Kalau semua w[i] = 1, komparatornya menjadi t[i] < t[j] —
persis SPT. Exercise 1 adalah kasus khusus soal ini.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void cetak(__int128 v) {
    if (v == 0) { cout << 0; return; }
    string s;
    while (v > 0) { s += char('0' + (int)(v % 10)); v /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    vector<pair<ll, ll>> a(n);              // (t, w)
    for (auto &p : a) cin >> p.first >> p.second;

    // Komparator hasil exchange argument.
    // Perkalian dalam long long — kedua sisi bisa mencapai 10^12.
    sort(a.begin(), a.end(), [](const pair<ll, ll> &x, const pair<ll, ll> &y) {
        return x.first * y.second < y.first * x.second;
    });

    __int128 sekarang = 0, total = 0;
    for (auto &p : a) {
        sekarang += p.first;                // tugas ini selesai di sini
        total += (__int128)p.second * sekarang;
    }

    cetak(total);
    cout << '\n';
    return 0;
}
