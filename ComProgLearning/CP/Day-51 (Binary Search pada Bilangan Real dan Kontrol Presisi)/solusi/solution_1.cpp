/*
============================================================
✅ Solution 1: Akar Kuadrat Tanpa sqrt
============================================================
Approach: Binary search real dengan iterasi tetap
Complexity: Time O(Q * 100) | Space O(1)
Key Insight: Kerangkanya sama dengan binary search integer, tetapi dua hal
             berubah: lo = mid (bukan mid + 1, karena tidak ada "bilangan
             berikutnya" pada bilangan real), dan kriteria berhentinya
             berupa JUMLAH ITERASI TETAP, bukan lo == hi.

📖 KENAPA ITERASI TETAP, BUKAN EPSILON:
   Pada bilangan real, lo dan hi tidak pernah menjadi SAMA -- di antara dua
   bilangan real selalu ada bilangan lain. Lebih buruk lagi, pada nilai
   besar (v = 10^18), jarak antara dua double yang berdekatan sudah lebih
   besar dari 1e-9. Akibatnya kondisi `while (hi - lo > 1e-9)` TIDAK PERNAH
   terpenuhi dan loopnya berputar SELAMANYA.
   Iterasi tetap selalu berhenti, dan mudah dianalisis.

📖 BERAPA ITERASI: setiap iterasi membagi rentang dua.
   Setelah k iterasi, lebar rentang = rentang_awal / 2^k.
   Untuk rentang 10^9 dan target 10^-9, kita butuh 2^k >= 10^18, jadi k >= 60.
   100 iterasi memberi faktor 2^100 ~ 10^30 -- jauh lebih dari cukup, dan
   biayanya hanya 100 perkalian.

⚠️ BATAS ATAS ADALAH JEBAKAN UTAMA SOAL INI.
   Untuk v >= 1, akarnya <= v sehingga hi = v cukup.
   Untuk v < 1 (misalnya 0.25), akarnya adalah 0.5 yang LEBIH BESAR dari v.
   Memakai hi = v akan mengurung jawabannya di luar rentang pencarian dan
   menghasilkan 0.25 alih-alih 0.5.
   Solusinya: hi = max(1.0, v). Sampel 3 memang menguji ini.

⚠️ mid * mid PADA v = 10^18: akarnya 10^9, dan 10^9 * 10^9 = 10^18 masih
   dalam jangkauan double (yang bisa merepresentasikan sampai ~1.8e308).
   Presisinya yang terbatas, bukan jangkauannya. double punya ~15-17 digit
   signifikan, sehingga untuk v = 10^18 kita tidak bisa berharap presisi
   absolut lebih baik dari sekitar 10^-7 -- tetapi soal meminta kesalahan
   RELATIF, yang jauh lebih longgar.

⚠️ MENCETAK: printf("%.9f") atau cout << fixed << setprecision(9).
   Kata `fixed` WAJIB. Tanpanya, setprecision(9) berarti 9 digit SIGNIFIKAN,
   sehingga 1234567.891234 dicetak sebagai 1234567.89 -- seluruh bagian
   desimalnya hilang.

🔄 ALTERNATIVE APPROACHES:
- Metode Newton: x = (x + v/x) / 2, konvergen KUADRATIK (jumlah digit benar
  berlipat ganda tiap iterasi), sehingga 10 iterasi sudah cukup. Lebih cepat,
  tetapi butuh tebakan awal yang baik dan tidak berlaku umum untuk predikat
  sembarang. Binary search bekerja untuk predikat monoton APA PUN.
- sqrtl (long double): lebih presisi, tetapi soal melarang.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    if (!(cin >> Q)) return 0;

    while (Q--) {
        double v;
        cin >> v;

        double lo = 0, hi = max(1.0, v);      // max(1, v): jebakan v < 1
        for (int it = 0; it < 100; it++) {
            double mid = (lo + hi) / 2;
            if (mid * mid >= v) hi = mid;
            else                lo = mid;      // lo = mid, BUKAN mid + 1
        }

        printf("%.9f\n", lo);
    }
    return 0;
}
