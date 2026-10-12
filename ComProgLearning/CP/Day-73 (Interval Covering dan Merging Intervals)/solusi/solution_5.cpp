/*
============================================================
✅ SOLUSI Exercise 5: Menutupi dengan Panjang Tetap
============================================================
Difficulty: Hard | Kompleksitas: O(n log n) waktu, O(n) memori

── PERBEDAAN MENDASAR DARI EXERCISE 3 ──────────────────────
Exercise 3 : interval SUDAH ADA, kamu memilih sebagian.
Exercise 5 : kamu BEBAS menaruh interval di mana pun, tetapi
             panjangnya tetap K.
Keduanya greedy, tetapi keputusan yang diambil berbeda jenis.

── IDE UTAMA ────────────────────────────────────────────────
Urutkan posisi rumah. Ambil rumah paling kiri yang belum
terlayani, sebut posisinya x. Pasang menara tepat di p = x,
sehingga ia melayani [x, x + K]. Lewati semua rumah dengan
posisi <= x + K. Ulangi.

── KENAPA MEMASANG TEPAT DI x ──────────────────────────────
Menara harus melayani x, jadi p <= x <= p + K, yaitu
p berada di [x - K, x].
Menara itu melayani [p, p + K]. Semakin besar p, semakin jauh
ke kanan jangkauannya, dan rumah-rumah berikutnya semuanya
berada di kanan x. Jadi p sebesar mungkin selalu paling
menguntungkan, yaitu p = x.

Exchange argument formalnya: ambil solusi optimal O. Menara di
O yang melayani rumah terkiri x berada pada suatu p <= x.
Geser menara itu ke p' = x. Semua rumah yang tadinya dilayani
menara tersebut berada di [p, p + K]; yang berada di kiri x
tidak ada (x adalah rumah terkiri), sehingga semuanya di
[x, p + K] yang termuat dalam [x, x + K]. Penggeseran tidak
kehilangan satu rumah pun, dan jumlah menara tidak berubah. ∎

── KENAPA MENGURUTKAN PENTING ──────────────────────────────
Tanpa urutan, "rumah paling kiri yang belum terlayani" tidak
bisa ditemukan dengan cepat. Setelah terurut, satu sapuan cukup.

── JEBAKAN ─────────────────────────────────────────────────
1. K = 0 (sampel 2). Menara hanya melayani satu titik. Kode di
   bawah tetap benar: x + 0 = x, sehingga rumah yang berimpit
   pada posisi sama tetap terlayani satu menara.
2. Rumah yang berimpit. Syarat lewati memakai <=, bukan <.
3. Overflow: x sampai 10^9 dan K sampai 10^9, jumlahnya 2*10^9
   yang MELEBIHI int. Pakai long long.
4. Menyangka jawabannya bisa dihitung dengan (rentang total / K).
   Salah — rumah tidak tersebar merata.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll K;
    if (!(cin >> n >> K)) return 0;
    vector<ll> x(n);
    for (ll& v : x) cin >> v;

    sort(x.begin(), x.end());

    int menara = 0;
    int i = 0;
    while (i < n) {
        ll batas = x[i] + K;               // pasang menara tepat di x[i]
        menara++;
        while (i < n && x[i] <= batas) i++;  // <= : rumah berimpit ikut terlayani
    }

    cout << menara << '\n';
    return 0;
}
