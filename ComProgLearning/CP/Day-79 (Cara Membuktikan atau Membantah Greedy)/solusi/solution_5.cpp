/*
============================================================
✅ SOLUSI Exercise 5: Menebak Kriteria dari Data
============================================================
Difficulty: Hard | Kompleksitas: O(n log n)

── PROSES PENEMUAN (yang seharusnya kamu jalani) ───────────
Batasan n sampai 2*10^5 berarti jawabannya berupa pengurutan.
Tapi urut menurut apa? JANGAN MENEBAK. Lakukan ini:

  (1) tulis brute force atas seluruh permutasi untuk n <= 7
  (2) daftar kriteria yang masuk akal:
        a menaik, a menurun, b menaik, b menurun,
        a+b menaik, a+b menurun, a-b menaik, b-a menaik
  (3) jalankan SEMUANYA terhadap brute force pada ribuan
      masukan acak, catat mana yang tidak pernah gagal

Hasilnya: hanya "b MENURUN" yang bertahan. Seluruh kriteria
lain gagal, termasuk yang melibatkan a.

Pendekatan ini disebut menemukan kriteria secara EMPIRIS, dan
jauh lebih cepat daripada menatap soal berharap ilham. Setelah
menemukan, barulah membuktikan — dan buktinya jauh lebih mudah
dicari karena kamu sudah tahu APA yang harus dibuktikan.

── BUKTI (exchange argument pada max) ──────────────────────
Ambil urutan optimal. Lihat dua pekerjaan BERDAMPINGAN i lalu
j. Misal jumlah a sebelum keduanya adalah S. Suku-suku untuk
pekerjaan lain identik pada kedua urutan, jadi cukup
membandingkan dua suku ini:

  urutan (i, j): max( S + a_i + b_i ,  S + a_i + a_j + b_j )
  urutan (j, i): max( S + a_j + b_j ,  S + a_i + a_j + b_i )

Kurangkan konstanta (S + a_i + a_j) dari kedua sisi:

  (i, j) -> max( b_i - a_j ,  b_j )
  (j, i) -> max( b_j - a_i ,  b_i )

Andaikan b_i >= b_j. Maka:
  sisi kiri  : b_i - a_j <= b_i  dan  b_j <= b_i   -> <= b_i
  sisi kanan : memuat b_i secara langsung          -> >= b_i

Jadi urutan (i, j) TIDAK LEBIH BURUK ketika b_i >= b_j.
Menukar pasangan berdampingan yang melanggar tidak pernah
memperburuk, sehingga urut b menurun optimal. ∎

── INTUISI SETELAH BUKTINYA ────────────────────────────────
Suku b_i adalah "ekor" yang menempel setelah akumulasi a.
Ekor yang PANJANG harus muncul sedini mungkin, saat akumulasi a
masih kecil. Panjang a_i sendiri tidak relevan untuk urutan
karena ia menggeser semuanya secara seragam.

── HUBUNGAN DENGAN HARI LAIN ───────────────────────────────
Soal ini identik strukturnya dengan Day 76 Exercise 4
(penjadwalan dua tahap). Perbedaannya di sini adalah CARA
menemukannya: Day 76 memintamu membuktikan, Day 79 memintamu
MENEMUKAN lebih dulu secara empiris.
Dua keterampilan yang berbeda, dan keduanya dibutuhkan.

── JEBAKAN ─────────────────────────────────────────────────
1. Menebak kriteria. Tiga dugaan yang wajar semuanya salah.
2. Menguji kriteria hanya pada beberapa kasus.
3. Menyangka jawabannya sum(a) + max(b). Itu benar hanya kalau
   pekerjaan ber-b terbesar dikerjakan TERAKHIR — justru
   kebalikan dari yang optimal.
4. Lupa long long: n = 2*10^5 dikali 10^9 = 2*10^14.
5. Melacak maksimum hanya di akhir. Nilai terbesar bisa
   dicapai di tengah.
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
    vector<pair<ll, ll>> j(n);
    for (auto& [a, b] : j) cin >> a >> b;

    // ditemukan secara empiris, lalu dibuktikan: b MENURUN
    sort(j.begin(), j.end(), [](const pair<ll, ll>& x, const pair<ll, ll>& y) {
        return x.second > y.second;
    });

    ll akum = 0, jawab = 0;
    for (auto& [a, b] : j) {
        akum += a;
        jawab = max(jawab, akum + b);       // maksimum bisa dicapai di tengah
    }

    cout << jawab << '\n';
    return 0;
}
