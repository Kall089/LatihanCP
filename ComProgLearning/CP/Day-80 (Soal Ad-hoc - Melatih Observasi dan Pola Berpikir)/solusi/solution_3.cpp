/*
============================================================
✅ SOLUSI Exercise 3: Mundur dari Tujuan
============================================================
Difficulty: Medium | Kompleksitas: O(log max(a, b))

── KENAPA MAJU MUSTAHIL ────────────────────────────────────
Dari (1,1) ada dua pilihan pada tiap langkah, sehingga
percabangannya 2^langkah. Dengan target sampai 10^18, jumlah
langkahnya bisa puluhan dan pohonnya jauh terlalu besar.

── KENAPA MUNDUR MUDAH ─────────────────────────────────────
Operasi maju:
    (x, y) -> (x + y, y)   atau   (x, y + x)
Inversnya:
    (a, b) -> (a - b, b)   kalau a > b
    (a, b) -> (a, b - a)   kalau b > a

Perhatikan: hanya SATU yang mungkin, karena hasil pengurangan
harus tetap positif. Tidak ada percabangan sama sekali.

Ini adalah inti Pola B: kalau percabangan maju besar tetapi
percabangan mundur kecil, baliklah arahnya.

── MEMPERCEPAT DENGAN PEMBAGIAN ────────────────────────────
Kalau a jauh lebih besar dari b, kita akan mengurangi b
berkali-kali. Itu persis algoritma Euclid, dan bisa dipercepat
dengan pembagian.

Tetapi hati-hati: kita harus berhenti sebelum a menjadi <= 0.
Karena target akhirnya (1,1), nilai a boleh turun sampai 1.
Jumlah pengurangan yang aman adalah (a - 1) / b, BUKAN a / b.
Memakai a / b bisa membuat a menjadi 0 atau negatif.

Contoh: a = 5, b = 3.
    (a-1)/b = 4/3 = 1  -> a menjadi 2   ✓
    a/b     = 5/3 = 1  -> a menjadi 2   (kebetulan sama)
Contoh: a = 6, b = 3.
    (a-1)/b = 5/3 = 1  -> a menjadi 3   ✓
    a/b     = 6/3 = 2  -> a menjadi 0   ✗ RUSAK

── KASUS MACET ─────────────────────────────────────────────
Kalau a == b dan keduanya bukan 1, tidak ada langkah mundur
yang sah (mengurangi menghasilkan 0). Jawabannya -1.
Sampel 3 menguji ini dengan (4, 4).

Kasus a == b == 1 adalah keadaan awal, jawabannya 0.

── KASUS TEPI b == 1 ───────────────────────────────────────
Kalau b == 1, maka (a-1)/1 = a-1 pengurangan langsung membawa
a ke 1. Rumus umumnya menanganinya dengan benar — tetapi
periksa dengan tangan: (5,1) butuh 4 langkah, dan
(5-1)/1 = 4. ✓

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai a/b alih-alih (a-1)/b.
2. Lupa kasus a == b.
3. Menelusuri maju dengan BFS/DFS.
4. Lupa long long: a, b sampai 10^18. Jumlah langkahnya juga
   bisa mencapai 10^18 (kasus b = 1, a = 10^18).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll a, b;
    if (!(cin >> a >> b)) return 0;

    ll langkah = 0;
    while (a > 1 || b > 1) {
        if (a == b) { cout << -1 << '\n'; return 0; }   // macet
        if (a > b) {
            ll k = (a - 1) / b;                         // (a-1), BUKAN a
            langkah += k;
            a -= b * k;
        } else {
            ll k = (b - 1) / a;
            langkah += k;
            b -= a * k;
        }
    }

    cout << langkah << '\n';
    return 0;
}
