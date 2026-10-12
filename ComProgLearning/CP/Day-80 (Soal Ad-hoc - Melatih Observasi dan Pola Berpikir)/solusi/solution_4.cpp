/*
============================================================
✅ SOLUSI Exercise 4: Memindahkan Batu ke Tetangga
============================================================
Difficulty: Medium | Kompleksitas: O(n)

── LANGKAH 1: PERIKSA KEMUSTAHILAN (paling murah) ──────────
Satu operasi memindahkan satu batu dari sebuah kotak ke
tetangganya, sehingga TOTAL batu tidak berubah. Itu invarian.
Agar semua kotak sama, total harus habis dibagi n.
Kalau tidak, jawabannya -1 — dan kita berhenti tanpa bekerja
lebih jauh.

Memeriksa kemustahilan lebih dulu adalah kebiasaan yang bagus:
ia murah, dan sering menyelesaikan separuh kasus uji.

── LANGKAH 2: BATAS BAWAH LEWAT ARGUMEN SEKAT ──────────────
Bayangkan SEKAT di antara kotak ke-i dan ke-(i+1).

Jumlah batu di kotak 0..i sekarang adalah prefix(i).
Setelah semuanya rata, jumlahnya harus (i+1) * rata.
Selisihnya
        d_i = prefix(i) - (i + 1) * rata
adalah banyaknya batu yang HARUS melintasi sekat ke-i:
  d_i > 0 -> sebanyak d_i batu harus keluar ke kanan
  d_i < 0 -> sebanyak |d_i| batu harus masuk dari kanan

Berapa pun cara kamu mengatur operasinya, setiap batu yang
melintasi sekat itu memerlukan minimal satu operasi. Jadi

        batas bawah = sum |d_i|  untuk i = 0 .. n-2

── LANGKAH 3: KONSTRUKSI YANG MENCAPAINYA ──────────────────
Batas bawah saja BUKAN solusi. Kita harus menunjukkan bahwa
nilai itu benar-benar bisa dicapai.

Konstruksinya: proses sekat dari kiri ke kanan. Pada sekat
ke-i, pindahkan tepat |d_i| batu melintasinya, ke arah yang
sesuai tanda d_i. Setiap perpindahan melintasi tepat satu
sekat, sehingga total operasinya persis sum |d_i|.

Yang perlu diperiksa: apakah selalu tersedia cukup batu saat
dibutuhkan? Ya — kalau kotak sebelah kiri sedang kekurangan,
kita cukup menunda perpindahannya sampai batu datang dari
kanan. Karena kita hanya menghitung JUMLAH operasi dan bukan
urutannya, penundaan itu tidak menambah biaya.

Batas bawah bertemu konstruksi -> jawabannya optimal. ∎

── MENGHITUNGNYA DALAM SATU SAPUAN ─────────────────────────
Tidak perlu menyimpan array prefix. Cukup pelihara satu
akumulator:
    c += a[i] - rata;   total += |c|;
Perhatikan bahwa setelah kotak terakhir, c pasti nol (karena
totalnya habis dibagi n), sehingga suku terakhirnya tidak
menambah apa pun.

── VERIFIKASI SAMPEL 1 ─────────────────────────────────────
{0, 0, 6, 2}, total 8, rata 2.
    i=0 : c = -2  -> |c| = 2   (total 2)
    i=1 : c = -4  -> |c| = 4   (total 6)
    i=2 : c =  0  -> |c| = 0   (total 6)
    i=3 : c =  0  -> |c| = 0   (total 6)
Jawaban 6. ✓

── JEBAKAN ─────────────────────────────────────────────────
1. Lupa memeriksa kemustahilan.
2. Menyangka jawabannya sum |a_i - rata|. Itu SALAH — batu
   yang harus berpindah jauh dihitung sekali per sekat yang
   dilintasi, bukan sekali saja.
3. Lupa long long: 2*10^5 kotak dengan 10^9 batu -> akumulasi
   sampai 2*10^14 atau lebih.
4. Hanya membuktikan batas bawah tanpa konstruksi (atau
   sebaliknya).
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
    vector<ll> a(n);
    ll total = 0;
    for (ll& x : a) { cin >> x; total += x; }

    if (total % n != 0) { cout << -1 << '\n'; return 0; }   // invarian
    ll rata = total / n;

    ll c = 0, operasi = 0;
    for (int i = 0; i < n; i++) {
        c += a[i] - rata;          // batu yang harus melintasi sekat ke-i
        operasi += llabs(c);
    }

    cout << operasi << '\n';
    return 0;
}
