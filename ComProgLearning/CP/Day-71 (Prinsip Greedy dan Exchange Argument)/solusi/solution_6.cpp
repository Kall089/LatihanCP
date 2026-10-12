/*
============================================================
✅ SOLUSI Exercise 6: Menyeberangi Jembatan
============================================================
Difficulty: Hard | Kompleksitas: O(n log n)

── KENAPA GREEDY NAIF SALAH ────────────────────────────────
Strategi paling alami: "yang tercepat selalu mengantar dan
kembali". Pada {1, 2, 5, 10}:
    1&2 menyeberang (2), 1 kembali (1)   -> 3
    1&5 menyeberang (5), 1 kembali (1)   -> 6, total 9
    1&10 menyeberang (10)                -> total 19
Padahal jawabannya 17. Strategi alami RUGI 2 menit.

Yang lebih baik:
    1&2 menyeberang (2), 1 kembali (1)   -> 3
    5&10 menyeberang (10), 2 kembali (2) -> 12, total 15
    1&2 menyeberang (2)                  -> total 17
Idenya: dua orang paling lambat menyeberang BERSAMA, sehingga
waktu yang lambat "tersembunyi" di balik yang paling lambat —
10 dibayar sekali saja, bukan 10 lalu 5 secara terpisah.

── DUA STRATEGI UNTUK MEMINDAHKAN DUA TERLAMBAT ────────────
Setelah diurutkan menaik, misalkan sisa orang adalah
t[0..i] dengan i >= 3. Dua terlambat adalah t[i-1] dan t[i].

  Strategi A (dua tercepat sebagai kurir):
      t[0] & t[1] menyeberang     : t[1]
      t[0] kembali                : t[0]
      t[i-1] & t[i] menyeberang   : t[i]
      t[1] kembali                : t[1]
      biaya = t[0] + 2*t[1] + t[i]

  Strategi B (tercepat mengantar satu per satu):
      t[0] & t[i] menyeberang     : t[i]
      t[0] kembali                : t[0]
      t[0] & t[i-1] menyeberang   : t[i-1]
      t[0] kembali                : t[0]
      biaya = 2*t[0] + t[i-1] + t[i]

Kedua strategi memindahkan tepat dua orang terlambat ke seberang
dan mengembalikan senter ke sisi awal, dengan sisa orang yang
sama persis. Jadi keduanya sebanding, dan kita ambil yang lebih
murah pada setiap langkah.

Perbandingannya: A lebih murah jika
    t[0] + 2*t[1] < 2*t[0] + t[i-1]
⟺  2*t[1] < t[0] + t[i-1]
(Kedua sisi sudah dikurangi t[i] yang sama.)

── KASUS DASAR ─────────────────────────────────────────────
  n = 1 : t[0]
  n = 2 : t[1]                     (yang lebih lambat)
  n = 3 : t[0] + t[1] + t[2]
          (t[0]&t[1] menyeberang, t[0] kembali, t[0]&t[2]
           menyeberang → t[1] + t[0] + t[2])
Lupa menangani salah satu dari ini adalah sumber WA tersering
pada soal ini.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai HANYA strategi A atau HANYA strategi B. Keduanya
   gagal pada masukan tertentu. Contoh: {1, 1000, 1001, 1002}
   di sana strategi B jauh lebih baik.
2. Lupa long long: n = 10^5 dan t = 10^9 → total sampai
   sekitar 10^14.
3. Salah kasus dasar n = 3 (menuliskannya sebagai t[2] saja).
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
    vector<ll> t(n);
    for (ll &x : t) cin >> x;
    sort(t.begin(), t.end());

    ll total = 0;
    int i = n - 1;

    // Selama masih ada lebih dari 3 orang, pindahkan dua terlambat.
    while (i >= 3) {
        ll A = t[0] + 2 * t[1] + t[i];        // dua tercepat jadi kurir
        ll B = 2 * t[0] + t[i - 1] + t[i];    // tercepat antar satu-satu
        total += min(A, B);
        i -= 2;
    }

    // Kasus dasar untuk sisa orang t[0..i].
    if (i == 2)      total += t[0] + t[1] + t[2];
    else if (i == 1) total += t[1];
    else             total += t[0];           // i == 0

    cout << total << '\n';
    return 0;
}
