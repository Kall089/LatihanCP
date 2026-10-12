/*
============================================================
✅ SOLUSI Exercise 2: Susun Bilangan Terbesar
============================================================
Difficulty: Easy | Kompleksitas: O(n log n * L), L = panjang string

── IDE UTAMA ────────────────────────────────────────────────
Urutkan dengan komparator: x mendahului y jika (x + y) > (y + x)
sebagai perbandingan STRING (leksikografis).

── KENAPA BUKAN "URUT MENURUN SEBAGAI BILANGAN" ────────────
Ambil {3, 30}. Urut menurun sebagai bilangan memberi 30 lalu 3
→ "303". Padahal 3 lalu 30 memberi "330" yang lebih besar.
Nilai numerik tidak menangkap apa yang penting; yang penting
adalah bagaimana digit-digitnya BERSAMBUNG.

── DARI DUA ELEMEN KE SELURUH ARRAY ────────────────────────
Kalau hanya ada x dan y, cuma ada dua susunan: x+y dan y+x.
Kita pilih yang lebih besar. Itu langsung memberi komparator.

Exchange argument: pada urutan optimal, dua elemen berdampingan
x lalu y pasti memenuhi x+y >= y+x. Kalau tidak, tukar keduanya:
seluruh string lain tidak berubah (panjang total sama, prefiks
di depan sama, sufiks di belakang sama), tetapi bagian tengah
menjadi lebih besar → hasil keseluruhan lebih besar. Kontradiksi.

── KENAPA KOMPARATOR INI SAH (transitif) ───────────────────
Ini tidak sepele. Definisikan x < y bila x+y < y+x. Relasi ini
terbukti merupakan strict weak ordering (bisa dibuktikan dengan
melihat x+y sebagai perbandingan nilai x * 10^|y| + y terhadap
y * 10^|x| + x, yang setara dengan membandingkan
x / (10^|x| - 1) terhadap y / (10^|y| - 1) — sebuah nilai
skalar per elemen, sehingga transitif).
Kalau komparator TIDAK transitif, std::sort bisa crash.

── JEBAKAN ─────────────────────────────────────────────────
1. Kasus semua nol: hasil naif "000...0". Harus dicetak "0".
   Sampel 2 khusus menguji ini.
2. Memakai perbandingan numerik x+y > y+x sebagai bilangan →
   overflow untuk angka panjang. Bandingkan sebagai string.
3. Komparator harus STRICT (memakai >, bukan >=). Dengan >=,
   dua elemen sama akan dianggap "saling mendahului" dan
   std::sort bisa membaca di luar batas.
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
    vector<string> a(n);
    for (string &s : a) cin >> s;

    // Komparator dari perbandingan dua elemen.
    // Perhatikan '>' (strict), bukan '>='.
    sort(a.begin(), a.end(), [](const string &x, const string &y) {
        return x + y > y + x;
    });

    string hasil;
    for (const string &s : a) hasil += s;

    // Kasus tepi: buang nol di depan, tetapi sisakan minimal satu digit.
    int i = 0;
    while (i + 1 < (int)hasil.size() && hasil[i] == '0') i++;

    cout << hasil.substr(i) << '\n';
    return 0;
}
